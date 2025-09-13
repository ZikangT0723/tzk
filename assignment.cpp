#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<cctype>
#include<windows.h> // for Sleep()
using namespace std;
// test validation
void charValidation(char* option);
void waitEnter(string action);
const int ansnum = 23;
const int Studentnum = 100;
const float checkans[ansnum] = { -11.3, 24.3, 4.3, -6.8, -36.8, 5.16, 1.95, 32.40, 28.80, -366.18, 2.25, 1125, 8.9, -1.1, 12.7, 3.13, 23, 1.74, 8.62, -21,
		10000, 200, 350 };
struct User {
	string Name;
	string ID;
	string password;
	float result_Test1 = 0; //7%
	int result_Test2 = 0; //23%
	bool attempt_Test1 = false;
	bool attempt_Test2 = false;
	float ans[ansnum] = {};
};
User Student[Studentnum];
int userindex = 0; //User count

//Userlist file operation
void loaduserdata();
void savefile(User*, string);

int getinfo(User[]);
int findslot(User[]);

//HOST FUNCTION
bool hostLogin();//Daniel
void hostMenu();//Daniel
//hostMenu_function
void Test1List();
void userlist(User[]);

//USER FUNCTION
bool userLogin(int* index);
void userMenu(int);
//userMenu_function
void note();
void sim();
void Test1_quizz(int);
void Test2_quizz(float*, int);


// Test1_function
struct Test1 {
	int num = 0; //Qustion No.
	string question;
	string objective_A;
	string objective_B;
	string objective_C;
	string objective_D;
	char ans = ' ';
	bool isDeleted = false;
};
Test1 Quizz[10]; //store 10 test1 questions
int Test1Count = 0; //count question from file
const int MAX_Numbers = 10; //maximum number
// quizz function for user
int checkAns(char ans, char answer);
void shuffle(int* temp, int Question_Numbers);//temporary storage for the sequence array
//quizz function for host
bool showTest1();
void createQuizz();
void editQuizz(int number);
void deleteQuizz(int num);
//file operation
void saveTest1();
void LoadTest1();

//Check and review for Test2_quizz
void checksubmit(float*, int);
int check(float*, int&);
int checksection(float*, int, int);
void review(float*, int);

// Simulator
void clipper();
void clamper();
void BJT_base();
void BJT_AC();
void BJT_Voltage_divider();
void jfet(); //Daniel
void mosfet(); //Daniel
void jfet_DrainCurrent();//Daniel
void non_inverting();
void VoltageFollower();
void invertingAmplifier();

//Notes
void notes_Diode();
void notes_BJT();
void notes_FET();
void notes_OA();

//Edit comment function by Trang
struct Comment
{
	string studentID = "";
	string text;
	string hostReply;
	bool deleted = false;
	bool fromHost = false;
};

const int MAX_COMMENTS = 100;
Comment comments[MAX_COMMENTS];
int commentCount = 0;

void saveComments(Comment[], int);
void loadComments(Comment[], int&);
void createNotification(Comment[], int&);
void hostCommentMenu(Comment[], int&);
void deleteComment(Comment[], int&);
void replyToComment(Comment[], int);
void showAllComments(Comment[], int);
void createStudentComment(Comment[], int&, User[], int);
void studentCommentMenu(Comment[], int&, User[], int);
void deleteEntireComment(Comment[], int&, int);
void deleteHostReply(Comment[], int, int);


int main() {
	int index;
	char choice;
	LoadTest1();
	loadComments(comments, commentCount);
	loaduserdata();

	do {
		system("cls");
		cout << "=================================\n";
		cout << "   WELCOME TO BASIC ELECTRONIC   \n";
		cout << "=================================\n";
		cout << "Please select mode:\n";
		cout << "1. Host Mode\n";
		cout << "2. User Mode\n";
		cout << "3. Exit\n";
		cout << "Choice (1~3): ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case '1':
			if (hostLogin())
				hostMenu();

			break;
		case '2':
			if (userLogin(&index)) {
				userlist(Student);
				userMenu(index);
			}

			break;
		case '3':
			cout << "Exitting program..."; //can design
			Sleep(1000);
			return 0;
			break;
		default:
			cout << "Invalid input please enter 1 to 3." << endl;
		}
	} while (choice != '3'); //debuged


}

//Pavan
bool userLogin(int* index) {
	int option;
	int position;
	string yourID;
	string yourPassword;

	cout << "Do you want to login or register [1 login, 2 register]";
	cin >> option;

	while (option != 1 && option != 2)
	{
		cout << "Invalid input please enter 1 or 2." << endl;
		cout << "Enter your choice: ";
		cin >> option;
	}

	if (option == 1) {
		cout << "Enter your student ID: ";
		cin >> yourID;

		cout << "Enter your password: ";
		cin >> yourPassword;
		for (int i = 0; i < userindex; i++) {
			if (yourID == Student[i].ID) {
				position = i;
				break;
			}
		}
		if (yourPassword == Student[position].password) {
			cout << "Login successful \n";
			*index = position;
			return true;
		}


		else {
			for (int attempts = 2; attempts > 0; attempts--) {
				cout << "Your ID: " << yourID << endl;
				cout << "You have " << attempts << " left...\n";
				cout << "Enter your correct password: ";
				cin >> yourPassword;
				if (yourPassword == Student[position].password) {
					*index = position;
					return true;
				}
			}
			cout << "You have no attempts left, please contact your teacher for help...\n";
			return false;
		}
	}
	else if (option == 2) {
		if (userindex < Studentnum) {
			*index = getinfo(Student);
			return true;
		}
		else {
			cout << "The userlist is full." << endl;
			return false;
		}
	}
}
//Daniel
bool hostLogin() {
	string hostID, hostPass;
	const string correctID = "Teacher";
	const string correctPass = "123456";
	int attempts = 0, maxAttempts = 3;
	system("cls");
	while (attempts < maxAttempts) {
		cout << "Host Login\n";
		cout << "==========\n";
		cout << "(Type 999 as Host ID to return to Login Surface)\n\n";
		cout << "Enter Host ID: ";
		cin >> hostID;

		// Option to return to login surface
		if (hostID == "999") {
			cout << "\nReturning to Login Surface...\n";
			Sleep(1000);
			return false; // exit without counting as failed attempt
		}

		cout << "Enter Password: ";
		cin >> hostPass;

		if (hostID == correctID && hostPass == correctPass) {
			cout << "\nLogin Successful!\n";
			cout << "Loading......\n";
			Sleep(1000);
			return true;
		}
		else {
			attempts++;
			system("cls");
			cout << "Invalid ID or Password. Attempts left: "
				<< (maxAttempts - attempts) << "\n";
		}
	}

	cout << "\nToo many failed attempts. Returning to Login Surface...\n";
	Sleep(1500);
	return false;
}
//Daniel
void hostMenu()
{
	char option;
	system("cls");
	do
	{
		cout << "Host Menu\n";
		cout << "=========\n";
		cout << "1. Test1 Question List\n";
		cout << "2. User List\n";
		cout << "3. Comment Management\n";//Trang
		cout << "4. Logout\n";
		cout << "Enter your choice(1~4):";
		cin >> option;
		switch (option)
		{
		case '1':
			Test1List();
			break;
		case '2':
			//userlist
			userlist(Student);
			break;
		case '3':
			hostCommentMenu(comments, commentCount);
			break;//Trang
		case '4':
			cout << "Exiting to Welcoming Surface..." << endl;
			Sleep(1000);
			break;
		default:
			system("cls");
			cout << "Invalid input. Please Enter (1-4)." << endl;
		}
	} while (option != '4');
}


void userMenu(int index) {
	int opt;
	if (userindex < 0 || userindex >= Studentnum) {
		cout << "ERROR! Invalid user index!" << endl;
		return;
	}
	while (true) {
		cout << "User Menu\n";
		cout << "=========\n";
		cout << "1. Test 1\n";
		cout << "2. Test 2 \n";
		cout << "3. Notes \n";
		cout << "4. Simulator\n";
		cout << "5. Student Comment Menu\n";
		cout << "0. Logout:";
		cin >> opt;
		system("cls");
		switch (opt) {
		case 1:
			if (!Student[index].attempt_Test1) {
				Test1_quizz(index);
			}
			else
			{
				cout << "You have submitted Test 1\n";
				cout << "Result of Test 1: " << Student[index].result_Test1 << " \n\n";
			}
			break;
		case 2:
			if (!Student[index].attempt_Test2) {
				Test2_quizz(Student[index].ans, index);

			}
			else {
				review(Student[index].ans, Student[index].result_Test2);
			}
			break;
		case 3:
			note();
			break;
		case 4:
			sim();
			break;
		case 5:
			studentCommentMenu(comments, commentCount, Student, index);
			break;
		case 0:
			cout << "You have been logged out..." << endl;
			saveComments(comments, commentCount);//Trang
			Sleep(1000);
			return;
		default:
			cout << "Invalid input try to choose again.(Input:1-5,0 to end)" << endl;
		}
	}
}

void Test2_quizz(float* answer, int index) {
	int i = 0, points = 0, record[12] = {};
	bool same;
	char option;//change name
	answer[ansnum] = {};

	do {
		do {
			same = false;
			cout << "Test 2\n";
			cout << "======\n";
			cout << "Choose the question you want to answer (Input 1-12, 13 to submit Test 2):";
			cin >> record[i];
			system("cls");
			if (record[i] == 0) {
				break;
			}
			for (int j = 0; j < i; j++) {
				if (record[i] == record[j]) {
					same = true;
					cout << "You have done question " << record[i] << ".\n";
					break;
				}
			}
		} while (same);

		cout << endl;
		switch (record[i]) {
		case 1:
			cout << "Question 1: Given the following configuration shown in Figure 1, Vin = 12V, Vd = 0.7V.\n ";
			cout << "Find Vout peak for the the negative half cycle.\n\n"; //answer is -11.3V 
			cout << "   ------------------------------\n";
			cout << "   |                            |            \n";
			cout << "   |                         -------         \n";
			cout << "   |                           / \\  Vd=0.7V \n";
			cout << "   |                          /   \\         \n";
			cout << " Vin = 12V                    -----          \n";
			cout << "   |                            |            \n";
			cout << "   |                            |            \n";
			cout << "   |                            |            \n";
			cout << "   |                            |            \n";
			cout << "   ---------Rload = 1k Ohm-------\n";
			cout << "         |                  | \n";
			cout << "         |                  | \n";
			cout << "         o                  o \n";
			cout << "         -       Vout       +\n";
			cout << "                Figure 1\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					clipper();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for Vout peak (in V):";
			cin >> answer[0];
			checksubmit(answer, 0);
			i++;
			break;

		case 2:
			cout << "Quesiton 2: Given the following configuration shown in Figure 2, Vin = 10V, Vd = 0.7V, Vbias = 5V.\n ";
			cout << "Find Vout peak in + ve half cycle and -ve half cycle.\n\n";
			cout << "   -------)|--------------------------------o +\n";
			cout << "   |      Vc    |               |\n";
			cout << "   |          -----             |\n";
			cout << "   |           / \\  Vd=0.7V     |" << endl;
			cout << "   |           ---              |\n";
			cout << "Vin=10V         |             RL=100kohm   Vout\n";
			cout << "   |           ---              |\n";
			cout << "   |            -   5V          |\n";
			cout << "   |           ---              |\n";
			cout << "   |            -               |\n";
			cout << "   |            |               |\n";
			cout << "   -----------------------------------------o -\n";
			cout << "                     Figure 2\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					clamper();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for Vout (+ve, in V):";
			cin >> answer[1];
			cout << "Enter the answer for Vout (-ve, in V):";
			cin >> answer[2];
			checksubmit(answer, 1);
			checksubmit(answer, 2);
			i++;
			break;

		case 3:
			cout << "Quesiton 3: Given the following configuration shown in Figure 3, Vin = 15V, Vd = 0.7V, Vbias = 7.5V.\n ";
			cout << "Find Vout peak in + ve half cycle and -ve half cycle.\n\n";
			cout << "   -------|(--------------------------------o +\n";
			cout << "   |      Vc    |               |\n";
			cout << "   |           ---              |\n";
			cout << "   |           \\ /  Vd=0.7V     |" << endl;
			cout << "   |          -----             |\n";
			cout << "Vin=15V         |             RL=100kohm   Vout\n";
			cout << "   |            -               |\n";
			cout << "   |           ---   7.5V       |\n";
			cout << "   |            -               |\n";
			cout << "   |           ---              |\n";
			cout << "   |            |               |\n";
			cout << "   -----------------------------------------o -\n";
			cout << "                     Figure 3\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					clamper();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for Vout (+ve, in V):";
			cin >> answer[3];
			cout << "Enter the answer for Vout (-ve, in V):";
			cin >> answer[4];
			checksubmit(answer, 3);
			checksubmit(answer, 4);
			i++;
			break;

		case 4:
			cout << "Question 4: Determine VCE and IC in the voltage-divider biased transistor circuit shown below. Assume betaDC = 100.\n\n";
			cout << "                       VCC = 10 V\n";
			cout << "                        |\n";
			cout << "      ------------------|\n";
			cout << "      |                 RC = 1.0k ohm\n";
			cout << "      |                 |\n";
			cout << "      R1 = 10k ohm      |\n";
			cout << "      |                /\n";
			cout << "      |             |\n";
			cout << "      --------------|\n";
			cout << "      |             |\n";
			cout << "      |                \\\n";
			cout << "      R2 = 5.6k ohm      |\n";
			cout << "      |                  RE = 560 ohm\n";
			cout << "      |                  |\n";
			cout << "      --------------------\n";
			cout << "               |\n";
			cout << "               |\n";
			cout << "              GND\n";
			cout << "                  Figure 4\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					BJT_Voltage_divider();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for IC (mA):";
			cin >> answer[5];
			cout << "Enter the answer for VCE (V):";
			cin >> answer[6];
			checksubmit(answer, 5);
			checksubmit(answer, 6);
			i++;
			break;

		case 5:
			cout << "Question 5: Determine the value of VCE when IC = 0.1mA and 0.2mA.\n\n";
			cout << "                       VCC = 36 V\n";
			cout << "                        |\n";
			cout << "      ------------------|\n";
			cout << "      |                 RC = 36k ohm\n";
			cout << "      |                 |\n";
			cout << "      |                 |\n";
			cout << "      |                /\n";
			cout << "      |             |\n";
			cout << "      ----- RB -----|\n";
			cout << "                    |\n";
			cout << "                       \\\n";
			cout << "                         |\n";
			cout << "                         |\n";
			cout << "                         |\n";
			cout << "                        GND\n";
			cout << "                     Figure 5\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					BJT_base();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for VCE in 0.1mA (V):";
			cin >> answer[7];
			cout << "Enter the answer for VCE in 0.2mA (V):";
			cin >> answer[8];
			checksubmit(answer, 7);
			checksubmit(answer, 8);
			i++;
			break;

		case 6:
			cout << "Question 6: This is the Common - Emitter(CE) Amplifier with bypass capacitor(C2) in the emitter, not involving swapping process and no load resistance, RL.\n\n";
			cout << "                                         VCC = 22 V\n";
			cout << "                                          |\n";
			cout << "                        ------------------|\n";
			cout << "                        |                 RC = 6.8k ohm\n";
			cout << "                        |                 |\n";
			cout << "                        R1 = 56k ohm      |-------C3---o---Vout\n";
			cout << "                        |                /\n";
			cout << "                        |              |\n";
			cout << " Vin ---o---RS---C1-----| -------------|\n";
			cout << "                        |              |\n";
			cout << "                        |                \\\n";
			cout << "                        R2 = 8.2k ohm        |\n";
			cout << "                        |                    |\n";
			cout << "                        |                    |----------------\n";
			cout << "                        |                    RE = 1.5k ohm    |\n";
			cout << "                        |                    |                C2\n";
			cout << "                        |                    |                |\n";
			cout << "                        --------------------------------------\n";
			cout << "                                             |\n";
			cout << "                                             |\n";
			cout << "                                            GND\n";
			cout << "                                         Figure 6\n\n";
			cout << "Find the value of voltage gain Av.\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					BJT_AC();
				}
			} while (toupper(option) == 'Y');
			cout << "\nEnter the answer for Av: ";
			cin >> answer[9]; // havent change ''''
			checksubmit(answer, 9);
			i++;
			break;

		case 7://ANS:2.25 ,1125
			cout << "Question 7: Determine the drain current (Id) and forward transconductance (gm) for Vgs = -4V for a 2N5459 JFET.\n";
			cout << "Refer to the data sheet for the JFET below.\n";
			cout << "Igss = -1nA \nVgs_off = -8V \nIdss = 9mA \ngm_0 = 2250 micro_S\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					jfet_DrainCurrent();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for Id (in mille-amperes):";
			cin >> answer[10];
			cout << "Enter the answer for gm (in micro-Siemens):";
			cin >> answer[11];
			checksubmit(answer, 10);
			checksubmit(answer, 11);
			i++;
			break;

		case 8:// Ans: V_DS: 8.9 V_GS:-1.1
			cout << "Question 8: FET (JFET)." << endl << endl;
			cout << "              +15 V" << endl;
			cout << "                 |    | Id = 5 mA" << endl;
			cout << "       1000_ohms Rd   v" << endl;
			cout << "                 |" << endl;
			cout << "                 | " << endl;
			cout << "                 D" << endl;
			cout << "                /" << endl;
			cout << "   ----G----> JFET" << endl;
			cout << "   |            \\" << endl;
			cout << "   |             S" << endl;
			cout << "   Rg 10 M_ohms  |" << endl;
			cout << "   |             Rs 220_ohms" << endl;
			cout << "   |             |" << endl;
			cout << "  GND           GND";
			cout << "            Figure 7\n\n";
			cout << "Find the voltage drain to source (V_DS) and voltage gate to source (V_GS)" << endl;
			cout << "in the circuit shown above." << endl << endl;
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					jfet();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for V_DS (in V and round to two decimals):";
			cin >> answer[12];
			cout << "Enter the answer for V_GS (in V and round to two decimals):";
			cin >> answer[13];
			checksubmit(answer, 12);
			checksubmit(answer, 13);
			i++;
			break;

		case 9:// Ans 12.7 ; 3.13
			cout << "Question 9: FET (E-MOSFET)." << endl << endl;
			cout << "                         +24 V" << endl;
			cout << "             --------------|" << endl;
			cout << "             |             |    | Id " << endl;
			cout << "  100 k_ohms R1   200_ohms Rd   V" << endl;
			cout << "             |             | " << endl;
			cout << "             |             D" << endl;
			cout << "             |            /" << endl;
			cout << "             ----G---- E_MOSFET" << endl;
			cout << "             |            \\" << endl;
			cout << "             |             S" << endl;
			cout << "             |             |" << endl;
			cout << "   15 k_ohms R2            |" << endl;
			cout << "             |             |" << endl;
			cout << "            GND           GND" << endl;
			cout << "                     Figure 8\n\n";
			cout << "Find the voltage drain to source (V_DS) and voltage gate to source (V_GS)" << endl;
			cout << "in the E-MOSFET circuit shown above. Given that the particular MOSFET has" << endl;
			cout << "the theshold voltage Vgs_th = 2V and the parameter devices K = 50 mA/V^2 ." << endl << endl;
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					mosfet();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for V_DS (in V and round to two decimals):";
			cin >> answer[14];
			cout << "Enter the answer for V_GS (in V and round to two decimals):";
			cin >> answer[15];
			checksubmit(answer, 14);
			checksubmit(answer, 15);
			i++;
			break;

		case 10://NI
			cout << "Question 10: Non-Inverting Amplifier,NI.\n\n";
			cout << "                                       \n";
			cout << "                |\\                    \n";
			cout << "                | \\                   \n";
			cout << " Vin (+)------->|+ \\                  \n";
			cout << "                |   \\_____________Vout\n";
			cout << "                |   /        |         \n";
			cout << "        ------->|- /         |         \n";
			cout << "        |       | /          Rf        \n";
			cout << "        |       |/           |         \n";
			cout << "        |____________________|         \n";
			cout << "                             |         \n";
			cout << "                             |         \n";
			cout << "                             Ri        \n";
			cout << "                             |         \n";
			cout << "                            GND        \n";
			cout << "                     Figure 9\n\n";
			cout << "Given: Rf =220000 ohms, Ri =10000 ohms ,Vin = 5.0 V, Aol = 200000 , Zin = 2000000 ohms, Zout = 75 ohms.\n";
			cout << "Determine the closed-loop voltage gain,Acl, the input and output impedances of the amplifier.\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					non_inverting();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for closed-loop voltage gain, Acl:";
			cin >> answer[16];
			cout << "Enter the answer for the input impedance (in Giga ohms) :";
			cin >> answer[17];
			cout << "Enter the answer for the output impedance (in micro ohms):";
			cin >> answer[18];
			checksubmit(answer, 16);
			checksubmit(answer, 17);
			checksubmit(answer, 18);
			i++;
			break;

		case 11://I
			cout << "Question 11: Inverting Amplifier,I.\n\n";
			cout << "                                               \n";
			cout << "                    _______Rf_______           \n";
			cout << "                   |               |          \n";
			cout << "                   |               |          \n";
			cout << "                   |    |\\         |          \n";
			cout << "                   |    | \\        |          \n";
			cout << " Vin (~)------Ri------->|+ \\       |          \n";
			cout << "                        |   \\______|____Vout  \n";
			cout << "                        |   /                  \n";
			cout << "                ------->|- /                   \n";
			cout << "                |       | /                    \n";
			cout << "                |       |/                     \n";
			cout << "               GND                             \n";
			cout << "                                               \n";
			cout << "                     Figure 10\n\n";
			cout << "Given: Rf =210000 ohms, Ri =10000 ohms.\n";
			cout << "Determine the closed-loop voltage gain,Acl and the input impedance of the amplifier.\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					invertingAmplifier();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for closed-loop voltage gain,Acl:";
			cin >> answer[19];
			cout << "Enter the answer for the input impedance:";
			cin >> answer[20];
			checksubmit(answer, 19);
			checksubmit(answer, 20);
			i++;
			break;

		case 12://VF
			cout << "Question 12: Voltage Follower,VF.\n\n";
			cout << "                                       \n";
			cout << "                |\\                    \n";
			cout << "                | \\                   \n";
			cout << " Vin (~)------->|+ \\                  \n";
			cout << "  |             |   \\_____________Vout\n";
			cout << "  GND           |   /        |         \n";
			cout << "        ------->|- /         |         \n";
			cout << "        |       | /          Rf        \n";
			cout << "        |       |/           |         \n";
			cout << "        |____________________|         \n";
			cout << "                             |         \n";
			cout << "                             |         \n";
			cout << "                             Ri        \n";
			cout << "                             |         \n";
			cout << "                            GND        \n";
			cout << "                     Figure 11\n\n";
			cout << "Given: Rf =230000 ohms, Ri =10000 ohms , Aol = 200000 , Zin = 1000000 ohms, Zout = 70 ohms and B = 1.\n";
			cout << "Determine the input and output impedances of the amplifier.\n\n";
			do {
				cout << "\nDo you want to use a simulator? (Y/N):";
				cin >> option;
				charValidation(&option);
				if (toupper(option) == 'Y') {
					VoltageFollower();
				}
			} while (toupper(option) == 'Y');
			cout << "Enter the answer for the input impedance (in Giga ohms):";
			cin >> answer[21];
			cout << "Enter the answer for the output impedance (in micro ohms):";
			cin >> answer[22];
			checksubmit(answer, 21);
			checksubmit(answer, 22);
			i++;
			break;
		case 13:
			system("cls");
			break;
		default:
			system("cls");
			cout << "Invalid input try to choose again.(Input:1-12,13 to end)" << endl;
			break;
		}
	} while (record[i] != 13);
	check(answer, Student[index].result_Test2);
	cout << "Score updated:" << Student[index].result_Test2 << endl;
	Student[index].attempt_Test2 = true;
	cout << "End of Quizz. Your total score is " << Student[index].result_Test2 << " Out of " << ansnum << "." << endl;
	savefile(Student, "Userlist");
}

void note() {
	char chap;

	do {
		cout << "Notes Selection\n";
		cout << "===============\n";
		cout << "Chapter 1: Diodes\n"
			<< "Chapter 2: Bipolar Junction Transistor\n"
			<< "Chapter 3: Field Effect Transistor\n"
			<< "Chapter 4: Operational Ampifier\n";
		cout << "Choose the chapter of notes you want to read (0.return):";
		cin >> chap;
		system("cls");
		switch (chap) {
		case '1':
			notes_Diode();
			break;
		case '2':
			notes_BJT();
			break;
		case '3':
			notes_FET();
			break;
		case '4':
			notes_OA();
			break;
		case '0':
			system("cls");
			cout << "You have returned to menu." << endl;
			break;
		default:
			system("cls");
			cout << "Invalid input try to choose again.(Input:1-4,0 to end)" << endl;
			break;
		}

	} while (chap != '0');
}
void sim()
{
	char opt_simulator;
	do
	{
		system("cls");
		cout << "\nSelect the type of simulator\na.Clipper\nb.Clamper\nc.DC(Voltage divider bias)\nd.DC(base bias)\ne.AC\nf.JFET Drain Current\n"
			<< "g.JFET\nh.MOSFET\n" << "i.non inverting\nj.Voltage follower\nk.inverting amplifier\n0.return:";
		cin >> opt_simulator;
		opt_simulator = tolower(opt_simulator);
		switch (opt_simulator)
		{
		case 'a':
			clipper();
			break;

		case 'b':
			clamper();
			break;

		case 'c':
			BJT_Voltage_divider();
			break;

		case 'd':
			BJT_base();
			break;

		case 'e':
			BJT_AC();
			break;

		case 'f':
			jfet_DrainCurrent();
			break;

		case 'g':
			jfet();
			break;

		case 'h':
			mosfet();
			break;

		case 'i':
			non_inverting();
			break;

		case 'j':
			VoltageFollower();
			break;

		case 'k':
			invertingAmplifier();
			break;

		case '0':
			system("cls");
			cout << "You have returned to menu." << endl;
			break;

		default:
			system("cls");
			cout << "Invalid input try to choose again! Enter 1-11 and 0 to end only!" << endl;
			break;
		}
	} while (opt_simulator != '0');
}


void loaduserdata() {
	userindex = 0;
	fstream list = fstream("Userlist", ios::in);
	string line;
	string emptyspace;
	while (userindex < Studentnum) {
		cout << "userindex(load):" << userindex << endl;
		if (!getline(list, line, '|')) {
			break;
		}
		Student[userindex].Name = line;

		if (getline(list, line, '|')) {
			Student[userindex].ID = line;
		}
		if (getline(list, line, '|')) {
			Student[userindex].password = line;
		}
		if (getline(list, line, '|')) {
			Student[userindex].result_Test1 = stof(line);
		}
		if (getline(list, line, '|'))
		{
			Student[userindex].result_Test2 = stoi(line);
		}
		if (getline(list, line, '|')) {
			Student[userindex].attempt_Test1 = stoi(line);
		}
		if (getline(list, line, '\n'))
		{
			Student[userindex].attempt_Test2 = stoi(line);
		}

		for (int j = 0; j < ansnum; j++) {
			if (getline(list, line, ','))
			{
				Student[userindex].ans[j] = stof(line);
			}
			else {
				break; // Stop if no more lines to read
			}
		}
		getline(list, line);
		userindex++;

		if (userindex >= Studentnum) break; //break if exceed the limit

	}
	list.close();
}

int getinfo(User Student[]) {
	bool IDvalid, IDdigits;
	loaduserdata();
	cout << "Enter your name:";
	cin.ignore();
	getline(cin, Student[userindex].Name);
	do {
		IDvalid = false, IDdigits = true;
		cout << "Enter your Student ID:";
		getline(cin, Student[userindex].ID);
		if (Student[userindex].ID.length() != 7) {
			cout << "Error: Student ID must be exactly 7 digits long.\n";
			continue;
		}
		for (int i = 0; i < Student[userindex].ID.length(); i++) {
			if (!isdigit(Student[userindex].ID[i])) {
				IDdigits = false;
				break;
			}
		}
		if (!IDdigits) {
			cout << "Error: Student ID must contain only digits (0-9).\n";
			continue;
		}
		if (Student[userindex].ID == "0000000") {
			cout << "Error: Student ID must not be empty.\n";
			continue;
		}
		IDvalid = true;
	} while (!IDvalid);
	cout << "Enter your password: ";
	getline(cin, Student[userindex].password);
	userindex++;
	savefile(Student, "Userlist");
	return userindex - 1;
}
void userlist(User Student[]) {
	cout << "================================================\n";
	cout << "     Basic Electronic UGEA1313: User List\n";
	cout << "================================================\n";
	if (userindex == 0 && Student[userindex].Name == "") {
		cout << "NO student registered yet.\n";
	}
	else {
		for (int width = 0; width <= 89; width++) {
			cout << "-";
		}
		cout << "\n";
		for (int i = 0; i < userindex; i++) {
			cout << setw(3) << right << i + 1 << ". " << "Name: " << left << setw(20) << Student[i].Name <<
				" | Student ID: " << setw(7) << Student[i].ID <<
				" | Test 1: " << fixed << setprecision(2) << Student[i].result_Test1 << "/7.00" <<
				" | Test 2: " << setw(2) << right << Student[i].result_Test2 << "/23" << endl;

		}
		for (int width = 0; width <= 89; width++) {
			cout << "-";
		}

	}
	cout << "\n";
	cin.ignore();
	waitEnter("return menu");
	system("cls");
}

void savefile(User* Student, string name) {
	fstream list = fstream("Userlist", ios::out);
	if (!list.is_open()) {
		cout << "Error opening file for saving: " << name << endl;
		return;
	}
	cout << "index(save):" << userindex << endl;

	for (int i = 0; i < userindex; i++) {

		list << Student[i].Name << "|"
			<< Student[i].ID << "|"
			<< Student[i].password << "|" //Pavan added this
			<< Student[i].result_Test1 << "|"
			<< Student[i].result_Test2 << "|"
			<< Student[i].attempt_Test1 << "|"
			<< Student[i].attempt_Test2 << "\n";
		for (int j = 0; j < ansnum; j++) {
			list << Student[i].ans[j] << ",";
		}
		list << "\n";

	}

	list.close();

}

int check(float* answer, int& points) {
	points = 0;
	for (int i = 0; i < 23; i++) {
		if (checkans[i] >= 0) {
			if ((checkans[i] - (checkans[i] * 5 / 100)) <= *(answer + i) && *(answer + i) <= (checkans[i] + (checkans[i] * 5 / 100))) {
				points++;
			}
		}
		else {
			if ((checkans[i] + (checkans[i] * 5 / 100)) <= *(answer + i) && *(answer + i) <= (checkans[i] - (checkans[i] * 5 / 100))) {
				points++;
			}
		}
	}
	return points;
}
void checksubmit(float* answer, int i) {
	if (checkans[i] >= 0) {
		if ((checkans[i] - (checkans[i] * 5 / 100)) >= *(answer + i) || *(answer + i) >= (checkans[i] + (checkans[i] * 5 / 100))) {
			cout << "Your answer " << answer[i] << " is wrong!\n";
			cout << "The correct answer is: " << checkans[i] << endl;

		}
	}
	else {
		if ((checkans[i] + (checkans[i] * 5 / 100)) >= *(answer + i) || *(answer + i) >= (checkans[i] - (checkans[i] * 5 / 100))) {
			cout << "Your answer " << answer[i] << " is wrong!\n";
			cout << "The correct answer is: " << checkans[i] << endl;
		}
	}
}
int checksection(float* answer, int i, int range) {
	int points = 0;
	for (i; i <= range; i++) {
		if (checkans[i] >= 0) {
			if ((checkans[i] - (checkans[i] * 5 / 100)) <= *(answer + i) && *(answer + i) <= (checkans[i] + (checkans[i] * 5 / 100))) {
				points++;

			}
		}
		else {
			if ((checkans[i] + (checkans[i] * 5 / 100)) <= *(answer + i) && *(answer + i) <= (checkans[i] - (checkans[i] * 5 / 100))) {
				points++;
			}
		}
	}
	return points;
}
void review(float* answer, int score) {
	cout << "=========================\n";
	cout << "      Test 2 Review\n";
	cout << "=========================\n";
	cout << "Question 1: Given the following configuration shown in Figure 1, Vin = 12V, Vd = 0.7V.\n ";
	cout << "Find Vout peak for the the negative half cycle.\n\n"; //answer is -11.3V 
	cout << "   ------------------------------\n";
	cout << "   |                            |            \n";
	cout << "   |                         -------         \n";
	cout << "   |                           / \\  Vd=0.7V \n";
	cout << "   |                          /   \\         \n";
	cout << " Vin = 12V                    -----          \n";
	cout << "   |                            |            \n";
	cout << "   |                            |            \n";
	cout << "   |                            |            \n";
	cout << "   |                            |            \n";
	cout << "   ---------Rload = 1k Ohm-------\n";
	cout << "         |                  | \n";
	cout << "         |                  | \n";
	cout << "         o                  o \n";
	cout << "         -       Vout       +\n";
	cout << "                Figure 1\n\n";
	cout << "Your answer is       : " << setw(5) << right << answer[0] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[0] << right
		<< setw(15) << "Score = " << checksection(answer, 0, 0) << endl << endl;
	cout << "Quesiton 2: Given the following configuration shown in Figure 2, Vin = 10V, Vd = 0.7V, Vbias = 5V.\n ";
	cout << "Find Vout peak in + ve half cycle and -ve half cycle.\n\n";
	cout << "   -------)|--------------------------------o +\n";
	cout << "   |      Vc    |               |\n";
	cout << "   |          -----             |\n";
	cout << "   |           / \\  Vd=0.7V     |" << endl;
	cout << "   |           ---              |\n";
	cout << "Vin=10V         |             RL=100kohm   Vout\n";
	cout << "   |           ---              |\n";
	cout << "   |            -   5V          |\n";
	cout << "   |           ---              |\n";
	cout << "   |            -               |\n";
	cout << "   |            |               |\n";
	cout << "   -----------------------------------------o -\n";
	cout << "                     Figure 2\n\n";
	cout << "Your answer is       : " << setw(5) << right << answer[1] << setw(5) << right << ", " << setw(5) << right << answer[2] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[1] << setw(5) << right << ", " << setw(5) << right << checkans[2] << right
		<< setw(15) << "Score = " << checksection(answer, 1, 2) << endl << endl;
	cout << "Quesiton 3: Given the following configuration shown in Figure 3, Vin = 15V, Vd = 0.7V, Vbias = 7.5V.\n ";
	cout << "Find Vout peak in + ve half cycle and -ve half cycle.\n\n";
	cout << "   -------|(--------------------------------o +\n";
	cout << "   |      Vc    |               |\n";
	cout << "   |           ---              |\n";
	cout << "   |           \\ /  Vd=0.7V     |" << endl;
	cout << "   |          -----             |\n";
	cout << "Vin=15V         |             RL=100kohm   Vout\n";
	cout << "   |            -               |\n";
	cout << "   |           ---   7.5V       |\n";
	cout << "   |            -               |\n";
	cout << "   |           ---              |\n";
	cout << "   |            |               |\n";
	cout << "   -----------------------------------------o -\n";
	cout << "                     Figure 3\n\n";
	cout << "Your answer is       : " << setw(5) << answer[3] << setw(5) << right << ", " << setw(5) << right << answer[4] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[3] << setw(5) << right << ", " << setw(5) << right << checkans[4] << right
		<< setw(15) << "Score = " << checksection(answer, 3, 4) << endl << endl;
	cout << "Question 4: Determine VCE and IC in the voltage-divider biased transistor circuit shown below. Assume betaDC = 100.\n\n";
	cout << "                       VCC = 10 V\n";
	cout << "                        |\n";
	cout << "      ------------------|\n";
	cout << "      |                 RC = 1.0k ohm\n";
	cout << "      |                 |\n";
	cout << "      R1 = 10k ohm      |\n";
	cout << "      |                /\n";
	cout << "      |             |\n";
	cout << "      --------------|\n";
	cout << "      |             |\n";
	cout << "      |                \\\n";
	cout << "      R2 = 5.6k ohm      |\n";
	cout << "      |                  RE = 560 ohm\n";
	cout << "      |                  |\n";
	cout << "      --------------------\n";
	cout << "               |\n";
	cout << "               |\n";
	cout << "              GND\n";
	cout << "                  Figure 4\n\n";
	cout << "Your answer is       : " << setw(5) << answer[5] << setw(5) << right << ", " << setw(5) << right << answer[6] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[5] << setw(5) << right << ", " << setw(5) << right << checkans[6] << right
		<< setw(15) << "Score = " << checksection(answer, 5, 6) << endl << endl;
	cout << "Question 5 : Determine the value of VCE when IC = 0.1mA and 0.2mA.\n\n";
	cout << "                       VCC = 36 V\n";
	cout << "                        |\n";
	cout << "      ------------------|\n";
	cout << "      |                 RC = 36k ohm\n";
	cout << "      |                 |\n";
	cout << "      |                 |\n";
	cout << "      |                /\n";
	cout << "      |             |\n";
	cout << "      ----- RB -----|\n";
	cout << "                    |\n";
	cout << "                       \\\n";
	cout << "                         |\n";
	cout << "                         |\n";
	cout << "                         |\n";
	cout << "                        GND\n";
	cout << "                     Figure 5\n\n";
	cout << "Your answer is       : " << setw(5) << answer[7] << setw(5) << right << ", " << setw(5) << right << answer[8] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[7] << setw(5) << right << ", " << setw(5) << right << checkans[8] << right
		<< setw(15) << "Score = " << checksection(answer, 7, 8) << endl << endl;
	cout << "Question 6: This is the Common - Emitter(CE) Amplifier with bypass capacitor(C2) in the emitter, not involving swapping process and no load resistance, RL.\n\n";
	cout << "                                         VCC = 22 V\n";
	cout << "                                          |\n";
	cout << "                        ------------------|\n";
	cout << "                        |                 RC = 6.8k ohm\n";
	cout << "                        |                 |\n";
	cout << "                        R1 = 56k ohm      |-------C3---o---Vout\n";
	cout << "                        |                /\n";
	cout << "                        |              |\n";
	cout << " Vin ---o---RS---C1-----| -------------|\n";
	cout << "                        |              |\n";
	cout << "                        |                \\\n";
	cout << "                        R2 = 8.2k ohm        |\n";
	cout << "                        |                    |\n";
	cout << "                        |                    |----------------\n";
	cout << "                        |                    RE = 1.5k ohm    |\n";
	cout << "                        |                    |                C2\n";
	cout << "                        |                    |                |\n";
	cout << "                        --------------------------------------\n";
	cout << "                                             |\n";
	cout << "                                             |\n";
	cout << "                                            GND\n";
	cout << "                                         Figure 6\n\n";
	cout << "Your answer is       : " << setw(5) << right << answer[9] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[9] << right
		<< setw(15) << "Score = " << checksection(answer, 9, 9) << endl << endl;
	cout << "Question 7: Determine the drain current (Id) and forward transconductance (gm) for Vgs = -4V for a 2N5459 JFET.\n";
	cout << "Refer to the data sheet for the JFET below.\n";
	cout << "Igss = -1nA \nVgs_off = -8V \nIdss = 9mA \ngm_0 = 2250 micro_S\n\n";
	cout << "Your answer is       : " << setw(5) << answer[10] << setw(5) << right << ", " << setw(5) << right << answer[11] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[10] << setw(5) << right << ", " << setw(5) << right << checkans[11] << right
		<< setw(15) << "Score = " << checksection(answer, 10, 11) << endl << endl;
	cout << "Question 8: FET (JFET)." << endl << endl;
	cout << "              +15 V" << endl;
	cout << "                 |    | Id = 5 mA" << endl;
	cout << "       1000_ohms Rd   v" << endl;
	cout << "                 |" << endl;
	cout << "                 | " << endl;
	cout << "                 D" << endl;
	cout << "                /" << endl;
	cout << "   ----G----> JFET" << endl;
	cout << "   |            \\" << endl;
	cout << "   |             S" << endl;
	cout << "   Rg 10 M_ohms  |" << endl;
	cout << "   |             Rs 220_ohms" << endl;
	cout << "   |             |" << endl;
	cout << "  GND           GND";
	cout << "            Figure 7\n\n";
	cout << "Find the voltage drain to source (V_DS) and voltage gate to source (V_GS)" << endl;
	cout << "in the circuit shown above." << endl << endl;
	cout << "Your answer is       : " << setw(5) << answer[12] << setw(5) << right << ", " << setw(5) << right << answer[13] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[13] << setw(5) << right << ", " << setw(5) << right << checkans[13] << right
		<< setw(15) << "Score = " << checksection(answer, 12, 13) << endl << endl;
	cout << "Question 9: FET (E-MOSFET)." << endl << endl;
	cout << "                         +24 V" << endl;
	cout << "             --------------|" << endl;
	cout << "             |             |    | Id " << endl;
	cout << "  100 k_ohms R1   200_ohms Rd   V" << endl;
	cout << "             |             | " << endl;
	cout << "             |             D" << endl;
	cout << "             |            /" << endl;
	cout << "             ----G---- E_MOSFET" << endl;
	cout << "             |            \\" << endl;
	cout << "             |             S" << endl;
	cout << "             |             |" << endl;
	cout << "   15 k_ohms R2            |" << endl;
	cout << "             |             |" << endl;
	cout << "            GND           GND" << endl;
	cout << "                     Figure 8\n\n";
	cout << "Find the voltage drain to source (V_DS) and voltage gate to source (V_GS)" << endl;
	cout << "in the E-MOSFET circuit shown above. Given that the particular MOSFET has" << endl;
	cout << "the theshold voltage Vgs_th = 2V and the parameter devices K = 50 mA/V^2 ." << endl << endl;
	cout << "Your answer is       : " << setw(5) << answer[14] << setw(5) << right << ", " << setw(5) << right << answer[15] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[14] << setw(5) << right << ", " << setw(5) << right << checkans[15] << right
		<< setw(15) << "Score = " << checksection(answer, 14, 15) << endl << endl;
	cout << "Question 10: Non-Inverting Amplifier,NI.\n\n";
	cout << "                                       \n";
	cout << "                |\\                    \n";
	cout << "                | \\                   \n";
	cout << " Vin (+)------->|+ \\                  \n";
	cout << "                |   \\_____________Vout\n";
	cout << "                |   /        |         \n";
	cout << "        ------->|- /         |         \n";
	cout << "        |       | /          Rf        \n";
	cout << "        |       |/           |         \n";
	cout << "        |____________________|         \n";
	cout << "                             |         \n";
	cout << "                             |         \n";
	cout << "                             Ri        \n";
	cout << "                             |         \n";
	cout << "                            GND        \n";
	cout << "                     Figure 9\n\n";
	cout << "Given: Rf =220000 ohms, Ri =10000 ohms ,Vin = 5.0 V, Aol = 200000 , Zin = 2000000 ohms, Zout = 75 ohms.\n";
	cout << "Determine the closed-loop voltage gain,Acl, the input and output impedances of the amplifier.\n\n";
	cout << "Your answer is       : " << setw(5) << answer[16] << setw(5) << right << ", " << setw(5) << right << answer[17]
		<< ", " << setw(5) << right << answer[18] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[16] << setw(5) << right << ", " << setw(5) << right << checkans[17]
		<< ", " << setw(5) << right << checkans[18] << right
		<< setw(15) << "Score = " << checksection(answer, 16, 18) << endl << endl;
	cout << "Question 11: Inverting Amplifier,I.\n\n";
	cout << "                                               \n";
	cout << "                    _______Rf_______           \n";
	cout << "                   |               |          \n";
	cout << "                   |               |          \n";
	cout << "                   |    |\\         |          \n";
	cout << "                   |    | \\        |          \n";
	cout << " Vin (~)------Ri------->|+ \\       |          \n";
	cout << "                        |   \\______|____Vout  \n";
	cout << "                        |   /                  \n";
	cout << "                ------->|- /                   \n";
	cout << "                |       | /                    \n";
	cout << "                |       |/                     \n";
	cout << "               GND                             \n";
	cout << "                                               \n";
	cout << "                     Figure 10\n\n";
	cout << "Given: Rf =210000 ohms, Ri =10000 ohms.\n";
	cout << "Determine the closed-loop voltage gain,Acl and the input impedance of the amplifier.\n\n";
	cout << "Your answer is       : " << setw(5) << answer[19] << setw(5) << right << ", " << setw(5) << right << answer[20] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[19] << setw(5) << right << ", " << setw(5) << right << checkans[20] << right
		<< setw(15) << "Score = " << checksection(answer, 19, 20) << endl << endl;
	cout << "Question 12: Voltage Follower,VF.\n\n";
	cout << "                                       \n";
	cout << "                |\\                    \n";
	cout << "                | \\                   \n";
	cout << " Vin (~)------->|+ \\                  \n";
	cout << "  |             |   \\_____________Vout\n";
	cout << "  GND           |   /        |         \n";
	cout << "        ------->|- /         |         \n";
	cout << "        |       | /          Rf        \n";
	cout << "        |       |/           |         \n";
	cout << "        |____________________|         \n";
	cout << "                             |         \n";
	cout << "                             |         \n";
	cout << "                             Ri        \n";
	cout << "                             |         \n";
	cout << "                            GND        \n";
	cout << "                     Figure 11\n\n";
	cout << "Given: Rf =230000 ohms, Ri =10000 ohms , Aol = 200000 , Zin = 1000000 ohms, Zout = 70 ohms and B = 1.\n";
	cout << "Determine the input and output impedances of the amplifier.\n\n";
	cout << "Your answer is       : " << setw(5) << answer[21] << setw(5) << right << ", " << setw(5) << right << answer[22] << endl;
	cout << "The correct answer is: " << setw(5) << checkans[21] << setw(5) << right << ", " << setw(5) << right << checkans[22] << right
		<< setw(15) << "Score = " << checksection(answer, 21, 22) << endl << endl;
	cout << "Total score = " << score << "/" << ansnum << endl;
	cin.ignore();
	waitEnter("return menu");
	system("cls");
}

void Test1_quizz(int index)
{
	/* this function is to let user answer 10 question made
	by host and each user the sequence will be shuffled*/

	int sequence[MAX_Numbers] = { 1,2,3,4,5,6,7,8,9,10 };
	int Num = 1, score = 0;
	char ans;

	shuffle(sequence, MAX_Numbers);
	if (Test1Count == 0) {
		cout << "There are no Question uploaded by Teacher." << endl;
		return;
	}


	for (int i = 0; i < MAX_Numbers; i++) //i<10
	{
		if (!Quizz[sequence[i] - 1].question.empty() && (!Quizz[sequence[i] - 1].isDeleted)) {
			cout << "Question " << Num++ << ": " << endl;
			cout << Quizz[sequence[i] - 1].question << endl;
			cout << "A: " << Quizz[sequence[i] - 1].objective_A << endl;
			cout << "B: " << Quizz[sequence[i] - 1].objective_B << endl;
			cout << "C: " << Quizz[sequence[i] - 1].objective_C << endl;
			cout << "D: " << Quizz[sequence[i] - 1].objective_D << endl;
			cout << "Enter your answer: ";
			cin >> ans;
			ans = toupper(ans);
			score += checkAns(ans, Quizz[sequence[i] - 1].ans);
			cout << endl;
		}
	}
	Student[index].result_Test1 = (score / float(Test1Count)) * 7;
	Student[index].attempt_Test1 = true;
	cout << "End of Quizz. Your total score is " << score << " Out of " << Num - 1 << " ("
		<< fixed << setprecision(2) << Student[index].result_Test1 << "." << endl;
	savefile(Student, "Userlist");
}

void shuffle(int* temp, int Question_Numbers)//temporary storage for the sequence array
{
	srand(time(NULL));

	int storage;//temporary keep 1 number
	int random_element; //store the random number
	// Fisher-Yates (exchange element tiwce to shuffle sequence)
	for (int i = Question_Numbers - 1; i > 0; i--) {
		random_element = rand() % (i + 1);
		storage = temp[i];
		temp[i] = temp[random_element]; //exchange element 
		temp[random_element] = storage;
	}
}

int checkAns(char response, char answer)
{
	int score = 0;
	if (response == answer)
	{
		score++;
		cout << "Correct!" << endl;
	}
	else
	{
		cout << "Wrong! The correct answer is " << answer << "." << endl;
	}
	return score;
}

void Test1List()
{
	char choice = 'N';
	int option = 0;
	system("cls");
	while (true) {
		cout << "Test 1 Question list\n";
		cout << "====================\n";

		if (!showTest1())
		{
			cout << "Do you want to create a new Question for Test 1 (MCQ)\n";
			cout << "'Y' for yes, 'N' to return menu:";
			cin >> choice;
			charValidation(&choice);
			if (toupper(choice) == 'Y')
				createQuizz();
			else
			{
				cout << "back to menu...\n";
				break;
			}
		}
		else
		{

			cout << "Enter the question you want to edit or other integer to create Quizz (0 to return):";
			cin >> option;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				system("cls");
				cout << "Invalid input, Please try again." << endl;
			}
			else if (option == 0) {
				cout << "Cancel successfully, exit to menu..." << endl;
				break;
			}
			else if (option > 0 && option <= Test1Count)
				editQuizz(option);
			else
				createQuizz();
		}
	}
	Sleep(1000);
	system("cls");
}
bool showTest1()
{
	cout << "Test1Count= " << Test1Count << endl; //testing pls delete
	if (Test1Count == 0)
	{
		cout << "There are no Question insert." << endl;
		return false;
	}
	else {
		for (int i = 0; i < Test1Count; i++)
		{
			if (Quizz[i].isDeleted == false) {
				cout << "Question " << Quizz[i].num << ": " << endl;
				cout << Quizz[i].question << endl << endl;
			}
		}
		return true;
	}

}
void createQuizz()
{
	cin.ignore(); // clear buffer
	Test1 newQuizz;
	newQuizz.num = Test1Count + 1;

	system("cls");
	cout << "Create Question Test 1\n";
	cout << "======================\n";
	if (Test1Count >= 10) {
		cout << "The questions are full. Please delete before creating.\n";
		return;
	}

	cout << "\nEnter your question for Question " << newQuizz.num << " (999 to cancel): " << endl;
	getline(cin, newQuizz.question);
	if (newQuizz.question == "999")
	{
		cout << "Cancel successfully, return to Edit Question..." << endl;
		Sleep(1000);
		system("cls");
		return;
	}

	cout << "Enter the option A." << endl;
	cout << "A :";
	getline(cin, newQuizz.objective_A);

	cout << "Enter the option B." << endl;
	cout << "B :";
	getline(cin, newQuizz.objective_B);

	cout << "Enter the option C." << endl;
	cout << "C :";
	getline(cin, newQuizz.objective_C);

	cout << "Enter the option D." << endl;
	cout << "D :";
	getline(cin, newQuizz.objective_D);

	cout << "Answer for the Question " << newQuizz.num << " : ";
	cin >> newQuizz.ans;
	cin.ignore();

	newQuizz.isDeleted = false;

	Quizz[Test1Count++] = newQuizz;
	saveTest1();
	cout << "\nThe Question was save successfully..." << endl;
	Sleep(1000);
	system("cls");
	//back to menu....
}

void editQuizz(int number)
{
	char option;
	Test1 EditQuizz;

	EditQuizz = Quizz[number - 1]; //temporary storage
	while (true) {
		system("cls");
		cout << "Edit Question Test 1\n";
		cout << "====================\n";
		cout << Quizz[number - 1].question << endl;
		cout << "A: " << Quizz[number - 1].objective_A << endl;
		cout << "B: " << Quizz[number - 1].objective_B << endl;
		cout << "C: " << Quizz[number - 1].objective_C << endl;
		cout << "D: " << Quizz[number - 1].objective_D << endl;
		cout << "Corrrect Answer: " << Quizz[number - 1].ans << endl << endl;
		cout << "Enter the part you want to edit in Question " << number << ":\n"
			<< "1. Question\n"
			<< "2. Option A\n"
			<< "3. Option B\n"
			<< "4. Option C\n"
			<< "5. Option D\n"
			<< "6. Correct answer\n"
			<< "7. Delete\n"
			<< "8. Cancel\n"
			<< "Enter (1-8):";
		cin >> option;
		cin.ignore();
		if (option == '7')
		{
			deleteQuizz(number - 1);
			break;
		}
		else if (option == '8')
		{
			cout << "\nReturning to the Test 1 List...\n";
			break;
		}
		else {
			switch (option)
			{
			case '1':
				cout << "\nQuestion: " << EditQuizz.question << endl;
				cout << "Enter your new Question:" << endl;
				getline(cin, EditQuizz.question);
				break;

			case '2':
				cout << "\nA: " << EditQuizz.objective_A << endl;
				cout << "Enter your new Option A:" << endl;
				getline(cin, EditQuizz.objective_A);
				break;

			case '3':
				cout << "\nB: " << EditQuizz.objective_B << endl;
				cout << "Enter your new Option B:" << endl;
				getline(cin, EditQuizz.objective_B);
				break;

			case '4':
				cout << "\nC: " << EditQuizz.objective_C << endl;
				cout << "Enter your new Option C:" << endl;
				getline(cin, EditQuizz.objective_C);
				break;

			case '5':
				cout << "\nD: " << EditQuizz.objective_D << endl;
				cout << "Enter your new Option D:" << endl;
				getline(cin, EditQuizz.objective_D);
				break;

			case '6':
				cout << "\nAnswer: " << EditQuizz.ans << endl;
				cout << "Enter your new Answer:" << endl;
				cin >> EditQuizz.ans;
				cin.ignore();
				break;

			default:
				cout << "\nInvalid option, please Enter (1-8)";
				Sleep(1000);
			}
			Quizz[number - 1] = EditQuizz;
			Quizz[number - 1].isDeleted = false;
			saveTest1();
			cout << "Editted successfully..." << endl;
		}
	}
	Sleep(500);
	system("cls");
}

void deleteQuizz(int num)
{
	Quizz[num].isDeleted = true;
	for (int i = num; i < Test1Count - 1; i++)
	{
		Quizz[i + 1].num = i + 1;
		Quizz[i] = Quizz[i + 1];
	}
	Quizz[Test1Count - 1] = {};
	Test1Count--;
	saveTest1();
	cout << "The quizz was deleted successfully.\n";
}

void saveTest1()
{
	ofstream outputFile;
	outputFile.open("Test1");
	for (int i = 0; i < Test1Count; i++)
	{
		if (Quizz[i].isDeleted == false) {
			outputFile << Quizz[i].num << "|";
			outputFile << Quizz[i].question << "|";
			outputFile << Quizz[i].objective_A << "|";
			outputFile << Quizz[i].objective_B << "|";
			outputFile << Quizz[i].objective_C << "|";
			outputFile << Quizz[i].objective_D << "|";
			outputFile << Quizz[i].ans << "\n";

		}
	}
	outputFile.close();
}

void LoadTest1()
{
	Test1Count = 0;
	ifstream inFile("Test1");
	if (!inFile) {
		cout << "Cann't find the File\n";
		return;
	}
	string line;
	Test1 tempQuizz;

	while (true)
	{

		if (!getline(inFile, line, '|')) break;
		tempQuizz.num = stoi(line);

		if (!getline(inFile, tempQuizz.question, '|')) break;
		if (!getline(inFile, tempQuizz.objective_A, '|')) break;
		if (!getline(inFile, tempQuizz.objective_B, '|')) break;
		if (!getline(inFile, tempQuizz.objective_C, '|')) break;
		if (!getline(inFile, tempQuizz.objective_D, '|')) break;
		if (!getline(inFile, line)) break;
		tempQuizz.ans = line[0]; //store ans to char from string line[0] means the first character.
		tempQuizz.isDeleted = false;
		Quizz[Test1Count++] = tempQuizz;

		if (Test1Count >= MAX_Numbers) break; //break if exceed the limit
		if (line.empty()) break;
	}
	inFile.close();
}
//Trang edit comment fuction
//menu
void hostCommentMenu(Comment comments[], int& count) {
	int choice;
	do {
		cout << "\n--- Host Comment Menu ---\n";
		cout << "1. Show All Comments\n";
		cout << "2. Create Notification\n";
		cout << "3. Reply to Student Comment\n";
		cout << "4. Delete Comment\n";
		cout << "0. Return\n";
		cout << "Choice (0~4): ";
		cin >> choice;

		switch (choice) {
		case 0: cout << "Returning...\n"; break;
		case 1: showAllComments(comments, count); break;
		case 2: createNotification(comments, count); break;
		case 3: replyToComment(comments, count); break;
		case 4: deleteComment(comments, count); break;
		default: cout << "Invalid choice.\n"; break;
		}
	} while (choice != 0);
}
void studentCommentMenu(Comment comments[], int& count, User Student[], int index)
{
	int option;
	do {
		cout << "\n--- Student Comment Menu ---\n";
		cout << "1. Show All Comments and Reply\n";
		cout << "2. Create a Comment\n";
		cout << "0. Return\n";
		cout << "Choice: ";
		cin >> option;

		switch (option) {
		case 1: showAllComments(comments, count); break;
		case 2:createStudentComment(comments, count, Student, index);
		}
	} while (option != 0);


}
//create
void createNotification(Comment comments[], int& count) {
	if (count >= MAX_COMMENTS) {
		cout << "Comment list is full!" << endl;
		return;
	}
	cin.ignore();
	cout << "Enter your comment (as host): ";
	getline(cin, comments[count].text);

	comments[count].studentID = "";
	comments[count].fromHost = true;
	comments[count].hostReply = "";
	comments[count].deleted = false;

	cout << "Host comment saved!" << endl;
	count++;
	saveComments(comments, count);
}
void createStudentComment(Comment comments[], int& count, User Student[], int index) {
	if (count >= MAX_COMMENTS) {
		cout << "Comment list is full!" << endl;
		return;
	}
	cin.ignore();
	cout << "Enter your comment: ";
	getline(cin, comments[count].text);

	comments[count].studentID = Student[index].ID;
	comments[count].fromHost = false;
	comments[count].hostReply = "";
	comments[count].deleted = false;

	cout << "Comment saved! (Student ID: " << Student[index].ID << ")" << endl;//can save student id
	count++;
	saveComments(comments, count);
}

void showAllComments(Comment comments[], int count) {
	cout << "\n======= Comment List =======\n";
	if (count == 0) {
		cout << "No comments yet.\n";
		return;
	}

	for (int i = 0; i < count; i++) {
		if (!comments[i].deleted) {
			cout << "Comment #" << i << endl;
			if (comments[i].fromHost) {
				cout << " ------Notification------\n";
				cout << "  Attention: " << comments[i].text << endl;
			}
			else {
				cout << " [Student ID: " << comments[i].studentID << "]\n";
				cout << "  Comment: " << comments[i].text << endl;
			}

			if (!comments[i].hostReply.empty())
				cout << "--->Host Reply: " << comments[i].hostReply << endl;
			cout << "----------------------------\n";
		}
	}
	cout << "============================\n";
}
void replyToComment(Comment comments[], int count) {
	if (count == 0) {
		cout << "No comments to reply.\n";
		return;
	}

	char reply = 'Y';
	while (toupper(reply) == 'Y') {
		showAllComments(comments, count);

		int index;
		cout << "Enter the comment number to reply: ";
		cin >> index;

		if (index < 0 || index >= count) {
			cout << "Invalid comment index!\n";
			return;
		}

		if (!comments[index].hostReply.empty()) {
			cout << "Already replied.\n";
		}
		else {
			cin.ignore();
			cout << "Enter your reply: ";
			getline(cin, comments[index].hostReply);

			cout << "Reply added successfully.\n";
			saveComments(comments, count);
		}

		while (true) {
			cout << "Do you want to continue replying? (Y/N): ";
			cin >> reply;

			if (reply == 'Y' || reply == 'y' || reply == 'N' || reply == 'n') {
				break;
			}
			else {
				cout << "Invalid input. Please enter Y or N.\n";
			}
		}
	}
}

//delete comment function
void deleteComment(Comment comments[], int& count) {
	if (count == 0) {
		cout << "No comments to delete.\n";
		return;
	}

	showAllComments(comments, count);

	int index;
	cout << "Enter the comment number to delete: ";
	cin >> index;

	if (index < 0 || index >= count) {
		cout << "Invalid comment index!\n";
		return;
	}

	cout << "\nWhat do you want to delete?\n";
	cout << "1. Entire comment\n";
	cout << "2. Host reply\n";
	cout << "3. Cancel\n";
	cout << "Choice: ";
	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		deleteEntireComment(comments, count, index);
		break;
	case 2:
		deleteHostReply(comments, count, index);
		break;
	case 3:
		cout << "Delete cancelled.\n";
		return;
	default:
		cout << "Invalid choice.\n";
		return;
	}
}
void deleteEntireComment(Comment comments[], int& count, int index) {
	for (int i = index; i < count - 1; i++) {
		comments[i] = comments[i + 1];
	}
	comments[count - 1] = {};
	count--;
	cout << "Comment deleted successfully.\n";
	saveComments(comments, count);
}
void deleteHostReply(Comment comments[], int count, int index) {
	if (!comments[index].hostReply.empty()) {
		comments[index].hostReply.clear();
		cout << "Host reply deleted successfully.\n";
		saveComments(comments, count);
	}
	else {
		cout << "This comment has no host reply.\n";
	}
}

void saveComments(Comment comments[], int count) {
	fstream file("Comments", ios::out);
	if (!file.is_open()) {
		cout << "Error saving comments.\n";
		return;
	}
	for (int i = 0; i < count; i++) {
		if (!comments[i].deleted) {

			file << comments[i].fromHost << endl;
			file << comments[i].studentID << endl;
			file << comments[i].text << endl;
			file << comments[i].hostReply << endl;
		}
	}
	file.close();
	cout << "Comments saved successfully." << endl;
}
void loadComments(Comment comments[], int& count) {
	fstream file("Comments", ios::in);
	if (!file.is_open()) {
		cout << "Starting fresh.\n";
		return;
	}

	string line;
	count = 0;
	while (getline(file, line)) {
		if (line.empty()) continue;
		comments[count].fromHost = (line == "1" || line == "true");

		if (!getline(file, comments[count].studentID)) break;
		if (!getline(file, comments[count].text)) break;
		if (!getline(file, comments[count].hostReply)) break;

		comments[count].deleted = false;
		count++;
		if (count >= MAX_COMMENTS) break;
	}

	file.close();
}

//Case 1 (for simulator)
void clipper()
{
	system("cls");
	float Vin, Vd, Vout;
	char polar, opt_clipper;

	cout << "\n        Positive clipper                                 Negative clipper           \n";

	cout << "   ------------------------------                   ------------------------------    \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   |                         -------                |                          -----  \n";
	cout << "   |                           / \\  Vd=0.7V        |                          \\  /   Vd\n";
	cout << "   |                          /   \\                |                           \\/   \n";
	cout << "  Vin                         -----                Vin                        ------- \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   -------------R load-----------                   -------------R load-----------    \n";
	cout << "         |                  |                                |             | \n";
	cout << "         |                  |                                |             | \n";
	cout << "         o                  o                                o             o \n";
	cout << "         -       Vout       +                                -     Vout    + \n\n";

	while (true)
	{
		do
		{
			cout << "Choose what you want to calculate for clipper: \nEnter '+' for positive\n'-' for negative\n'.' for return:\n";
			cin >> polar;

			if (polar != '+' && polar != '-' && polar != '.')
				cout << "INPUT ERROR! Enter '+', '-' or '.' !";

		} while (polar != '+' && polar != '-' && polar != '.');

		if (polar == '+')
		{
			cout << "\nPositive clipper. " << endl;
			cout << "Choose what you want to calculate: \n1.Vout (Positive half cycle)\n2.Vout (Negative half cycle):\n";
			cin >> opt_clipper;
			switch (opt_clipper)
			{
			case '1':
				cout << "\nDuring positive cycle, the diode is reverse biased.\n";
				cout << "Vd = Vin \n";

				cout << "Enter the value of Vin (in Volt): ";
				cin >> Vin;
				Vd = Vin;
				Vout = Vin - Vd;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vd = " << fixed << setprecision(2) << Vd << endl;
				cout << "Vout = Vin - Vd \n";
				cout << "Vout = " << fixed << setprecision(2) << Vout << endl;
				break;

			case '2':
				cout << "\nDuring negative cycle, the diode is forward biased.\n";
				cout << "Enter the value of Vin (in Volt): ";
				cin >> Vin;
				cout << "Enter the value of Vd (in Volt): ";
				cin >> Vd;
				Vout = -Vin + Vd;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vout = -Vin + Vd \n";
				cout << "Vout = " << fixed << setprecision(2) << Vout << endl;
				break;

			default:
				cout << "\nINPUT ERROR! Enter integer 1 or 2!" << endl;
			}
		}

		else if (polar == '-')
		{
			cout << "\nNegative clipper. " << endl;
			cout << "Choose what you want to calculate: \n1. Vout (Positive half cycle)\n2. Vout (Negative half cycle):\n";
			cin >> opt_clipper;
			switch (opt_clipper)
			{
			case '1':
				cout << "\nDuring the positive cycle, the diode is forward biased.\n";
				cout << "Enter the value of Vin (in Volt): ";
				cin >> Vin;

				cout << "Enter the value of Vd (in Volt): ";
				cin >> Vd;
				Vout = Vin - Vd;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vout = Vin - Vd\n";
				cout << "Vout = " << fixed << setprecision(2) << Vout << endl;
				break;

			case '2':
				cout << "\nDuring the negative cycle, the diode is reverse biased.\n";
				cout << "Vd = Vin \n";
				cout << "Enter the value of Vin (in Volt): ";
				cin >> Vin;
				Vd = Vin;
				Vout = Vin - Vd;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vd = " << fixed << setprecision(2) << Vd << endl;
				cout << "Vout = Vin - Vd \n";
				cout << "Vout = " << fixed << setprecision(2) << Vout << endl;
				break;

			default:
				cout << "\nINPUT ERROR! Enter integer 1 or 2!" << endl;
				break;
			}
		}

		else if (polar == '.')
		{
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;
		}

		else
			cout << "\nINPUT ERROR! Enter '+', '-' or '.' !" << endl;
	}
}

//Case 2 (for simulator)
void clamper()
{
	system("cls");
	float Vin, Vc, Vd, Vbias, Vout;
	char polar, opt_clamper;
	cout << "\n           Positive-biased clamper                                      Negative-biased clamper\n" << endl;
	cout << "   -------)|--------------------------------o +                -------|(--------------------------------o +\n";
	cout << "   |      Vc    |               |                              |      Vc    |               |\n";
	cout << "   |          -----             |                              |           ---              |\n";
	cout << "   |           / \\  Vd          |                              |           \\ /  Vd          |" << endl;
	cout << "   |           ---              |                              |          -----             |\n";
	cout << "  Vin           |               RL         Vout               Vin           |               RL         Vout\n";
	cout << "   |           ---              |                              |            -               |\n";
	cout << "   |            -               |                              |           ---              |\n";
	cout << "   |           ---              |                              |            -               |\n";
	cout << "   |            -               |                              |           ---              |\n";
	cout << "   |            |               |                              |            |               |\n";
	cout << "   -----------------------------------------o -                -----------------------------------------o -\n";
	cout << "\n           Positive clamper                                             Negative clamper\n" << endl;
	cout << "   -------)|--------------------------------o +                -------|(--------------------------------o +\n";
	cout << "   |      Vc    |               |                              |      Vc    |               |\n";
	cout << "   |          -----             |                              |           ---              |\n";
	cout << "   |           / \\  Vd          |                             |           \\ /  Vd         |" << endl;
	cout << "   |           ---              |                              |          -----             |\n";
	cout << "  Vin           |               RL         Vout               Vin           |               RL         Vout\n";
	cout << "   |            |               |                              |            |               |\n";
	cout << "   |            |               |                              |            |               |\n";
	cout << "   -----------------------------------------o -                -----------------------------------------o -\n";

	while (true)
	{
		do
		{
			cout << "Choose what you want to calculate for clamper: \nEnter '+' for positive\n'-' for negative\n'.' for return:\n";
			cin >> polar;
			if (polar != '+' && polar != '-' && polar != '.')
			{
				cout << "INPUT ERROR! Enter '+', '-' or '.' ! ";
			}
		} while (polar != '+' && polar != '-' && polar != '.');

		if (polar == '+')
		{
			cout << "Positive clamper." << endl;
			cout << "Choose what you want to calculate: \n1.Vc\n2.Vout(+ve half cycle)\n3.Vout(-ve half cycle):\n";
			cin >> opt_clamper;
			switch (opt_clamper)
			{
			case '1':
				cout << "Vc = Vin - Vd + Vbias" << endl;
				cout << "Enter the value of Vin (in Volt):";
				cin >> Vin;

				cout << "Enter the value of Vd (in Volt):";
				cin >> Vd;

				cout << "Enter the value of Vbias (add a negative sign, e.g., -2, if the polarity of the battery is opposite to Vout):";
				cin >> Vbias;

				Vc = Vin - Vd + Vbias;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vc = Vin - Vd + Vbias\n";
				cout << "Vc = " << fixed << setprecision(2) << Vc << "V" << endl;
				break;

			case '2':
				cout << "Vout(+ve half cycle) = Vc + Vin" << endl;
				cout << "Enter the value of Vc (in Volt):";
				cin >> Vc;
				cout << "Enter the value of Vin (in Volt):";
				cin >> Vin;
				Vout = Vc + Vin;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vout = Vc + Vin\n";
				cout << "Vout(+ve half cycle) = " << fixed << setprecision(2) << Vout << "V" << endl;
				break;

			case '3':
				cout << "Vout(-ve half cycle) = -Vd + Vbias" << endl;

				cout << "Enter the value of Vd (in Volt):";
				cin >> Vd;

				cout << "Enter the value of Vbias (in Volt) (add a negative sign, e.g., -2, if the polarity of the battery is opposite to Vout):";
				cin >> Vbias;
				Vout = -Vd + Vbias;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vout = -Vd + Vbias\n";
				cout << "Vout(-ve half cycle) = " << fixed << setprecision(2) << Vout << "V" << endl;
				break;

			default:
				cout << "INPUT ERROR! Enter integer 1,2 or 3!" << endl;

			}
		}
		else if (polar == '-')
		{
			cout << "Negative clamper." << endl;
			cout << "Choose what you want to calculate: \n1.Vc\n2.Vout(+ve half cycle)\n3.Vout(-ve half cycle):\n";
			cin >> opt_clamper;
			switch (opt_clamper)
			{
			case '1':
				cout << "Vc = Vin - Vd - Vbias" << endl;
				cout << "Enter the value of Vin (in Volt):";
				cin >> Vin;

				cout << "Enter the value of Vd (in Volt):";
				cin >> Vd;

				cout << "Enter the value of Vbias (in Volt) (add a negative sign, e.g., -2, if the polarity of the battery is opposite to Vout):";
				cin >> Vbias;

				Vc = Vin - Vd - Vbias;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vc = Vin - Vd - Vbias\n";
				cout << "Vc = " << fixed << setprecision(2) << Vc << "V" << endl;
				break;

			case '2':
				cout << "Vout(+ve half cycle) = Vd + Vbias" << endl;
				cout << "Enter the value of Vd (in Volt):";
				cin >> Vd;

				cout << "Enter the value of Vbias (in Volt) (add a negative sign, e.g., -2, if the polarity of the battery is opposite to Vout):";
				cin >> Vbias;

				Vout = Vd + Vbias;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Vout = Vd + Vbias\n";
				cout << "Vout(+ve half cycle) = " << fixed << setprecision(2) << Vout << "V" << endl;
				break;

			case '3':
				cout << "Vout(-ve half cycle) = -Vc - Vin" << endl;
				cout << "Enter the value of Vc (in Volt):";
				cin >> Vc;

				cout << "Enter the value of Vin (in Volt):";
				cin >> Vin;

				Vout = -Vc - Vin;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "	Vout = -Vc - Vin\n";
				cout << "Vout(-ve half cycle)= " << fixed << setprecision(2) << Vout << "V" << endl;
				break;

			default:
				cout << "INPUT ERROR! Enter integer 1,2 or 3!" << endl;
			}
		}

		else if (polar == '.')
		{
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;
		}

		else
			cout << "\nINPUT ERROR! Enter '+', '-' or '.' !" << endl;
	}
}

//Case 3 (for simulator)
void BJT_Voltage_divider()
{
	system("cls");
	char calculate;
	double RIN_base, betaDC, RE, R2, R2_total, R1, VCC, VB, IC_mA, RC, VCE;
	cout << "BJT volatge-divider biased configuration.\n\n";

	cout << "                       VCC\n";
	cout << "                        |\n";
	cout << "      ------------------|\n";
	cout << "      |                 RC\n";
	cout << "      |                 |\n";
	cout << "      R1                |\n";
	cout << "      |                /\n";
	cout << "      |             |\n";
	cout << "      --------------|\n";
	cout << "      |             |\n";
	cout << "      |                \\\n";
	cout << "      R2                 |\n";
	cout << "      |                  RE\n";
	cout << "      |                  |\n";
	cout << "      --------------------\n";
	cout << "               |\n";
	cout << "               |\n";
	cout << "              GND\n\n";

	while (true)
	{
		cout << "\nChoose what you want to calculate:\n";
		cout << "1. RIN_base and R2_total\n2. VB\n3. IC\n4. VCE\n5. return:\n";
		cin >> calculate;
		cout << endl;

		switch (calculate)
		{
		case '1':
			cout << "Enter the value of R2 (in Ohm): ";
			cin >> R2;

			cout << "Enter the value of RE (in Ohm): ";
			cin >> RE;

			cout << "Enter the value of betaDC: ";
			cin >> betaDC;

			RIN_base = betaDC * RE;

			if (RIN_base >= 10 * R2)
			{
				R2_total = R2;

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "R2_total = R2\n";
				cout << "The value of R2_total is " << fixed << setprecision(2) << R2_total << " Ohm.\n";
			}

			else
			{
				R2_total = 1.0 / ((1.0 / R2) + (1.0 / RIN_base));

				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "(RIN_base < 10 * R2), R2_total = 1.0 / ((1.0 / R2) + (1.0 / RIN_base))\n";
				cout << "The value of R2_total is " << fixed << setprecision(2) << R2_total << " Ohm.\n";
			}
			break;

		case '2':
			cout << "Enter the value of R1 (in Ohm): ";
			cin >> R1;

			cout << "Enter the value of R2_total (in Ohm): ";
			cin >> R2_total;

			cout << "Enter the value of VCC (in Volt): ";
			cin >> VCC;

			VB = R2_total / (R1 + R2_total) * VCC;

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "VB = R2_total / (R1 + R2_total) * VCC\n";
			cout << "The value of VB is " << fixed << setprecision(2) << VB << " V.\n";
			break;

		case '3':
			cout << "Enter the value of VB (in Volt): ";
			cin >> VB;

			cout << "Enter the value of RE (in Ohm): ";
			cin >> RE;

			IC_mA = (VB - 0.7) / RE; //note that the IC_mA at here is in A

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "IC = (VB - 0.7) / RE\n";
			cout << "The value of IC is " << fixed << setprecision(2) << IC_mA * 1000 << " mA.\n\n";
			break;

		case '4':
			cout << "Enter the value of VCC (in Volt): ";
			cin >> VCC;

			cout << "Enter the value of IC (in milli Ampere): ";
			cin >> IC_mA;

			cout << "Enter the value of RC (in Ohm): ";
			cin >> RC;

			cout << "Enter the value of RE (in Ohm): ";
			cin >> RE;

			VCE = VCC - (IC_mA / 1000 * (RC + RE));

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "VCE = VCC - IC * (RC + RE)\n";
			cout << "The value of VCE is " << fixed << setprecision(2) << VCE << " V\n\n";
			break;

		case '5':
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;

		default:
			cout << "INPUT ERROR! Enter integer 1,2,3,4 or 5!" << endl;
		}
	}
}

//Case 4 (for simulator)
void BJT_base()
{
	system("cls");
	char calculate;
	double VCC, IC_mA, RC, VCE;

	cout << "                       VCC\n";
	cout << "                        |\n";
	cout << "      ------------------|\n";
	cout << "      |                 RC \n";
	cout << "      |                 |\n";
	cout << "      |                 |\n";
	cout << "      |                /\n";
	cout << "      |             |\n";
	cout << "      ----- RB -----|\n";
	cout << "                    |\n";
	cout << "                       \\\n";
	cout << "                         |\n";
	cout << "                         |\n";
	cout << "                         |\n";
	cout << "                        GND\n\n";

	while (true)
	{
		cout << "\nChoose what you want to calculate:\n";
		cout << "1. VCE\n2. return:\n";
		cin >> calculate;
		cout << endl;

		switch (calculate)
		{
		case '1':
			cout << "Enter the value of VCC (in Volt): ";
			cin >> VCC;

			cout << "Enter the value of IC (in milli Ampere): ";
			cin >> IC_mA;

			cout << "Enter the value of RC (in Ohm): ";
			cin >> RC;

			VCE = VCC - (IC_mA / 1000 * RC);

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "VCE = VCC - (IC * RC)\n";
			cout << "The value for VCE is " << fixed << setprecision(2) << VCE << "V\n";
			break;

		case '2':
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;

		default:
			cout << "INPUT ERROR! Enter integer 1 or 2!" << endl;
		}
	}
}

//Case 5 (for simulator)
void BJT_AC()
{
	system("cls");
	char calculate;
	double R1, R2, VB, VCC, RC, RE, betaAC, Rin_base, Rin_total, IE_mA, re, AV;

	cout << "                                         VCC\n";
	cout << "                                          |\n";
	cout << "                        ------------------|\n";
	cout << "                        |                 RC\n";
	cout << "                        |                 |\n";
	cout << "                        R1                |-------C3---o---Vout\n";
	cout << "                        |                /\n";
	cout << "                        |              |\n";
	cout << " Vin ---o---RS---C1-----| -------------|\n";
	cout << "                        |              |\n";
	cout << "                        |                \\\n";
	cout << "                        R2                   |\n";
	cout << "                        |                    |\n";
	cout << "                        |                    |----------------\n";
	cout << "                        |                    RE               |\n";
	cout << "                        |                    |                C2\n";
	cout << "                        |                    |                |\n";
	cout << "                        --------------------------------------\n";
	cout << "                                             |\n";
	cout << "                                             |\n";
	cout << "                                            GND\n\n";
	cout << "                                         Figure 6\n\n\n";
	cout << " Hint: This is the Common-Emitter (CE) Amplifier with bypass capacitor (C2) in the emitter, "
		<< "without involving swapping process and no load resistance, RL.\n\n";

	while (true)
	{
		cout << "\nChoose what you want to calculate:\n";
		cout << "1. Rin_base\n2. Rin_total\n3. VB\n4. IE\n5. re\n6. AV\n7. return:\n";
		cin >> calculate;
		cout << endl;

		switch (calculate)
		{

		case '1':

			cout << "Enter the value of betaAC: ";
			cin >> betaAC;

			cout << "Enter the value of RE (in Ohm): ";
			cin >> RE;

			Rin_base = betaAC * RE;

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "Rin_base = betaAC * RE\n";
			cout << "The value for Rin_base is " << fixed << setprecision(2) << Rin_base << "Ohm\n";
			break;

		case '2':
			cout << "Enter the value of Rin_base (in Ohm): ";
			cin >> Rin_base;

			cout << "Enter the value of R1 (in Ohm): ";
			cin >> R1;

			cout << "Enter the value of R2 (in Ohm): ";
			cin >> R2;

			if (Rin_base >= 10 * R2)
			{
				Rin_total = 1.0 / ((1.0 / R1) + (1.0 / R2));
				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Rin_total = 1.0 / ((1.0 / R1) + (1.0 / R2))\n";
				cout << "The value for Rin_total is " << fixed << setprecision(2) << Rin_total << "Ohm\n";
			}

			else
			{
				Rin_total = 1.0 / ((1.0 / R1) + (1.0 / R2) + (1.0 / Rin_base));
				cout << endl << " Result " << endl;
				cout << "------------------------" << endl;
				cout << "Rin_total = 1.0 / ((1.0 / R1) + (1.0 / R2) + (1.0 / Rin_base))\n";
				cout << "The value for Rin_total is " << fixed << setprecision(2) << Rin_total << "Ohm\n";
			}
			break;

		case '3':
			cout << "Enter the value of R1(in Ohm): ";
			cin >> R1;

			cout << "Enter the value of R2(in Ohm): ";
			cin >> R2;

			cout << "Enter the value of VCC (in Volt): ";
			cin >> VCC;

			VB = R2 / (R1 + R2) * VCC;

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "VB = R2 / (R1 + R2) * VCC\n";
			cout << "The value for VB is " << fixed << setprecision(2) << VB << "V\n";
			break;

		case '4':
			cout << "Enter the value of VB (in Volt): ";
			cin >> VB;

			cout << "Enter the value of RE (in Ohm): ";
			cin >> RE;

			IE_mA = (VB - 0.7) / RE;

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "IE = (VB - 0.7) / RE\n";
			cout << "The value for IE is " << fixed << setprecision(2) << IE_mA * 1000 << "mA\n";
			break;

		case '5':
			cout << "Enter the value of IE (in milli Ampere): ";
			cin >> IE_mA;

			re = 0.026 / (IE_mA / 1000);

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "re = 0.026 / IE\n";
			cout << "The value for re is " << fixed << setprecision(2) << re << "Ohm\n";
			break;

		case '6':
			cout << "Enter the value of RC (in Ohm): ";
			cin >> RC;

			cout << "Enter the value of re (in Ohm): ";
			cin >> re;

			AV = -RC / re;

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "AV = -RC / re\n";
			cout << "The value of AV is " << fixed << setprecision(2) << AV << endl;
			break;

		case '7':
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;

		default:
			cout << "INPUT ERROR! Enter integer 1,2,3,4,5,6 or 7!" << endl;
		}
	}
}

//Case 6 (for simulator)
void jfet_DrainCurrent()
{
	system("cls");
	char option;
	float Idss, Vgs_off, Vgs, Id;
	float gm, gm_0;

	while (true)
	{
		cout << "Enter the calculator you want to use: \n1. drain current\n2. transconductance\n3. return:\n";
		cin >> option;
		switch (option)
		{
		case '1':
			cout << "\n Tips:To calculate drain current, the equation for JFET transfer characteristic was applied." << endl;
			cout << " _________________________________" << endl;
			cout << "| Id = Idss [1-(Vgs / Vgs_off)]^2 |" << endl;
			cout << " ---------------------------------" << endl;
			//key in data
			do
			{
				cout << "Enter your data to calculate the value" << endl;
				cout << "Idss (in milli Ampere) : ";
				cin >> Idss;

				cout << "Vgs_off (in Volt) [it should be a -ve Voltage]: ";
				cin >> Vgs_off;

				cout << "Vgs (in Volt) [it should be a -ve Voltage]    : ";
				cin >> Vgs;

				if (Vgs_off > 0 || Vgs > 0)
					cout << "Both Voltage should be a negative voltage." << endl
					<< "Please rekey the data." << endl;
			} while (Vgs_off > 0 || Vgs > 0);

			//calculation
			Id = Idss * (1 - (Vgs / Vgs_off)) * (1 - (Vgs / Vgs_off));

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "Id = Idss * (1 - (Vgs / Vgs_off)) * (1 - (Vgs / Vgs_off))\n";
			cout << "Id = " << Id << " mili-ampere." << endl << endl;
			break;

		case '2':
			cout << "\n Tips:Equation for forward transconductance, which is the slope of the transconductance curve." << endl;
			cout << " ____________________________" << endl;
			cout << "| gm = gm_0[1-(Vgs/Vgs_off)] |" << endl;
			cout << " ----------------------------" << endl;

			//key in data
			do
			{
				cout << "Enter your data to calculate the value" << endl;
				cout << "gm_0 (in micro_Siemens) : ";
				cin >> gm_0;

				cout << "Vgs_off (in Volt) [it should be a -ve Voltage]: ";
				cin >> Vgs_off;

				cout << "Vgs (in Volt) [it should be a -ve Voltage]    : ";
				cin >> Vgs;

				if (Vgs_off > 0 || Vgs > 0)
					cout << "Both Voltage should be a negative voltage." << endl
					<< "Please rekey the data." << endl;

			} while (Vgs_off > 0 || Vgs > 0);

			//calculation
			gm = gm_0 * (1 - (Vgs / Vgs_off));

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "gm = gm_0 * (1 - (Vgs / Vgs_off))";
			cout << "gm = " << gm << " micro-Siemens ." << endl << endl;
			break;

		case '3':
		{
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;
		}

		default:
			cout << "INPUT ERROR! Enter integer 1,2 or 3!" << endl;
		}
	}
}

//Case 7 (for simulator)
void jfet()
{
	system("cls");
	char option;
	float Id, Vdd, Rg, Rd, Rs;  //for jFET

	cout << "\n________________________________________" << endl;
	cout << "n-channel JFET self biased configuration" << endl;
	cout << "----------------------------------------" << endl << endl;
	cout << "Verify each values according to the cicuit in figure shown:" << endl << endl;
	cout << "                Vdd" << endl;
	cout << "                 |    | Id" << endl;
	cout << "                 Rd   v" << endl;
	cout << "                 |" << endl;
	cout << "                 | " << endl;
	cout << "                 D" << endl;
	cout << "                /" << endl;
	cout << "   ----G----> JFET" << endl;
	cout << "   |            \\" << endl;
	cout << "   |             S" << endl;
	cout << "   Rg            |" << endl;
	cout << "   |             Rs" << endl;
	cout << "   |             |" << endl;
	cout << "  GND           GND" << endl;
	cout << "_________________________________________________________________" << endl << endl;

	while (true)
	{
		cout << "Enter the calculator you want to use: \n1. drain-source voltage\n2. return:\n";
		cin >> option;
		switch (option)
		{
		case '1':
		{
			//key in data
			cout << "Vdd (in Volt): ";
			cin >> Vdd;
			cout << "Rd (in Ohm): ";
			cin >> Rd;
			cout << "Rs (in Ohm): ";
			cin >> Rs;
			cout << "Rg (in mega Ohm): ";
			cin >> Rg;
			cout << "Id (in milli Ampere): ";
			cin >> Id;

			// calculation
			Id /= 1000; // convert Id from milli Ampere to amperes
			cout << endl << " Result and calculation" << endl;
			cout << "------------------------" << endl;
			cout << "VGS = VG - VS, VG = 0" << endl;
			cout << "    = 0 - Id * Rs" << endl;
			cout << "    = " << -Id * Rs << " V" << endl << endl;

			cout << "VDS = VD - VS" << endl;
			cout << "    = Vdd - Id (Rd + Rs)" << endl;
			cout << "    = " << Vdd - Id * (Rd + Rs) << " V" << endl << endl;
			break;
		}

		case '2':
		{
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;
		}

		default:
			cout << "INPUT ERROR! Enter integer 1 or 2!" << endl;
		}

	}
}

//Case 8 (for simulator)
void mosfet()
{
	system("cls");
	char option;
	float Id, Vdd, R1, R2, R12, Rd, Vgs_th, K;  //for MOSFET

	cout << "\n_________________________________________________________" << endl;
	cout << " N-channel E-MOSFET Voltage divider biased configuration" << endl;
	cout << "---------------------------------------------------------" << endl << endl;
	cout << "Verify each values according to the cicuit in figure shown:" << endl << endl;
	cout << "                Vdd" << endl;
	cout << "   --------------|" << endl;
	cout << "   |             |   | Id " << endl;
	cout << "   R1            Rd  V" << endl;
	cout << "   |             | " << endl;
	cout << "   |             D" << endl;
	cout << "   |            /" << endl;
	cout << "   ----G----E_MOSFET" << endl;
	cout << "   |            \\" << endl;
	cout << "   |             S" << endl;
	cout << "   |             |" << endl;
	cout << "   R2            |" << endl;
	cout << "   |             |" << endl;
	cout << "  GND           GND" << endl;
	cout << "_________________________________________________________________" << endl << endl;

	while (true)
	{
		cout << "Enter the calculator you want to use: \n1. drain-source voltage\n2. return:\n";
		cin >> option;
		switch (option)
		{
		case '1':
		{
			//key in data
			cout << "Vdd (in Volt): ";
			cin >> Vdd;
			cout << "Rd (in Ohm): ";
			cin >> Rd;
			cout << "R1 (in kilo Ohm): ";
			cin >> R1;
			cout << "R2 (in kilo Ohm): ";
			cin >> R2;
			cout << "The thereshold Voltage Vgs_th (in Volt): ";
			cin >> Vgs_th;
			cout << "The devices pameter K (in milli Ampere/Volt^2): ";
			cin >> K;

			// calculation
			R12 = R2 / (R1 + R2);
			K /= 1000; // convert K from mA/V^2 to A/V^2
			Id = K * (R12 * Vdd - Vgs_th); // Id in ampere

			cout << endl << " Result and calculation" << endl;
			cout << "------------------------" << endl;
			cout << "VGS = [R2 / (R1+R2)] * Vdd" << endl;
			cout << "    = " << R12 << " * " << Vdd << endl;
			cout << "    = " << R12 * Vdd << " V" << endl << endl;
			cout << "Id = K *( Vgs - Vgs_th)^2" << endl;
			cout << "   = " << K << " * ( " << R12 * Vdd << " - " << Vgs_th << " )^2" << endl;
			cout << "   = " << K * pow((R12 * Vdd - Vgs_th), 2) * 1000 << " mA" << endl << endl;
			cout << "VDS = V_D - V_S" << endl;
			cout << "    = Vdd - (Id * Rd)" << endl;
			cout << "    = " << Vdd - (Id * Rd) << " V" << endl << endl;
			break;
		}

		case '2':
		{
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;
		}
		default:
			cout << "INPUT ERROR! Enter integer 1 or 2!" << endl;
		}
	}
}

//Case 9 (for simulator)
void non_inverting()
{
	system("cls");
	double Rf_NI, Ri_NI, Vin, Aol, Zin_NI, Zout_NI, Acl_NI, B, Zin, Zout;
	char opt;

	cout << "\n---Non-Inverting Amplifier,NI---\n";
	cout << "Circuit Diagram: \n";
	cout << "                                       \n";
	cout << "                |\\                    \n";
	cout << "                | \\                   \n";
	cout << " Vin (+)------->|+ \\                  \n";
	cout << "                |   \\_____________Vout\n";
	cout << "                |   /        |         \n";
	cout << "        ------->|- /         |         \n";
	cout << "        |       | /          Rf        \n";
	cout << "        |       |/           |         \n";
	cout << "        |____________________|         \n";
	cout << "                             |         \n";
	cout << "                             |         \n";
	cout << "                             Ri        \n";
	cout << "                             |         \n";
	cout << "                            GND        \n";
	cout << "                                       \n";
	cout << "Given:Vin = 5.0V, Rf = 220000 Ohm,Ri = 10000 Ohm and Aol = 200000 , Zin = 2000000 Ohm, Zout = 75 Ohm.\n";
	cout << "Determine the cloosed-loop Voltage gain,Acl, the input and output impedances of the amplifier.\n";

	while (true)
	{
		cout << "\nFormula Option:\n";
		cout << "1. Acl(NI) = 1 + (Rf/Ri) \n";
		cout << "2.  B = Ri / (Ri + Rf)\n";
		cout << "3. Zin(NI) = (1+ Aol*B) * Zin\n";
		cout << "4. Zout(NI) =  Zout / (1 + Aol * B)\n";
		cout << "5. Return.\n";
		cout << "Enter your choice (1-5):\n";
		cin >> opt;

		if (opt == '1')
		{
			cout << "1. Acl(NI) = 1 + (Rf/Ri) \n";
			cout << "Enter the value of Rf (in Ohm): \n";
			cin >> Rf_NI;
			cout << "Enter the value of Ri (in Ohm): \n";
			cin >> Ri_NI;
			Acl_NI = 1 + (Rf_NI / Ri_NI);

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "Acl(NI) = 1 + (Rf/Ri)\n";
			cout << "Acl(NI) = " << fixed << setprecision(2) << Acl_NI << endl;
		}

		else if (opt == '2')
		{
			cout << "2. B = Ri / (Ri + Rf)\n";
			cout << "Enter the value of Rf (in Ohm): \n";
			cin >> Rf_NI;
			cout << "Enter the value of Ri (in Ohm): \n";
			cin >> Ri_NI;
			B = Ri_NI / (Ri_NI + Rf_NI);

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "B = Ri_NI / (Ri_NI + Rf_NI)\n";
			cout << "B = " << fixed << setprecision(4) << B << endl;
		}
		else if (opt == '3')
		{
			cout << "3. Zin(NI) = (1+ Aol*B) * Zin\n";
			cout << "Enter the value of B : \n";
			cin >> B;
			cout << "Enter the value of Aol : \n";
			cin >> Aol;
			cout << "Enter the value of Zin (in Ohm): \n";
			cin >> Zin;
			Zin_NI = (1 + Aol * B) * Zin;

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "Zin_NI = (1 + Aol * B) * Zin\n";
			cout << "Zin(NI) = " << fixed << setprecision(2) << Zin_NI << " Ohm" << endl;
		}

		else if (opt == '4')
		{
			cout << "4.Zout(NI) =  Zout / (1 + Aol * B)\n";
			cout << "Enter the value of Zout (in Ohm): \n";
			cin >> Zout;
			cout << "Enter the value of Aol: \n";
			cin >> Aol;
			cout << "Enter the value of B: \n";
			cin >> B;
			Zout_NI = Zout / (1 + Aol * B);

			cout << endl << " Result " << endl;
			cout << "------------------------" << endl;
			cout << "Zout_NI = Zout / (1 + Aol * B)\n";
			cout << "Zout(NI) = " << fixed << setprecision(2) << Zout_NI << " Ohm " << endl;
		}

		else if (opt == '5')
		{
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;
		}
		else
		{
			cout << "INPUT ERROR! Enter integer 1,2,3,4 or 5!" << endl;
		}
	}
}

//Case 10 (for simulator)
void VoltageFollower()
{
	system("cls");
	char opt;
	double Rf_VF, Ri_VF, Aol, Zin_VF, Zout_VF, B, Zin, Zout;

	cout << "\n---Voltage Follower,VF---\n";
	cout << "Circuit Diagram: \n";
	cout << "                                       \n";
	cout << "                |\\                    \n";
	cout << "                | \\                   \n";
	cout << " Vin (~)------->|+ \\                  \n";
	cout << "  |             |   \\_____________Vout\n";
	cout << "  GND           |   /        |         \n";
	cout << "        ------->|- /         |         \n";
	cout << "        |       | /          Rf        \n";
	cout << "        |       |/           |         \n";
	cout << "        |____________________|         \n";
	cout << "                             |         \n";
	cout << "                             |         \n";
	cout << "                             Ri        \n";
	cout << "                             |         \n";
	cout << "                            GND        \n";
	cout << "                                       \n";
	cout << "Given: Rf =230000 Ohm, Ri =10000 Ohm , Aol = 200000 , Zin = 1000000 Ohm, Zout = 70 Ohm and B = 1.\n";
	cout << "Determine the input and output impedances of the amplifier.\n";

	while (true)
	{
		cout << "\nFormula Option:\n";
		cout << "1. Zin(VF) = (1+ Aol*B) * Zin\n";
		cout << "2. Zout(VF) =  Zout / (1 + Aol)\n";
		cout << "3. Return.\n";
		cout << "Enter your choice (1-3):\n";
		cin >> opt;

		if (opt == '1')
		{
			cout << "1. Zin(VF) = (1+ Aol*B) * Zin\n";
			cout << "Enter the value of B: \n";
			cin >> B;
			cout << "Enter the value of Aol: \n";
			cin >> Aol;
			cout << "Enter the value of Zin (in Ohm): \n";
			cin >> Zin;
			Zin_VF = (1 + Aol * B) * Zin;

			cout << "Zin_VF = (1 + Aol * B) * Zin\n";
			cout << "Zin(VF) = " << fixed << setprecision(2) << Zin_VF << " Ohm" << endl;
		}

		else if (opt == '2')
		{
			cout << "2.Zout(VF) =  Zout / (1 + Aol)\n";
			cout << "Enter the value of Zout (in Ohm): \n";
			cin >> Zout;
			cout << "Enter the value of Aol: \n";
			cin >> Aol;
			Zout_VF = Zout / (1 + Aol);

			cout << "Zout_VF = Zout / (1 + Aol)\n";
			cout << "Zout(VF) = " << fixed << setprecision(2) << Zout_VF << " Ohm" << endl;
		}
		else if (opt == '3')
		{
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;
		}

		else
		{
			cout << "INPUT ERROR! Enter integer 1,2 or 3!" << endl;
		}
	}
}

//Case 11 (for simulator)
void invertingAmplifier()
{
	system("cls");
	char opt;
	double Rf_I, Ri_I, Acl_I;

	cout << "\n---Inverting Amplifier,I---\n";
	cout << "Circuit Diagram: \n";
	cout << "                                               \n";
	cout << "                    _______Rf_______          \n";
	cout << "                   |                |          \n";
	cout << "                   |                |          \n";
	cout << "                   |    |\\         |          \n";
	cout << "                   |    | \\        |          \n";
	cout << " Vin (~)------Ri------->|+ \\       |          \n";
	cout << "                        |   \\______|____Vout  \n";
	cout << "                        |   /                  \n";
	cout << "                ------->|- /                   \n";
	cout << "                |       | /                    \n";
	cout << "                |       |/                     \n";
	cout << "               GND                             \n";
	cout << "                                               \n";
	cout << "Given: Rf =210000 Ohm, Ri =10000 Ohm.\n";
	cout << "Determine the closed-loop Voltage gain,Acl and the input impedance of the amplifier.\n";

	while (true)
	{
		cout << "\nFormula Option:\n";
		cout << "1. Acl(I)= - (Rf/Ri)\n";
		cout << "2. Zin(I) = Ri \n";
		cout << "3. Return.\n";
		cout << "Enter your choice (1-3):\n";
		cin >> opt;

		if (opt == '1')
		{
			cout << "1. Acl(I)= - (Rf/Ri)\n";
			cout << "Enter the value of Rf (in Ohm): \n";
			cin >> Rf_I;
			cout << "Enter the value of Ri (in Ohm): \n";
			cin >> Ri_I;
			Acl_I = -(Rf_I / Ri_I);

			cout << "Acl_I = -(Rf_I / Ri_I)\n";
			cout << "Acl(I) = " << fixed << setprecision(2) << Acl_I << endl;
		}
		else if (opt == '2')
		{
			cout << "2. Zin(I) = Ri \n";
			cout << "Enter the value of Ri: \n";
			cin >> Ri_I;

			cout << "Zin(I) = Ri\n";
			cout << "Zin(I) = " << fixed << setprecision(2) << Ri_I << " Ohm" << endl;
		}

		else if (opt == '3')
		{
			cout << "Return to simulation option...\n";
			Sleep(1000);
			return;
		}

		else
		{
			cout << "INPUT ERROR! Enter integer 1,2 or 3!" << endl;
		}
	}
}

void notes_Diode()
{
	system("cls");
	cout << "\n-----------------------------------------------------------\n";
	cout << "| Chapter 1: Diodes                                       |\n";
	cout << "-----------------------------------------------------------\n\n";

	cout << "1.0 Introduction:" << endl;
	cout << "=================" << endl;
	cout << "Materials can be classified by their electrical properties into insulators, conductors and semiconductors." << endl;
	cout << "Insulators do not conduct electricity, conductors do conduct electricity and semiconductors "
		<< "are in between conductors and insulators in their ability to conduct electricity." << endl;

	cout << "There are two types of semiconductor structures: intrinsic and extrinsic." << endl;
	cout << "Intrinsic semiconductors are pure, while extrinsic semiconductors are doped with impurities." << endl;
	cout << "Extrinsic semiconductors are semiconductors that have gone through the doping process, "
		<< "which increases the conductivity of pure semiconductors by adding impurities." << endl;
	cout << "This process gives rise to n-type and p-type semiconductors." << endl;
	cout << "P-type has holes as the majority carriers, while n-type has electrons as the majority carriers." << endl;
	cout << "Putting these two materials together forms a pn junction at the boundary, which is the basis of what a diode is." << endl;

	cout << "A depletion region will be formed until equilibrium is established." << endl;
	cout << "Once achieved, a barrier potential is formed that repels further diffusion." << endl;
	cout << "Biasing means applying a potential across the pn junction to control the width of the depletion layer." << endl;

	cout << "There are two types of bias: forward bias and reverse bias." << endl;
	cout << "A pn junction is forward biased when the n-type is more negative than the p-type." << endl;
	cout << "The pn junction begins to conduct when the forward voltage is greater than the barrier potential." << endl;
	cout << "Reverse bias is when the n-type is more positive than the p-type. " << endl;
	cout << "In this condition, charges move away from the junction." << endl << endl;

	cin.ignore();
	waitEnter("continue");

	system("cls");
	cout << "\n1.1 PN Junction Diode" << endl;
	cout << "======================" << endl;
	cout << "A diode conducts when it is forward biased and the forward voltage, Vf, is greater than the barrier potential, Vb." << endl;
	cout << "There are three diode models: ideal model, practical model and complete model." << endl;

	cout << "\n1.1.a <The Ideal Model>:" << endl;
	cout << "The diode is represented as a switch: closed (forward bias) and open (reverse bias)." << endl;
	cout << "In forward bias, the diode has no resistance and acts as a short circuit, so there is no voltage drop across it." << endl;
	cout << "In reverse bias, the diode has infinite resistance and acts as an open circuit, so the entire voltage drops across it." << endl;

	cout << "\n1.1.b <The Practical Model>:" << endl;
	cout << "The model includes characteristics such as forward voltage Vf, peak reverse voltage Vrrm, average forward current Io, "
		<< "and forward power dissipation Pd(max)." << endl;
	cout << "Forward voltage is the voltage at which the forward current suddenly rises, approximately 0.7V for silicon diodes." << endl;
	cout << "Hence, voltage drop across the remaining components = Vin - 0.7V." << endl;
	cout << "When the diode is reverse-biased, the maximum reverse voltage that will not force conduction is called Vrrm." << endl;
	cout << "Vrrm = 1.2 * (Peak reverse voltage)." << endl;
	cout << "If a diode conducts significantly in the reverse direction, the device will be destroyed." << endl;
	cout << "Average forward current indicates the maximum allowable dc forward current ? 120% of rated forward current." << endl;
	cout << "Forward power dissipation, Pd(max), indicates the maximum power of diode operation in forward bias." << endl;

	cout << "\n1.1.c <The Complete Model>:" << endl;
	cout << "The complete diode model includes bulk resistance and reverse current." << endl;
	cout << "Bulk resistance is the natural resistance of the materials that make up the pn junction." << endl;
	cout << "Bulk resistance and barrier potential are only taken into account during forward bias operation." << endl;
	cout << "Forward voltage Vf = Barrier potential + (Forward current * Bulk resistance) = Vb + If * Rb." << endl << endl;
	waitEnter("continue");

	system("cls");
	cout << "\n1.2 Diode Applications" << endl;
	cout << "=======================" << endl;

	cout << "1.2.a <Clippers>" << endl;
	cout << "A clipper (limiter) is a diode circuit that is used to eliminate some portion of a waveform." << endl;
	cout << "There are two types of clippers: series and shunt clippers." << endl;
	cout << "Series clippers are connected in series with the load and provide an output when forward biased." << endl;

	// ASCII diagrams kept exactly the same ?
	cout << "\n        Positive clipper                                 Negative clipper           \n";
	cout << "   ------------------------------                   ------------------------------    \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   |                         -------                |                          -----  \n";
	cout << "   |                           / \\  Vd=0.7V        |                          \\  /   Vd\n";
	cout << "   |                          /   \\                |                           \\/   \n";
	cout << "  Vin                         -----                Vin                        ------- \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   |                            |                   |                            |    \n";
	cout << "   -------------R load-----------                   -------------R load-----------    \n";
	cout << "         |                  |                                |             | \n";
	cout << "         |                  |                                |             | \n";
	cout << "         o                  o                                o             o \n";
	cout << "         -       Vout       +                                -    Vout     + \n\n";

	cout << "For a positive series clipper: in forward bias, Vload = -Vin + 0.7V." << endl;
	cout << "In reverse bias, Vdiode = Vin." << endl;
	cout << "For a negative series clipper: in forward bias, Vload = Vin - 0.7V." << endl;
	cout << "In reverse bias, Vdiode = -Vin." << endl;

	cout << "\nShunt clippers are connected parallel to the load and provide an output when forward biased." << endl;
	cout << "\n        Negative clipper                                 Positive clipper           \n";

	cout << " -----------------------------------------o+    -----------------------------------------o+   \n";
	cout << " |                    |              |          |                     |            |\n";
	cout << " |                 -------           |          |                   -----          |\n";
	cout << " |                   / \\  Vd=0.7V   |          |                   \\  /   Vd     |\n";
	cout << " |                  /   \\           |          |                    \\/           |\n";
	cout << "Vin                 -----        R load         Vin                -------         |\n";
	cout << " |                    |              |          |                     |          R load \n";
	cout << " |                    |              |          |                     |            |\n";
	cout << " |                    |              |          |                     |            |\n";
	cout << " |                    |              | Vout     |                     |            |   Vout \n";
	cout << " ---------------R1-------------------------o-   ----------------R1-----------------------o-\n\n";

	cout << "For a negative shunt clipper: during reverse bias, Vload = Vin * (Rload || R1)." << endl;
	cout << "During forward bias, Vload = -0.7V." << endl;
	cout << "For a positive shunt clipper: during reverse bias, Vload = -Vin * (Rload || R1)." << endl;
	cout << "During forward bias, Vload = 0.7V." << endl;
	cout << "Note: R1 must be much smaller than Rload to ensure that most of the voltage drops across Rload." << endl << endl;
	waitEnter("continue");

	system("cls");
	cout << "1.2.b <Clamper circuit (DC Restorer)>" << endl;
	cout << "=====================================" << endl;
	cout << "A clamper circuit is used to shift a waveform either above or below a reference voltage without distorting its shape." << endl;
	cout << "There are positive clampers and negative clampers." << endl;
	cout << "A positive clamper shifts the input waveform so that its negative peak is approximately equal to the clamper's DC reference voltage." << endl << endl;

	cout << "\n           Positive clamper                                       Negative clamper\n" << endl;
	cout << "   -------)|--------------------------------o +           -------|(--------------------------------o +\n";
	cout << "   |      Vc    |               |                         |      Vc    |               |\n";
	cout << "   |          -----             |                         |           ---              |\n";
	cout << "   |           / \\  Vd          |                         |           \\ /  Vd         | \n";
	cout << "   |           ---              |                         |          -----             |\n";
	cout << "  Vin           |               RL         Vout          Vin           |               RL         Vout\n";
	cout << "   |            |               |                         |            |               |\n";
	cout << "   |            |               |                         |            |               |\n";
	cout << "   -----------------------------------------o -           -----------------------------------------o -\n\n";

	cout << "For clamper circuits, Vload is the sum of the source voltage and the capacitor voltage." << endl;
	cout << "For the positive clamper: during the negative half cycle, the diode is forward biased. " << endl;
	cout << "The capacitor is charged during this cycle." << endl;
	cout << "A capacitor with a low charge time and high discharge time must be chosen." << endl;
	cout << "During the positive half cycle, the diode is reverse biased (assuming a practical diode)." << endl;
	cout << "The capacitor voltage is approximately Vc = Vin - 0.7V." << endl;
	cout << "Hence, during the positive cycle, Vload = Vin + Vc." << endl;
	cout << "For the negative clamper: during the positive half cycle, the diode is forward biased." << endl;
	cout << "The capacitor is charged during this cycle, with Vc = Vin - 0.7V." << endl;
	cout << "During the negative half cycle, the diode is reverse biased." << endl;
	cout << "Vload = -(Vc + Vin)." << endl;

	cout << "\nCongrats!! You are done reading the notes on Chapter 1: Diodes." << endl;
	waitEnter("return notes selection");
	system("cls");
}

// note for chapter 2
void notes_BJT()
{
	char study_analysis;
	system("cls");
	cout << "\n-----------------------------------------------------------\n";
	cout << "| Chapter 2: Bipolar Junction Transistor                  |\n";
	cout << "-----------------------------------------------------------\n\n";

	cout << "A Bipolar Junction Transistor (BJT) is a three-terminal device whose output current, voltage, and power are controlled by its input current.\n";
	cout << "It is a current-controlled device.\n";
	cout << "The main applications are amplifier and switch.\n\n";

	cout << "There are two types of BJTs:\n\n";

	cout << "Type 1: PNP BJT (arrow points inward).\n";
	cout << "                        |\n";
	cout << "                        |\n";
	cout << "                    Collector\n";
	cout << "                        |\n";
	cout << "                        |\n";
	cout << "                     |\n";
	cout << "     -----Base-------<|\n"; // PNP emitter arrow points in
	cout << "                     |\n";
	cout << "                        |\n";
	cout << "                        |\n";
	cout << "                    Emitter\n";
	cout << "                        |\n";
	cout << "                        |\n\n";

	cout << "Type 2: NPN BJT (arrow points outward).\n";
	cout << "                        |\n";
	cout << "                        |\n";
	cout << "                    Collector\n";
	cout << "                        |\n";
	cout << "                        |\n";
	cout << "                     |\n";
	cout << "     -----Base-------|>\n";// NPN emitter arrow points out
	cout << "                     |\n";
	cout << "                        |\n";
	cout << "                        |\n";
	cout << "                    Emitter\n";
	cout << "                        |\n";
	cout << "                        |\n\n";

	cout << "PNP BJTs are often used in calculations and practical applications.\n\n";


	cout << "*Note 1: In a BJT, VBE = 0.7V is because the base - emitter junction of the transistor is forward biased.\n";
	cout << " The 0.7 V is required to overcome the potential barrier (depletion region) of the PN junction.\n";

	cout << "*Note 2: In a BJT, the emitter current is given by IE = IC + IB.\n";
	cout << " Since the base current IB is very small compared to the collector current IC(due to the large current gain beta), it is often neglected.\n";
	cout << " Therefore, IC is assumed to be approximately equal to IE.\n";
	cin.ignore();
	waitEnter("continue");
	do //if study_analysis not equal to 'Q', it will run this part again
	{
		cout << "Enter your choice of study (A for AC analysis, D for DC analysis, Q for quit):";
		cin >> study_analysis;
		study_analysis = toupper(study_analysis);
		cout << endl;

		if (study_analysis == 'A')
		{
			system("cls");
			cout << "AC analysis\n";
			cout << "===========\n";
			cout << "To analyze the ac operation of the amplifier in common emitter, we develop an ac equivalent circuit based on the following rules: \n";
			cout << "1) Short all capacitors because we assume that their reactance XC = 0 at the signal frequency.\n";
			cout << "2) Replace all dc sources with a ground symbol.\n\n";

			cout << "There are 4 cases of Common-Emitter (CE) Amplifier.\n\n";

			cout << "Case 1: \n";

			cout << "                                         VCC\n";
			cout << "                                          |\n";
			cout << "                        ------------------|\n";
			cout << "                        |                 RC\n";
			cout << "                        |                 |\n";
			cout << "                        R1                |-------C3---o---Vout\n";
			cout << "                        |                /\n";
			cout << "                        |              |\n";
			cout << "      Vin ---o---C1-----| -------------|\n";
			cout << "                        |              |\n";
			cout << "                        |                \\\n";
			cout << "                        R2                   |\n";
			cout << "                        |                    |\n";
			cout << "                        |                   RE1\n";
			cout << "                        |                    |\n";
			cout << "                        |                    |--------\n";
			cout << "                        |                   RE2      |\n";
			cout << "                        |                    |       C2\n";
			cout << "                        |                    |       |\n";
			cout << "                        ------------------------------\n";
			cout << "                                      |\n";
			cout << "                                      |\n";
			cout << "                                     GND\n\n";

			cout << "This is the Common-Emitter (CE) Amplifier with bypass capacitor (C2) in the emitter, involving swapping process.\n\n";

			cout << "Case 2: \n";

			cout << "                                         VCC\n";
			cout << "                                          |\n";
			cout << "                        ------------------|\n";
			cout << "                        |                 RC\n";
			cout << "                        |                 |\n";
			cout << "                        R1                |-------C3---o---Vout-----\n";
			cout << "                        |                /                          |\n";
			cout << "                        |              |                            |\n";
			cout << "      Vin ---o---C1-----| -------------|                            |\n";
			cout << "                        |              |                            |\n";
			cout << "                        |                \\                         |\n";
			cout << "                        R2                   |                      RL\n";
			cout << "                        |                    |--------              |\n";
			cout << "                        |                    RE      |              |\n";
			cout << "                        |                    |       C2             |\n";
			cout << "                        |                    |       |              |\n";
			cout << "                        --------------------------------------------\n";
			cout << "                                             |\n";
			cout << "                                             |\n";
			cout << "                                            GND\n\n";

			cout << "This is the Common-Emitter (CE) Amplifier with bypass capacitor (C2) in the emitter, with a load resistance.\n\n";

			cout << "Case 3: \n";

			cout << "                                         VCC\n";
			cout << "                                          |\n";
			cout << "                        ------------------|\n";
			cout << "                        |                 RC\n";
			cout << "                        |                 |\n";
			cout << "                        R1                |-------C3---o---Vout\n";
			cout << "                        |                /\n";
			cout << "                        |              |\n";
			cout << "      Vin ---o---C1-----| -------------|\n";
			cout << "                        |              |\n";
			cout << "                        |                \\\n";
			cout << "                        R2                   |\n";
			cout << "                        |                    |\n";
			cout << "                        |                    |--------\n";
			cout << "                        |                    RE      |\n";
			cout << "                        |                    |       C2\n";
			cout << "                        |                    |       |\n";
			cout << "                        ------------------------------\n";
			cout << "                                      |\n";
			cout << "                                      |\n";
			cout << "                                     GND\n\n";

			cout << "This is the Common-Emitter (CE) Amplifier with bypass capacitor (C2) in the emitter, without involving swapping process and no load resistance, RL.\n\n";

			cout << "Case 4: \n";

			cout << "                                         VCC\n";
			cout << "                                          |\n";
			cout << "                        ------------------|\n";
			cout << "                        |                 RC\n";
			cout << "                        |                 |\n";
			cout << "                        R1                |-------C3---o---Vout\n";
			cout << "                        |                /\n";
			cout << "                        |              |\n";
			cout << "      Vin ---o---C1-----| -------------|\n";
			cout << "                        |              |\n";
			cout << "                        |                \\\n";
			cout << "                        R2                   |\n";
			cout << "                        |                    |\n";
			cout << "                        |                    |\n";
			cout << "                        |                    RE\n";
			cout << "                        |                    |\n";
			cout << "                        |                    |\n";
			cout << "                        ---------------------\n";
			cout << "                                  |\n";
			cout << "                                  |\n";
			cout << "                                 GND\n\n";

			cout << "This is the Common-Emitter (CE) Amplifier without bypass capacitor (C2) in the emitter, not involving swapping process and no load resistance, RL.\n\n";


			cout << "There are 10 equations for the Common-Emitter (CE) Amplifier in AC analysis.\n";
			cout << "All equations are expressed in terms of voltage (V), current (A), and resistance (ohm), instead of using prefixes such as milli (m) or kilo (k).\n\n";

			cout << "[Equation 1 (for finding AC emitter resistance, re)]: re = 25mV / IE ";
			cout << ",where IE = (VB - VBE) / RE\n\n\n";

			cout << "[Equation 2 (for finding input resistance at the base, Rin_base)]: Rin_base = betaAC * re\n\n\n";

			cout << "[Equation 3 (for finding the total input resistance of the amplifier, Rin_total)]:\n";
			cout << "\tCase 1: If Rin_base >= 10R2, Rin_total = 1 / ((1 / R1) + (1 / R2))\n";
			cout << "\tCase 2: If Rin_base < 10R2, Rin_total = 1 / ((1 / R1) + (1 / R2) + (1 / Rin_base))\n\n\n";

			cout << "[Equation 4 (for finding base voltage, VB)]: VB = Rin_total * VCC\n\n\n";

			cout << "[Equation 5 (for finding voltage gain, AV)]:\n";
			cout << "\tCase 1: With bypass capacitor (C2) in the emitter, involving swapping process and RE1 > 10re, AV = - RC / RE1\n";
			cout << "\tCase 2: With bypass capacitor (C2) in the emitter, involving swapping process and RE1 < 10re, AV = - RC / (re + RE1)\n";
			cout << "\tCase 3: With bypass capacitor (C2) in the emitter, with a load resistance: RC_total = 1 / ((1 / RC) + (1 / RL)), AV = - RC_total / re\n";
			cout << "\tCase 4: With bypass capacitor (C2) in the emitter, not involving a swapping process and with no load resistance, AV = - RC / re\n";
			cout << "\tCase 5: Without bypass capacitor (C2) in the emitter, not involving a swapping process and with no load resistance, AV = - RC / (re + RE) \n\n\n";
			cin.ignore();
			waitEnter("continue"); //stop the program until user press enter
			system("cls");
		}

		else if (study_analysis == 'D')
		{
			system("cls");
			cout << "DC analysis\n";
			cout << "===========\n";
			cout << "For DC analysis, the common-emitter configuration has two common biasing methods: base bias and voltage divider bias.\n";
			cout << "To perform DC analysis, a DC equivalent circuit is developed by replacing the coupling and bypass capacitors with open circuits.\n";

			cout << "Base Bias\n";
			cout << "=========\n";
			cout << "Base bias is also called fixed bias, which is the simplest way to bias a transistor.\n";
			cout << "In base bias, a resistor is connected from the base to the power supply, and the emitter is connected to ground.\n";
			cout << "The advantage of base bias is its simplicity.\n";
			cout << "The disadvantage of base bias is that it is beta-dependent and affected by temperature variations.\n";
			cout << "Base bias is mainly used for switching applications.\n";

			cout << "                       VCC\n";
			cout << "                        |\n";
			cout << "      ------------------|\n";
			cout << "      |                 RC\n";
			cout << "      |                 |\n";
			cout << "      |                 |\n";
			cout << "      |                /\n";
			cout << "      |             |\n";
			cout << "      ----- RB -----|\n";
			cout << "                    |\n";
			cout << "                       \\\n";
			cout << "                         |\n";
			cout << "                         |\n";
			cout << "                         |\n";
			cout << "                        GND\n\n";

			cout << "This is the base bias circuit.\n\n";

			cout << "There are 3 equations for the base bias circuit in DC analysis.\n";
			cout << "All equations are expressed in terms of voltage (V), current (A), and resistance (ohm), instead of using prefixes such as milli (m) or kilo (k).\n\n";

			cout << "[Equation 1 (for finding IB)]: VCC - IBRB - VBE = 0 and VBE is 0.7V.\n\n\n";

			cout << "[Equation 2 (for finding IC)]: IC = betaDC * IB\n\n\n";

			cout << "[Equation 3 (for finding VCE)]: VCC - ICRC -VCE = 0\n\n\n";
			cin.ignore();
			waitEnter("continue"); //stop the program until user press enter

			system("cls");
			cout << "Voltage divider bias\n";
			cout << "====================\n";
			cout << "Voltage divider bias uses a voltage divider in the base circuit.\n";
			cout << "The advantage of voltage divider bias is that it is beta-independent and does not require a dual polarity power supply.\n";
			cout << "The disadvantage of voltage divider bias is essentially none (compared to other biasing circuits) in terms of DC operation.\n";
			cout << "Voltage divider bias is primarily used to bias linear amplifiers.\n";

			cout << "                       VCC\n";
			cout << "                        |\n";
			cout << "      ------------------|\n";
			cout << "      |                 RC\n";
			cout << "      |                 |\n";
			cout << "      R1                |\n";
			cout << "      |                /\n";
			cout << "      |             |\n";
			cout << "      --------------|\n";
			cout << "      |             |\n";
			cout << "      |                \\\n";
			cout << "      R2                 |\n";
			cout << "      |                  RE\n";
			cout << "      |                  |\n";
			cout << "      --------------------\n";
			cout << "               |\n";
			cout << "               |\n";
			cout << "              GND\n\n";

			cout << "This is the voltage divider bias circuit.\n\n";

			cout << "There are 5 equations for the voltage divider bias circuit in DC analysis.\n";
			cout << "! Note: All equations are expressed in terms of voltage (V), current (A), and resistance (?), instead of using prefixes such as milli (m) or kilo (k). !\n\n";

			cout << "[Equation 1 (for finding RIN_base)]: RIN_base = betaDC * RE\n\n\n";

			cout << "[Equation 2 (for finding R2_total)]: \n";
			cout << "\tCase 1: if RIN_base >= 10R2, R2_total = R2\n";
			cout << "\tCase 2: if RIN_base < 10R2, R2_total = 1 / ((1 / R2) + (1 / RIN_base))\n\n\n";

			cout << "[Equation 3 (for finding VB)]: VB = R2_total / (R1 + R2_total) * VCC\n\n\n";

			cout << "[Equation 4 (for finding IC)]: IC = (VB - 0.7) / RE\n\n\n";

			cout << "[Equation 5 (for finding VCE)]: VCE = VCC - IC * (RC + RE)\n\n\n";

			waitEnter("continue"); //stop the program until user press enter
			system("cls");
		}
		else if (study_analysis == 'Q') {
			cout << "Exiting notes program... Bye-bye (^-^)\n\n";
			Sleep(1000);
			system("cls");
		}

		else
			cout << "Invalid input! Please enter A, D or Q!\n"; //if study_analysis is not equal to 'A' or 'D' or 'Q', it will ask user to enter again

	} while (study_analysis != 'Q');
}

//notes for chapter 3
void notes_FET()
{
	char option;
	cout << "\n --------------------------------------------" << endl;
	cout << "| Chapter 3: Field Effect transistors (FETs) |" << endl;
	cout << " --------------------------------------------" << endl << endl;
	cout << "3.0 Introduction:" << endl;
	cout << "=================" << endl;
	cout << "The FET is a voltage-controlled device where voltage between two of the terminals (gate and source) controls the current through the device." << endl << endl;
	cout << "A major feature of FETs is that they have very high input resistance." << endl;
	cout << "Hence, there are very useful in designing VLSI circuits since the devices draws negligible currents due to there high input impedance." << endl << endl;
	cout << "There are two main types of FETs: " << endl;
	cout << "1) Junction field-effect transistor (JFET) " << endl;
	cout << "2) Metal-oxide field-effect transistor (MOSFET)" << endl << endl;
	waitEnter("continue");
	system("cls");
	cout << "3.1 Junction Field-Effect Transistor (JFET)" << endl;
	cout << "===========================================" << endl;
	cout << "The JFET has two regions: a p-type material and an n-type material." << endl;
	cout << "The construction of the JFET is shown bellow." << endl;

	cout << "       Drain                            Drain  " << endl;
	cout << "      ___|___                          ___|___ " << endl;
	cout << "     |_  n  _|                        |_  p  _|" << endl;
	cout << "Gate-|p|   |p|                   Gate-|n|   |n|" << endl;
	cout << "     |-     -|                        |-     -|" << endl;
	cout << "      -------                          ------- " << endl;
	cout << "         |                                |    " << endl;
	cout << "       Source                           Source " << endl;
	cout << "     n-channel                        p-channel" << endl << endl;

	cout << "Note that the non-channel material axtually surrounds the channel like \"a belt around the waist\"." << endl;
	cout << "The non-channel material is diffused in the relative material to form a channel and it is connected to the gate lead." << endl << endl;

	cout << "By providing a drain to source voltage Vds, it sypplying a current from the drain to source" << endl;
	cout << "(then we can say Id = Is , where is is Source current) " << endl;
	cout << "Next, by providing a negative voltage to gate-to-source and sets a reverse-bias voltage between it and the pn junction become reverse biased." << endl << endl;

	cout << "In short, A JFET works by using the gate voltage to widen or narrow the depletion layer," << endl;
	cout << "which controls the channels width and therefore regulates the current flowing from drain to source." << endl << endl;

	waitEnter("continue");
	system("cls");
	cout << "3.2 JFET Characteristics and Parameters" << endl;
	cout << "=======================================" << endl;
	cout << "The drain current can be determine by using the equation of the JFET transfer characteristics:" << endl;
	cout << " _________________________________" << endl;
	cout << "| Id = Idss [1-(Vgs / Vgs_off)]^2 |" << endl;
	cout << " ---------------------------------" << endl;
	cout << "the meaning of parameters is shown below: " << endl;
	cout << "Id: Drain current \nIdss: maximum drain current \nVgs: volatge gate-to-source \nVgs_off: cutoff voltage" << endl;
	cout << "! Notes that the Idss and the Vgs_off can be found in related JFET datasheet !" << endl << endl;

	cout << "Besides, the JFET forward transconductance (gm) is the slope of the curve." << endl;
	cout << "The unit of it is siemens (S), it is used to calculate the voltage gain in an amplifier." << endl;
	cout << "It can be determined by following equation: " << endl;
	cout << " ____________________________" << endl;
	cout << "| gm = gm_0[1-(Vgs/Vgs_off)] |" << endl;
	cout << " ----------------------------" << endl;
	cout << "where gm_0 is the gm at Vgs =0V , and will be given in the data sheets." << endl << endl;

	waitEnter("continue");
	system("cls");
	cout << "3.3 JFET Biasing" << endl;
	cout << "================" << endl;
	cout << "Just like BJTs, there are severals type of JFET biasing like Self biasing and Voltage-divider biasing." << endl;
	cout << "The most common biasing is self biasing, the circuit is shown below. " << endl;
	cout << "                Vdd" << endl;
	cout << "                 |    | Id" << endl;
	cout << "                 Rd   v" << endl;
	cout << "                 |" << endl;
	cout << "                 | " << endl;
	cout << "                 D" << endl;
	cout << "                /" << endl;
	cout << "   ----G----> JFET" << endl;
	cout << "   |            \\" << endl;
	cout << "   |             S" << endl;
	cout << "   Rg            |" << endl;
	cout << "   |             Rs" << endl;
	cout << "   |             |" << endl;
	cout << "  GND           GND" << endl;
	cout << "! Note that the value of source resistor Rs must be greater than Rs_min = |Vgs/Id|,to establishing a JFET bias point !" << endl;
	cout << "The step to determine Vgs and Vds can be explained in JFET self biasing simulation." << endl;
	cout << "\nDo you want jump to JFET simulation? (Y/N):";
	cin >> option;
	charValidation(&option);
	if (toupper(option) == 'Y')
		jfet();
	cin.ignore();
	waitEnter("continue");
	system("cls");
	cout << "3.4 The Metal-Oxide Semiconductor Field-Effect Transistor (MOSFET)" << endl;
	cout << "==================================================================" << endl;
	cout << "There are two types of MOSFET: D-MOSFET and E-MOSFET." << endl;
	cout << "Both of them are having p and n channel. The construction of n-channel MOSFET was shown below." << endl;

	cout << "       Source       Gate(Metal)    Drain\n";
	cout << "        |             |              |\n";
	cout << "        |             |              |\n";
	cout << "        |       ______|______        |\n";
	cout << "        |      | Oxide (SiO2)|       |\n";
	cout << "     | ==[n]===== n-Channel ====>>===[n]==|\n";
	cout << "     |        p-type Substrate            |\n";
	cout << "     | ___________________________________|\n";

	cout << "An n-channel MOSFET operates in the depletion mode when a negative gate-to-source" << endl;
	cout << "voltage is applied.In this mode, its characteristics are similar to that of JFET." << endl;
	cout << "When a positive gate - to - source voltage is applied, the n - channel MOSFET operates in the enhancement - mode." << endl;
	cout << "! Note that E-MOSFET only can operates in enhancement mode while D-MOSFET can operates in both mode. !" << endl;

	waitEnter("continue");
	system("cls");
	cout << "\n3.5 MOSFET Characteristics and Parameters" << endl;
	cout << "=========================================" << endl;
	cout << "The transconductance curve equation for D-MOSFET is same with JFET." << endl;
	cout << "For E-MOSFET, the square law equation is:" << endl;
	cout << " _____________________________" << endl;
	cout << "| Id = K [1-(Vgs / Vgs_th)]^2 |" << endl;
	cout << " -----------------------------" << endl;
	cout << "where Vgs_th is the threshold voltage and the constant K can be given:" << endl;
	cout << " _______________________________" << endl;
	cout << "| K = Id_on / (Vgs_on-Vgs_th)^2 |" << endl;
	cout << " -------------------------------" << endl;
	cout << "where Id_on and Vgs_on can be found from the data sheet." << endl;

	waitEnter("continue");
	system("cls");
	cout << "3.6 E-MOSFET Biasing " << endl;
	cout << "=====================" << endl;
	cout << "The most common biasing for E-MOSFET is voltage-divider bias and drain-feedback bias." << endl;
	cout << "The circuit shown below is the voltage-divider bias model for E-MOSFET: " << endl;
	cout << "                Vdd" << endl;
	cout << "   --------------|" << endl;
	cout << "   |             |   | Id " << endl;
	cout << "   R1            Rd  V" << endl;
	cout << "   |             | " << endl;
	cout << "   |             D" << endl;
	cout << "   |            /" << endl;
	cout << "   ----G----E_MOSFET" << endl;
	cout << "   |            \\" << endl;
	cout << "   |             S" << endl;
	cout << "   |             |" << endl;
	cout << "   R2            |" << endl;
	cout << "   |             |" << endl;
	cout << "  GND           GND" << endl;
	cout << "The way we analyse the circuit is almost same with JFET and D-MOSFET by using Kirchhoff's Law" << endl;
	cout << "It can be explained in E-MOSFET's simulation." << endl << endl;

	cout << "\nDo you want jump to E-MOSFET simulation? (Y/N):";
	cin >> option;
	charValidation(&option);
	if (toupper(option) == 'Y') // added by Daniel to debug
		mosfet();

	cout << "\n\nCongrats!! you are done on reading the notes for Chapter 3. (*^V^*)/" << endl;
	cin.ignore();
	waitEnter("return notes selection");
	system("cls");
}


void notes_OA() {
	system("cls");
	cout << "\n --------------------------------------" << endl;
	cout << "| Chapter 4: The Operational Amplifier. |" << endl;
	cout << " ----------------------------------------" << endl << endl;
	cout << "->There are three type of amplifier:\n ";
	cout << "1.Noninverting Amplifier\n";
	cout << "2.Inverting Amplifier\n";
	cout << "3.Voltage-Follower\n\n";

	cout << "4.1.Noninverting Amplifier\n";
	cout << "==========================\n";
	cout << "Circuit Diagram: \n";
	cout << "                                       \n";
	cout << "                |\\                    \n";
	cout << "                | \\                   \n";
	cout << " Vin (+)------->|+ \\                  \n";
	cout << "                |   \\_____________Vout\n";
	cout << "                |   /        |         \n";
	cout << "        ------->|- /         |         \n";
	cout << "        |       | /          Rf        \n";
	cout << "        |       |/           |         \n";
	cout << "     Vf |____________________|  Feedback    \n";
	cout << "                             |  Network     \n";
	cout << "                             |         \n";
	cout << "                             Ri        \n";
	cout << "                             |         \n";
	cout << "                            GND        \n";
	cout << "                                       \n";
	cout << "An op-amp connected in a closed-loop configuration as a noninverting amplifier.\n";
	cout << "The input signal is applied to the noninverting(+) input.\n ";
	cout << "A portion of the output is applied back to the inverting(-) input through the feedback network.This constitutes negative feedback. \n";
	cout << "-->The feedback fraction, B = Ri/(Ri + Rf) \n";
	cout << "-->The closed-loop gain for the noninverting amplifier, Acl(NI) = 1 + (Rf / Ri)\n";
	cout << "-->The input impedance of a noninverting amplifier configuration, Zin(NI) = (1 + Aol * B ) * Zin\n";
	cout << "-->The output impedance of a noninverting amplifier configuration, Zout(NI) = Zout/(1 + Aol * B )\n\n";
	cin.ignore();
	waitEnter("continue");
	system("cls");

	cout << "4.2 Inverting Amplifier\n";
	cout << "=======================\n";
	cout << "Circuit Diagram: \n";
	cout << "                                               \n";
	cout << "                    _______Rf_______           \n";
	cout << "                   |                |          \n";
	cout << "                   |                |          \n";
	cout << "                   |    |\\         |          \n";
	cout << "                   |    | \\        |          \n";
	cout << " Vin (~)------Ri------->|+ \\       |          \n";
	cout << "                        |   \\______|____Vout  \n";
	cout << "                        |   /                  \n";
	cout << "                ------->|- /                   \n";
	cout << "                |       | /                    \n";
	cout << "                |       |/                     \n";
	cout << "               GND                             \n";
	cout << "                                               \n";
	cout << "An op-amp connected as an inverting amplifier with a controlled amount of voltage gain.\n";
	cout << "The input signal is applied through a series input resistor(Ri) to the inverting (-) input.\n";
	cout << "Also, the output is feed back through Rf to the inverting input. The noninverting (+) inout is grounded.\n";
	cout << "-->The closed-loop gain for the inverting amplifier, Acl(I) = -(Rf / Ri)\n";
	cout << "-->The input impedance of the inverting amplifier configuration, Zin(I) ? Ri\n";
	cout << "The inout impedance,Zin(I), approximately equals the external inout resistance,Ri, because of the virtual ground at the inverting input.\n";
	cout << "-->The output impedance of the inverting amplifier configuration, Zout(I) = Zout/(1 + Aol * B )\n\n";

	waitEnter("continue");
	system("cls");
	cout << "4.3.Voltage-Follower\n";
	cout << "====================\n";
	cout << "Circuit Diagram: \n";
	cout << "                                       \n";
	cout << "                |\\                    \n";
	cout << "                | \\                   \n";
	cout << " Vin (~)------->|+ \\                  \n";
	cout << "  |             |   \\_____________Vout\n";
	cout << "  GND           |   /        |         \n";
	cout << "        ------->|- /         |         \n";
	cout << "        |       | /          Rf        \n";
	cout << "        |       |/           |         \n";
	cout << "        |____________________|         \n";
	cout << "                             |         \n";
	cout << "                             |         \n";
	cout << "                             Ri        \n";
	cout << "                             |         \n";
	cout << "                            GND        \n";
	cout << "                                       \n";
	cout << "The voltage-follower configuration is a special case of the noninverting amplifier where all of the"
		<< "output voltage is fed back to the inverting(-) inout by a straingt connection.\n";
	cout << "The straingt feedback connection has a voltage gain of approximately 1.\n";
	cout << "The closed - loop voltage gain of a noninverting amplifier is 1 / B as previosly derived.\n";
	cout << "Since B = 1, the closed - loop gain of the voltage - follower is Acl(VF) = 1.\n";
	cout << "-->The input impedance of the voltage-follower, Zin(VF) = (1 + Aol) * Zin\n";
	cout << "-->The output impedance of the voltage-follower, Zout(VF) = Zout/(1 + Aol)\n";


	cout << "\nCongrats!! you are done on reading the notes for Chapter 4. (*^V^*)/" << endl;
	waitEnter("return notes selection");
	system("cls");
}




void charValidation(char* option) {
	while (toupper(*option) != 'Y' && toupper(*option) != 'N' || cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid input, please ENTER 'Y' or 'N':" << endl;
		cin >> option;
	}
}

void waitEnter(string action)
{
	string dummy;
	cout << "\nPress ENTER to " << action << " ~~~";
	getline(cin, dummy);
}