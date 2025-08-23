#include <iostream>
#include <string>
#include <cmath>
#include<iomanip>
#include<fstream>
#include<cctype>
using namespace std;
struct User {
	string Name;
	int ID;
	int score;
};//hi//hihihihihi
void cal(int);
void note();
int quiz();
void getinfo(User&);
void userlist(User*, int);
void loaduserdata(User*);
bool checkopenfile(fstream&, string);
void menu(User[], int);
int findslot(User[]);
void savefile(User*, string, int);
int check(float*, int&);
float fun1();
float fun2();
float fun3();
void clamper();
const int num = 100;
//try using push in github

bool hostLogin();//Daniel
bool hostMenu();//Daniel
void jfet(); //Daniel
void mosfet(); //Daniel
void jfet_DrainCurrent(int option);//Daniel
void notes_FET(); //Daniel
//trang
void non_inverting();
void voltageFollower();
void invertingAmplifier();

// Zinor
void simulator1_BJT();
void simulator2_BJT();
void simulator3_BJT();
void notes_BJT();


int main() {
	int opt, userindex = -1;

	int choice;
	bool Return = true;
	do
	{
		cout << "=================================\n";
		cout << "   WELCOME TO BASIC ELECTRONIC   \n";
		cout << "=================================\n";
		cout << "Please select mode:\n";
		cout << "1. Host Mode\n";
		cout << "2. User Mode\n";
		cout << "0. Exit\n";
		cout << "Choice (0~2): ";
		cin >> choice;
		while (choice != 0 && choice != 1 && choice != 2)
		{
			cout << "Invalid input please enter 0 to 2." << endl;
			cout << "Enter your choice: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
		{
			if (hostLogin())
				Return = hostMenu();
			else
				Return = true; 
			break;
		}
		case 2:
		{
			cout << "userMenu";//zk code
			Return = false;
			break;
		}
		case 0:
		{
			cout << "Exitting program...";
			break;
		}
		}
	} while (Return);
	//By zikang
	User stu[num] = {};

	fstream list;
	list.open("Userlist", ios::app);
	list.close();
	if (!checkopenfile(list, "Userlist")) {
		return 1; // Exit if file cannot be opened
	}
	loaduserdata(stu);

	userindex = findslot(stu);
	if (userindex != -1) {
		getinfo(stu[userindex]);
	}
	else {
		cout << "The userlist is full." << endl;
	}

	userlist(stu, userindex);


	menu(stu, userindex);


	return 0;
}

//Daniel
bool hostLogin() {
	string hostID, hostPass;
	const string correctID = "Teacher";
	const string correctPass = "123456";

	int attempts = 0, maxAttempts = 3;

	cout << "\n--- Host Login ---\n";
	cout << "(Type 999 as Host ID to return to Login Surface)\n\n";

	while (attempts < maxAttempts) {
		cout << "Enter Host ID: ";
		cin >> hostID;

		// Option to return to login surface
		if (hostID == "999") {
			cout << "\nReturning to Login Surface...\n";
			return false; // exit without counting as failed attempt
		}

		cout << "Enter Password: ";
		cin >> hostPass;

		if (hostID == correctID && hostPass == correctPass) {
			cout << "\nLogin Successful!\n";
			return true;
		}
		else {
			attempts++;
			cout << "\nInvalid ID or Password. Attempts left: "
				<< (maxAttempts - attempts) << "\n";
		}
	}

	cout << "\nToo many failed attempts. Returning to Login Surface...\n";
	return false;
}
//Daniel
bool hostMenu()
{
	int option;
	cout << "\n--- Host Menu ---\n";
	cout << "1. Show Student Result\n";
	cout << "2. User List\n";
	cout << "3. Edit / Delete Comments\n";
	cout << "0. Logout\n";
	cout << "Enter your choice(0~3):";
	cin >> option;
	switch (option) {
	case 0:
	{
		cout << "Exit..." << endl << endl;
		return true;
		break;
	}
	case 1:
	{
		cout << "1";
		return false;
		break;
	}
	default:
		return true; // temporary logout
	}
}


void menu(User stu[], int userindex) {

	int a, b, opt;
	if (userindex < 0 || userindex >= num) {
		cout << "ERROR! Invalid user index!" << endl;
		return;
	}
	do {
		cout << "Choose the action you want to proceed 1. note, 2. quiz, 3. stimulator, 4. userlist, 5. end:(i.e. 1,2,3,4,5 out)";
		cin >> opt;
		switch (opt) {
		case 1:
			note();
			break;
		case 2:

			stu[userindex].score = quiz();

			cout << "Score updated:" << stu[userindex].score << endl;
			break;
		case 3:
			do {
				cout << "Select the type of stimulator\n1.\n2.clamper\n3.BJT 1\n4.BJT 2\n5.BJT 3\n6.JFET\n7. E-MOSFET\n8-10.chp4 \n0.return:";
				cin >> a;
				cal(a); //select stimular in menu
			} while (a != 0);
			break;
		case 4:
			userlist(stu, userindex);
			break;
		case 5:
			cout << "Programme end." << endl;

			break;
		default:
			cout << "Invalid input try to choose again.(1,2,3,4)" << endl;
		}
	} while (opt != 5);
}
int quiz() {
	int b, points;
	char a;
	float answer[23] = {};
	do {
		cout << "Choose the question you want to answer(13 out):";
		cin >> b;
		cout << endl;
		switch (b) {
		case 1:
			cout << "1";//insert your question here
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;
				a = toupper(a);

				while (a != 'Y' && a != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y') {
					fun1();
				}

			} while (a == 'Y');
			cout << "Enter the answer:";//add this two line if your question need answer more than 1
			cin >> answer[0];           //add this two line if your question need answer more than 1, answer[i+1]
			break;
		case 2:
			cout << "Quesiton 2. Given the following configuration shown in figure 1, Vin = 10V, Vd = 0.7V, Vbias = 5V. " << endl;
			cout << "Find Vout peak in + ve half cycle and -ve half cycle.\n";
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
			cout << "                     Figure 2\n";
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;
				a = toupper(a);

				while (a != 'Y' && a != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y') {
					clamper();
				}

			} while (a == 'Y');
			cout << "Enter the answer of Vout(+ve):";
			cin >> answer[1];
			cout << "Enter the answer of Vout(-ve):";
			cin >> answer[2];
			break;
		case 3:
			cout << "Quesiton 3. Given the following configuration shown in figure 1, Vin = 15V, Vd = 0.7V, Vbias = 7.5V. " << endl;
			cout << "Find Vout peak in + ve half cycle and -ve half cycle.\n";
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
			cout << "                     Figure 3\n";
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;
				a = toupper(a);

				while (a != 'Y' && a != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y') {
					clamper();
				}

			} while (a == 'Y');
			cout << "Enter the answer of Vout(+ve):";
			cin >> answer[3];
			cout << "Enter the answer of Vout(-ve):";
			cin >> answer[4];
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
			cout << "              GND\n\n";

			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;
				a = toupper(a);

				while (a != 'Y' && a != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y') {
					simulator1_BJT();
				}

			} while (a == 'Y');
			cout << "Enter the answer for IC (mA):";
			cin >> answer[5];
			cout << "Enter the answer for VCE (V):";
			cin >> answer[6];
			break;
		case 5:
			cout << "\n\n\nQuestion 5: Determine the value of VCE when IC = 0.1mA and 0.2mA.\n\n";

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
			cout << "                        GND\n\n";

			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;
				a = toupper(a);

				while (a != 'Y' && a != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (a == 'Y') {
					simulator2_BJT();
				}

			} while (a == 'Y');
			cout << "Enter the answer dor VCE in 0.1mA(V):";
			cin >> answer[7];
			cout << "Enter the answer dor VCE in 0.2mA(V):";
			cin >> answer[8];
			break;
		case 6:
			cout << "Question 6 :\n";
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
			cout << "                                            GND\n\n";
			cout << "                                         Figure 6\n\n\n";
			cout << " Hint: This is the Common-Emitter (CE) Amplifier with bypass capacitor (C2) in the emitter, not involving swapping process and no load resistance, RL.\n\n";


			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;
				a = toupper(a);

				while (a != 'Y' && a != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (a == 'Y') {
					simulator3_BJT();
				}

			} while (a == 'Y');
			cout << "\nEnter the answer for AV: ";
			cin >> answer[9]; // havent change ''''
			break;

		case 7://ANS:2.25 ,1125
			cout << "Q7. Chp3" << endl;
			cout << "Determine the drain current (Id) and forward transconductance (gm) for Vgs = -4V for a 2N5459 JFET." << endl;
			cout << "Refer to the data sheet for the JFET below." << endl;
			cout << "Igss = -1nA \nVgs_off = -8V \nIdss = 9mA \ngm_0 = 2250 micro_S" << endl;

			do {
				//tips for darain current
				cout << "\nDo you want a tips to calculate drain current? (Y/N): ";
				cin >> a;
				while (toupper(a) != 'Y' && toupper(a) != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (toupper(a) == 'Y') // added by Daniel to debug
					jfet_DrainCurrent(1);

				// tips for gm
				cout << "\nDo you want a tips to calculate forward transconductance gm? (Y/N): ";
				cin >> a;
				while (toupper(a) != 'Y' && toupper(a) != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (toupper(a) == 'Y') // added by Daniel to debug
					jfet_DrainCurrent(2);
			} while (toupper(a) == 'Y');
			cout << "Enter the answer for Id (in mille-amperes):";
			cin >> answer[10];
			cout << "Enter the answer for gm (in micro-Siemens):";
			cin >> answer[11];
			break;
		case 8:// Ans: V_DS: 8.9 V_GS:-1.1
			cout << "Q8. Chp 3: FET (JFET)" << endl << endl;
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
			cout << "  GND           GND" << endl << endl;
			cout << " Find the voltage drain to source (V_DS) and voltage gate to source (V_GS)" << endl;
			cout << " in the circuit shown above." << endl << endl;

			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (toupper(a) != 'Y' && toupper(a) != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (toupper(a) == 'Y') // added by Daniel to debug
					jfet();
			} while (toupper(a) == 'Y');
			cout << "Enter the answer for V_DS (in volts and round to two decimals):";
			cin >> answer[12];
			cout << "Enter the answer for V_GS (in volts and round to two decimals):";
			cin >> answer[13];

			break;
		case 9:// Ans 12.7 ; 3.13
			cout << "Q9. Chapter 3: FET (E-MOSFET)" << endl << endl;
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
			cout << "            GND           GND" << endl << endl;
			cout << " Find the voltage drain to source (V_DS) and voltage gate to source (V_GS)" << endl;
			cout << " in the E-MOSFET circuit shown above. Given that the particular MOSFET has" << endl;
			cout << " the theshold voltage Vgs_th = 2V and the parameter devices K = 50 mA/V^2 ." << endl << endl;
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (toupper(a) != 'Y' && toupper(a) != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (toupper(a) == 'Y') // added by Daniel to debug
					mosfet();
			} while (toupper(a) == 'Y');
			cout << "Enter the answer for V_DS (in volts and round to two decimals):";
			cin >> answer[14];
			cout << "Enter the answer for V_GS (in volts and round to two decimals):";
			cin >> answer[15];
			break;


		case 10://NI
			cout << "Question 10 :\n";
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
			cout << "Given: Rf =220000 ohms, Ri =10000 ohms ,Vin = 5.0 V, Aol = 200000 , Zin = 2000000 ohms, Zout = 75 ohms.\n";
			cout << "Determine the closed-loop voltage gain,Acl, the input and output impedances of the amplifier.\n";


			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (toupper(a) != 'Y' && toupper(a) != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (toupper(a) == 'Y')
					non_inverting();
			} while (toupper(a) == 'Y');

			cout << "Enter the answer for closed-loop voltage gain,Acl:";
			cin >> answer[16];
			cout << "Enter the answer for the input impedance (in Giga ohms) :";
			cin >> answer[17];
			cout << "Enter the answer for the output impedance (in micro ohms):";
			cin >> answer[18];
			break;
		case 11://I

			cout << "\nQuestion 11 :\n";
			cout << "\n---Inverting Amplifier,I---\n";
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
			cout << "Given: Rf =210000 ohms, Ri =10000 ohms.\n";
			cout << "Determine the closed-loop voltage gain,Acl and the input impedance of the amplifier.\n";

			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (toupper(a) != 'Y' && toupper(a) != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (toupper(a) == 'Y')
					invertingAmplifier();
			} while (toupper(a) == 'Y');

			cout << "Enter the answer for closed-loop voltage gain,Acl:";
			cin >> answer[19];
			cout << "Enter the answer for the input impedance:";
			cin >> answer[20];
			break;
		case 12://VF

			cout << "\nQuestion 12 :\n";
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
			cout << "Given: Rf =230000 ohms, Ri =10000 ohms , Aol = 200000 , Zin = 1000000 ohms, Zout = 70 ohms and B = 1.\n";
			cout << "Determine the input and output impedances of the amplifier.\n";

			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (toupper(a) != 'Y' && toupper(a) != 'N') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
					cin >> a;
				}
				if (toupper(a) == 'Y')
					voltageFollower();
			} while (toupper(a) == 'Y');
			cout << "Enter the answer for the input impedance( in Giga ohms):";
			cin >> answer[21];
			cout << "Enter the answer for the output impedance (in micro ohms):";
			cin >> answer[22];
			break;

		case 13:
			cout << "You have returned to main function." << endl;
			break;
		default:
			cout << "Invalid input." << endl;
			break;
		}



	} while (b != 13);
	check(answer, points);
	return points;


}

void note() {
	int chap;
	do {
		cout << "Choose the chapter of notes you want to read(5 out):";
		cin >> chap;
		switch (chap) {
		case 1:
			cout << "chap 1." << endl;
			break;
		case 2:
			cout << "chap 2." << endl;
			notes_BJT();
			break;
		case 3:
			cout << "chap 3." << endl;
			notes_FET();
			break;
		case 4:
			cout << "----Chapter 4: The Operational Amplifier.---- \n";
			cout << "\n1.Noninverting Amplifier\n";
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
			cout << "The input signal is applied to the noninverting(+) input.A portion of the output\n ";
			cout << "is applied back to the inverting(-) input through the feedback network.This constitutes negative feedback. \n";
			cout << "-->The feedback fraction, B = Ri/(Ri + Rf) \n";
			cout << "-->The closed-loop gain for the noninverting amplifier, Acl(NI) = 1 + (Rf / Ri)\n";
			cout << "-->The input impedance of a noninverting amplifier configuration, Zin(NI) = (1 + Aol * B ) * Zin\n";
			cout << "-->The output impedance of a noninverting amplifier configuration, Zout(NI) = Zout/(1 + Aol * B )\n";
			cout << "\n2.Inverting Amplifier\n";
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
			cout << "An op-amp connected as an inverting amplifier with a controlled amount of voltage gain. The input signal \n";
			cout << "is applied through a series input resistor(Ri) to the inverting (-) input.Also, the output is feed back through\n";
			cout << "Rf to the inverting input. The noninverting (+) inout is grounded.\n";
			cout << "-->The closed-loop gain for the inverting amplifier, Acl(I) = -(Rf / Ri)\n";
			cout << "-->The input impedance of the inverting amplifier configuration, Zin(I) ≅ Ri\n";
			cout << "The inout impedance,Zin(I), approximately equals the external inout resistance,Ri,";
			cout << "because of the virtual ground at the inverting input.\n";
			cout << "-->The output impedance of the inverting amplifier configuration, Zout(I) = Zout/(1 + Aol * B )\n";
			cout << "\n3.Voltage-Follower\n";
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
			cout << "The voltage-follower configuration is a special case of the noninverting amplifier where all of the \n";
			cout << "output voltage is fed back to the inverting(-) inout by a straingt connection.The straingt feedback connection \n";
			cout << "has a voltage gain of approximately 1. The closed - loop voltage gain of a noninverting amplifier is 1 / B as previosly derived. \n";
			cout << "Since B = 1, the closed - loop gain of the voltage - follower is Acl(VF) = 1.\n";
			cout << "-->The input impedance of the voltage-follower, Zin(VF) = (1 + Aol) * Zin\n";
			cout << "-->The output impedance of the voltage-follower, Zout(VF) = Zout/(1 + Aol)\n";
			break;

			break;
		case 5:
			cout << "You have returned to menu" << endl;
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	} while (chap != 5);
}
void cal(int a) {

	switch (a) {
	case 1:
		cout << "Equation 1" << endl;
		fun1();//insert you function here
		break;
	case 2:
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
		cout << "   |           / \\  Vd          |                              |           \\ /  Vd          |" << endl;
		cout << "   |           ---              |                              |          -----             |\n";
		cout << "  Vin           |               RL         Vout               Vin           |               RL         Vout\n";
		cout << "   |            |               |                              |            |               |\n";
		cout << "   |            |               |                              |            |               |\n";
		cout << "   -----------------------------------------o -                -----------------------------------------o -\n";
		clamper();
		break;
	case 3:
		cout << "Equation 3" << endl;
		simulator1_BJT();
		break;
	case 4:
		cout << "Equation 4" << endl;
		simulator2_BJT();
		break;
	case 5:
		cout << "Equation 5" << endl;
		simulator3_BJT();
		break;
	case 6:
		jfet();
		break;
	case 7:
		mosfet();
		break;
	case 8:
		non_inverting();
		break;
	case 9:
		voltageFollower();
		break;
	case 10:
		invertingAmplifier();
		break;

	case 0:
		cout << "You have returned to quizz" << endl;
		break;

	default:
		cout << "Invalid input" << endl;
		break;
	}

}
bool checkopenfile(fstream& file, string name) {
	file.open(name, ios::in | ios::out | ios::app);
	if (file.is_open()) {
		cout << "File opened successfully: " << name << endl;
		return true;
	}
	else {
		cout << "Error opening file: " << name << endl;
		return false;
	}

}

void loaduserdata(User* stu) {
	fstream list = fstream("Userlist", ios::in);
	if (!list.is_open()) {
		cout << "Error opening user list file." << endl;
		return;
	}
	string line;
	for (int i = 0; i < num; i++) {
		if (getline(list, line)) {
			if (line.empty()) continue; // Skip empty lines
			stu[i].Name = line;
			if (getline(list, line)) {
				stu[i].ID = stoi(line);
			}
			if (getline(list, line)) {
				stu[i].score = stoi(line);
			}
		}
		else {
			break; // Stop if no more lines to read
		}
	}
	list.close();
}

void getinfo(User& stu) {
	cout << "Enter your name:";
	getline(cin, stu.Name);
	cout << "Enter your student ID:";
	cin >> stu.ID;
	stu.score = 0;

}
void userlist(User stu[], int index) {
	for (int i = 0; i <= index; i++) {
		cout << "Name: " << left << setw(20) << stu[i].Name <<
			" | Student ID: " << setw(7) << stu[i].ID <<
			" | Score: " << stu[i].score << endl;

	}
}

int findslot(User stu[]) {
	for (int i = 0; i < num; i++) {
		if (stu[i].ID == 0) {
			return i;
		}
	}
	return -1;
}

void savefile(User* stu, string name, int index) {
	fstream list = fstream("Userlist", ios::out | ios::app);
	if (!list.is_open()) {
		cout << "Error opening file for saving: " << name << endl;
		return;
	}
	list << stu[index].Name << endl;
	list << stu[index].ID << endl;
	list << stu[index].score << endl;
	list.close();
	cout << "User data saved successfully." << endl;
}

int check(float* a, int& points) {
	points = 0;       //9-19: Q8-Q12
	float checkans[23] = { 0, 24.3, 4.3, -6.8, 5.16, 1.95, 32.40, 28.80, -366.18, -36.8, 2.25, 1125, 8.9, -1.1, 12.7, 3.13, 23, 1.74, 8.62, -21,
		10000, 200, 350 }; //insert your answer here
	for (int i = 0; i < 20; i++) {
		if (checkans[i] >= 0) {
			if ((checkans[i] - (checkans[i] * 5 / 100)) <= *(a + i) && *(a + i) <= (checkans[i] + (checkans[i] * 5 / 100))) {
				points++;

			}
		}
		else {
			if ((checkans[i] + (checkans[i] * 5 / 100)) <= *(a + i) && *(a + i) <= (checkans[i] - (checkans[i] * 5 / 100))) {
				points++;
			}
		}

	}
	return points;
}
//add your calculator function here;
float fun1() {
	int a = 3;
	cout << a << endl;
	return a;
}

void clamper() {
	float Vin, Vc, Vd, Vbias, Vout;
	char polar;
	int opt;
	do {
		cout << "Select the type of clamper (input '+' for posivite '-' for negative):";
		cin >> polar;
		if (polar != '+' && polar != '-') {
			cout << "INPUT ERROR, input '+' or '-'";
		}
	} while (polar != '+' && polar != '-');
	if (polar == '+') {
		do {
			cout << "Positive clamper." << endl;
			cout << "Select the variable you want to find (1.Vc, 2.Vout(+ve half cycle), 3.Vout(-ve half cycle), 4. return):";
			cin >> opt;
			switch (opt) {
			case 1:
				cout << "Vc = Vin - Vd + Vbias" << endl;
				cout << "Input the value of Vin:";
				cin >> Vin;
				cout << "Input the value of Vd:";
				cin >> Vd;
				cout << "Input the value of Vbias(add -ve e.g. -2, if the polarity of battery is different to Vout):";
				cin >> Vbias;
				Vc = Vin - Vd + Vbias;
				cout << "Vc = " << Vc << "V" << endl;
				break;
			case 2:
				cout << "Vout(+ve half cycle) = Vc + Vin" << endl;
				cout << "Input the value of Vc:";
				cin >> Vc;
				cout << "Input the value of Vin:";
				cin >> Vin;
				Vout = Vc + Vin;
				cout << "Vout(+ve half cycle) = " << Vout << "V" << endl;
				break;
			case 3:
				cout << "Vout(-ve half cycle) = -Vd + Vbias" << endl;
				cout << "Input the value of Vd:";
				cin >> Vd;
				cout << "Input the value of Vbias(add -ve e.g. -2, if the polarity of battery is different to Vout):";
				cin >> Vbias;
				Vout = -Vd + Vbias;
				cout << "Vout(-ve half cycle) = " << Vout << "V" << endl;
				break;
			case 4:
				cout << "You have returned." << endl;
				break;
			default:
				cout << "INPUT ERROR, input integer (1,2,3,4)" << endl;

			}
		} while (opt != 4);

	}
	if (polar == '-') {
		do {
			cout << "Negative clamper." << endl;
			cout << "Select the variable you want to find (1.Vc, 2.Vout(+ve half cycle), 3.Vout(-ve half cycle), 4. return):";
			cin >> opt;
			switch (opt) {
			case 1:
				cout << "Vc = Vin - Vd - Vbias" << endl;
				cout << "Input the value of Vin:";
				cin >> Vin;
				cout << "Input the value of Vd:";
				cin >> Vd;
				cout << "Input the value of Vbias(add -ve e.g. -2, if the polarity of battery is different to Vout):";
				cin >> Vbias;
				Vc = Vin - Vd - Vbias;
				cout << "Vc = " << Vc << "V" << endl;
				break;
			case 2:
				cout << "Vout(+ve half cycle) = Vd + Vbias" << endl;
				cout << "Input the value of Vd:";
				cin >> Vd;
				cout << "Input the value of Vbias(add -ve e.g. -2, if the polarity of battery is different to Vout):";
				cin >> Vbias;
				Vout = Vd + Vbias;
				cout << "Vout(+ve half cycle) = " << Vout << "V" << endl;
				break;
			case 3:
				cout << "Vout(-ve half cycle) = -Vc - Vin" << endl;
				cout << "Input the value of Vc:";
				cin >> Vc;
				cout << "Input the value of Vin:";
				cin >> Vin;
				Vout = -Vc - Vin;
				cout << "Vout(-ve half cycle)= " << Vout << "V" << endl;
				break;
			case 4:
				cout << "You have returned." << endl;
				break;
			default:
				cout << "INPUT ERROR, input integer (1,2,3,4)" << endl;

			}
		} while (opt != 4);
	}

}

//made by Daniel for jfet drain current calculation
void jfet_DrainCurrent(int option)
{
	char correct_option;
	float Idss, Vgs_off, Vgs, Id;
	float gm, gm_0;

	switch (option) {
	case 1:
	{
		cout << "\n Tips:To calculate drain current, the equation for JFET transfer characterustic was applied." << endl;
		cout << " _________________________________" << endl;
		cout << "| Id = Idss [1-(Vgs / Vgs_off)]^2 |" << endl;
		cout << " ---------------------------------" << endl;
		do
		{
			//key in data
			do
			{
				cout << "Enter your data to calculate the value" << endl;
				cout << "Idss (in milli-amperes) : ";
				cin >> Idss;
				cout << "Vgs_off (in volts) [it should be a -ve voltage]: ";
				cin >> Vgs_off;
				cout << "Vgs (in volts) [it should be a -ve voltage]    : ";
				cin >> Vgs;
				if (Vgs_off > 0 || Vgs > 0)
					cout << "Both voltage should be a negative volatge." << endl
					<< "Please rekey the data." << endl;
			} while (Vgs_off > 0 || Vgs > 0);

			// print data
			cout << "\n\nIdss    : " << setprecision(2) << fixed << Idss << " milli-amperes." << endl;
			cout << "Vgs_off : " << setprecision(2) << fixed << Vgs_off << " volts." << endl;
			cout << "Vgs     : " << setprecision(2) << fixed << Vgs << " volts." << endl;
			cout << "Is the data all be verified correctly? (Y/N): ";
			cin >> correct_option;
			while (toupper(correct_option) != 'Y' && toupper(correct_option) != 'N')
			{
				cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
				cout << "Is the data all be verified correctly? (Y/N): ";
				cin >> correct_option;
			}
			if (toupper(correct_option) == 'N')
				cout << "\tPlease Reenter the data." << endl;
		} while (toupper(correct_option) == 'N');

		//calculation
		Id = Idss * (1 - (Vgs / Vgs_off)) * (1 - (Vgs / Vgs_off));
		cout << endl << " Result " << endl;
		cout << "------------------------" << endl;
		cout << "Id = " << Id << " mili-ampere." << endl << endl;
		break;
	}
	case 2:
	{
		cout << "\n Tips:Equation for forward transconductance, which is the slope of the transconductance curve." << endl;
		cout << " ____________________________" << endl;
		cout << "| gm = gm_0[1-(Vgs/Vgs_off)] |" << endl;
		cout << " ----------------------------" << endl;
		do
		{
			//key in data
			do
			{
				cout << "Enter your data to calculate the value" << endl;
				cout << "gm_0 (in micro_Siemens) : ";
				cin >> gm_0;
				cout << "Vgs_off (in volts) [it should be a -ve voltage]: ";
				cin >> Vgs_off;
				cout << "Vgs (in volts) [it should be a -ve voltage]    : ";
				cin >> Vgs;
				if (Vgs_off > 0 || Vgs > 0)
					cout << "Both voltage should be a negative volatge." << endl
					<< "Please rekey the data." << endl;
			} while (Vgs_off > 0 || Vgs > 0);

			// print data
			cout << "\n\ngm_0    : " << setprecision(2) << fixed << gm_0 << " micro-Siemens." << endl;
			cout << "Vgs_off : " << setprecision(2) << fixed << Vgs_off << " volts." << endl;
			cout << "Vgs     : " << setprecision(2) << fixed << Vgs << " volts." << endl;
			cout << "Is the data all be verified correctly? (Y/N): ";
			cin >> correct_option;
			while (toupper(correct_option) != 'Y' && toupper(correct_option) != 'N')
			{
				cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
				cout << "Is the data all be verified correctly? (Y/N): ";
				cin >> correct_option;
			}
			if (toupper(correct_option) == 'N')
				cout << "\tPlease Reenter the data." << endl;
		} while (toupper(correct_option) == 'N');

		//calculation
		gm = gm_0 * (1 - (Vgs / Vgs_off));
		cout << endl << " Result " << endl;
		cout << "------------------------" << endl;
		cout << "gm = " << gm << " micro-Siemens ." << endl << endl;
	}
	}
}
//made by Daniel for jfet simulation
void jfet()
{
	char correct_option;
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
	do
	{
		//key in data
		cout << "Vdd (in volts): ";
		cin >> Vdd;
		cout << "Rd (in Ohms): ";
		cin >> Rd;
		cout << "Rs (in Ohms): ";
		cin >> Rs;
		cout << "Rg (in Mega-Ohms): ";
		cin >> Rg;
		cout << "Id (in milli-amperes): ";
		cin >> Id;

		// print data
		cout << "\n\nVdd : " << setprecision(2) << fixed << Vdd << " volts." << endl;
		cout << "Rd : " << setprecision(2) << fixed << Rd << " ohms." << endl;
		cout << "Rs : " << setprecision(2) << fixed << Rs << " ohms." << endl;
		cout << "Rg : " << setprecision(2) << fixed << Rg << " Mega-ohms." << endl;
		cout << "Id : " << setprecision(2) << fixed << Id << " milli-amperes." << endl;
		cout << "Is the data all be verified correctly? (Y/N): ";
		cin >> correct_option;
		while (toupper(correct_option) != 'Y' && toupper(correct_option) != 'N')
		{
			cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
			cout << "Is the data all be verified correctly? (Y/N): ";
			cin >> correct_option;
		}
		if (toupper(correct_option) == 'N')
			cout << "\tPlease Reenter the data." << endl;
	} while (toupper(correct_option) == 'N');
	// calculation
	Id /= 1000; // convert Id from milli-amperes to amperes
	cout << endl << " Result and calculation" << endl;
	cout << "------------------------" << endl;
	cout << "V_GS = V_G - V_S" << endl;
	cout << "     = 0 - Id*Rs" << endl;
	cout << "     = " << -Id * Rs << " V" << endl << endl;
	cout << "V_DS = V_D - V_S" << endl;
	cout << "     = Vdd - Id (Rd + Rs)" << endl;
	cout << "     = " << Vdd - Id * (Rd + Rs) << " V" << endl << endl;
}

//made by Daniel for mosfet simulation
void mosfet()
{
	char correct_option;
	float Id, Vdd, R1, R2, R12, Rd, Vgs_th, K;  //for MOSFET

	cout << "\n_________________________________________________________" << endl;
	cout << " n-channel E-MOSFET voltage divider biased configuration" << endl;
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
	do
	{
		//key in data
		cout << "Vdd (in volts): ";
		cin >> Vdd;
		cout << "Rd (in Ohms): ";
		cin >> Rd;
		cout << "R1 (in Kilo-Ohms): ";
		cin >> R1;
		cout << "R2 (in Kilo-Ohms): ";
		cin >> R2;
		cout << "The thereshold voltage Vgs_th (in volts): ";
		cin >> Vgs_th;
		cout << "The devices pameter K (in milli-ampere/volt^2): ";
		cin >> K;

		// print data
		cout << "\n\nVdd : " << setprecision(2) << fixed << Vdd << " volts." << endl;
		cout << "Rd : " << setprecision(2) << fixed << Rd << " ohms." << endl;
		//cout << "Rs : " << setprecision(2) << fixed << Rs << " ohms." << endl;
		cout << "R1 : " << setprecision(2) << fixed << R1 << " Kilo-ohms." << endl;
		cout << "R2 : " << setprecision(2) << fixed << R2 << " Kilo-ohms." << endl;
		cout << "Vgs_th : " << setprecision(2) << fixed << Vgs_th << " volts." << endl;
		cout << "K  : " << setprecision(2) << fixed << K << " mA/V^2." << endl;
		cout << "Is the data all be verified correctly? (Y/N): ";
		cin >> correct_option;
		while (toupper(correct_option) != 'Y' && toupper(correct_option) != 'N')
		{
			cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
			cout << "Is the data all be verified correctly? (Y/N): ";
			cin >> correct_option;
		}
		if (toupper(correct_option) == 'N')
			cout << "\tPlease Reenter the data." << endl;
	} while (toupper(correct_option) == 'N');
	// calculation
	R12 = R2 / (R1 + R2);
	K /= 1000; // convert K from mA/V^2 to A/V^2
	Id = K * (R12 * Vdd - Vgs_th); // Id in amperes
	cout << endl << " Result and calculation" << endl;
	cout << "------------------------" << endl;
	cout << "V_GS = [R2 / (R1+R2)] * Vdd" << endl;
	cout << "     = " << R12 << " * " << Vdd << endl;
	cout << "     = " << R12 * Vdd << " V" << endl << endl;
	cout << "Id = K *( Vgs - Vgs_th)^2" << endl;
	cout << "   = " << K << " * ( " << R12 * Vdd << " - " << Vgs_th << " )^2" << endl;
	cout << "   = " << K * pow((R12 * Vdd - Vgs_th), 2) * 1000 << " mA" << endl << endl;
	cout << "V_DS = V_D - V_S" << endl;
	cout << "     = Vdd - (Id * Rd)" << endl;
	cout << "     = " << Vdd - (Id * Rd) << " V" << endl << endl;
}

void non_inverting()//Trang
{
	double Rf_NI, Ri_NI, Vin, Aol, Zin_NI, Zout_NI, Acl_NI, B, Zin, Zout;
	int opt;

	cout << "Question 10 :\n";
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
	cout << "Given:Vin = 5.0V, Rf = 220000 ohms,Ri = 10000 ohms and Aol = 200000 , Zin = 2000000 ohms, Zout = 75 ohms.\n";
	cout << "Determine the cloosed-loop voltage gain,Acl, the input and output impedances of the amplifier.\n";
	do
	{
		cout << "\nFormula Option:\n";
		cout << "1. Acl(NI) = 1 + (Rf/Ri) \n";
		cout << "2.  B = Ri / (Ri + Rf)\n";
		cout << "3. Zin(NI) = (1+ Aol*B) * Zin\n";
		cout << "4. Zout(NI) =  Zout / (1 + Aol * B)\n";
		cout << "5. Exit formula menu.\n";
		cout << "Enter your choice (1-5): ";
		cin >> opt;

		if (opt == 1)
		{
			cout << "1. Acl(NI) = 1 + (Rf/Ri) \n";
			cout << "Enter the value of Rf : \n";
			cin >> Rf_NI;//220000
			cout << "Enter the value of Ri : \n";
			cin >> Ri_NI;//10000
			Acl_NI = 1 + (Rf_NI / Ri_NI);
			cout << "Acl(NI) = " << fixed << setprecision(2) << Acl_NI << endl;//23.0
		}
		else if (opt == 2)
		{
			cout << "2. B = Ri / (Ri + Rf)\n";
			cout << "Enter the value of Rf : \n";
			cin >> Rf_NI;//220000
			cout << "Enter the value of Ri : \n";
			cin >> Ri_NI;//10000
			B = Ri_NI / (Ri_NI + Rf_NI);
			cout << "B = " << fixed << setprecision(4) << B << endl;//0.0435
		}
		else if (opt == 3)
		{
			cout << "3. Zin(NI) = (1+ Aol*B) * Zin\n";
			cout << "Enter the value of B : \n";
			cin >> B;//0.0435
			cout << "Enter the value of Aol : \n";
			cin >> Aol;//200000
			cout << "Enter the value of Zin: \n";
			cin >> Zin;//2000000
			Zin_NI = (1 + Aol * B) * Zin;
			cout << "Zin(NI) = " << fixed << setprecision(2) << Zin_NI << " ohms" << endl;//1.74G
		}

		else if (opt == 4)
		{
			cout << "4.Zout(NI) =  Zout / (1 + Aol * B)\n";
			cout << "Enter the value of Zout: \n";
			cin >> Zout;//75
			cout << "Enter the value of Aol: \n";
			cin >> Aol;//200000
			cout << "Enter the value of B: \n";
			cin >> B;//0.0435
			Zout_NI = Zout / (1 + Aol * B);
			cout << "Zout(NI) = " << fixed << setprecision(2) << Zout_NI << " ohms " << endl;//8.62m
		}
		else if (opt == 5)
		{
			cout << "Exiting formula menu...\n"; break;
		}
		else
		{
			cout << "Invalid optional!!Please enter the valid option(1-5): ";
		}
	} while (true);
}

void voltageFollower()//Trang
{
	double Rf_VF, Ri_VF, Aol, Zin_VF, Zout_VF, B, Zin, Zout;
	int opt;

	cout << "\nQuestion 11 :\n";
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
	cout << "Given: Rf =230000 ohms, Ri =10000 ohms , Aol = 200000 , Zin = 1000000 ohms, Zout = 70 ohms and B = 1.\n";
	cout << "Determine the input and output impedances of the amplifier.\n";
	do
	{
		cout << "\nFormula Option:\n";
		cout << "1. Zin(VF) = (1+ Aol*B) * Zin\n";
		cout << "2. Zout(VF) =  Zout / (1 + Aol)\n";
		cout << "3. Exit formula menu.";
		cout << "Enter your choice (1-3): ";
		cin >> opt;

		if (opt == 1)
		{
			cout << "1. Zin(VF) = (1+ Aol*B) * Zin\n";
			cout << "Enter the value of B: \n";
			cin >> B;//1
			cout << "Enter the value of Aol: \n";
			cin >> Aol;//200000
			cout << "Enter the value of Zin: \n";
			cin >> Zin;//1000000
			Zin_VF = (1 + Aol * B) * Zin;
			cout << "Zin(VF) = " << fixed << setprecision(2) << Zin_VF << " ohms" << endl;//200G
		}

		else if (opt == 2)
		{
			cout << "2.Zout(VF) =  Zout / (1 + Aol)\n";
			cout << "Enter the value of Zout: \n";
			cin >> Zout;//70
			cout << "Enter the value of Aol: \n";
			cin >> Aol;//200000
			Zout_VF = Zout / (1 + Aol);
			cout << "Zout(VF) = " << fixed << setprecision(2) << Zout_VF << " ohms" << endl;//350u
		}
		else if (opt == 3)
		{
			cout << "Exiting formula menu...\n"; break;
		}

		else
		{
			cout << "Invalid optional!!Please enter the valid option(1-3): ";
		}

	} while (true);
}
void invertingAmplifier()//Trang
{
	double Rf_I, Ri_I, Acl_I;
	int opt;

	cout << "\nQuestion 12 :\n";
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
	cout << "Given: Rf =210000 ohms, Ri =10000 ohms.\n";
	cout << "Determine the closed-loop voltage gain,Acl and the input impedance of the amplifier.\n";
	do
	{
		cout << "\nFormula Option:\n";
		cout << "1. Acl(I)= - (Rf/Ri)\n";
		cout << "2. Zin(I) ≅ Ri \n";
		cout << "3. Exit formula menu.";
		cout << "Enter your choice (1-3): ";
		cin >> opt;

		if (opt == 1)
		{
			cout << "1. Acl(I)= - (Rf/Ri)\n";
			cout << "Enter the value of Rf: \n";
			cin >> Rf_I;//210000
			cout << "Enter the value of Ri: \n";
			cin >> Ri_I;//10000
			Acl_I = -(Rf_I / Ri_I);
			cout << "Acl(I) = " << fixed << setprecision(2) << Acl_I << endl;//-21
		}
		else if (opt == 2)
		{
			cout << "2. Zin(I) ≅ Ri \n";
			cout << "Enter the value of Ri: \n";
			cin >> Ri_I;//10000
			cout << "Zin(I) = " << fixed << setprecision(2) << Ri_I << " ohms" << endl;//10000
		}

		else if (opt == 3)
		{
			cout << "Exiting formula menu...\n"; break;
		}

		else
		{
			cout << "Invalid optional!!Please enter the valid option(1-3): ";
		}
	} while (true);
}

//Simulator for Question 4
void simulator1_BJT()
{
	int calculate;
	double RIN_base, betaDC, RE, R2, R2_total, R1, VCC, VB, IC_mA, RC, VCE;
	cout << "BJT volatge-divider bised configuration.\n\n";

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

	cout << "\nChoose what you want to calculate:\n";
	cout << "(1. RIN_base and R2_total, 2. VB, 3. IC, 4. VCE): ";
	cin >> calculate;
	cout << endl;

	switch (calculate)
	{
	case 1:
		cout << "Enter the value of R2 (in ohm), RE (in ohm) and betaDC: ";
		cin >> R2 >> RE >> betaDC;
		RIN_base = betaDC * RE;

		if (RIN_base >= 10 * R2)
			R2_total = R2;
		else
			R2_total = 1.0 / ((1.0 / R2) + (1.0 / RIN_base));

		cout << "\nRIN_base = betaDC * RE\n";
		cout << "--> The value of RIN_base is " << fixed << setprecision(2) << RIN_base << " ohm.\n\n";

		cout << "\nif (RIN_base >= 10 * R2), R2_total = R2\n";
		cout << "if (RIN_base < 10 * R2), R2_total = 1.0 / ((1.0 / R2) + (1.0 / RIN_base))\n";
		cout << "--> The value of R2_total is " << fixed << setprecision(2) << R2_total << " ohm.\n\n";
		break;

	case 2:
		cout << "Enter the value of R1 (in ohm), R2_total (in ohm) and VCC (in V): ";
		cin >> R1 >> R2_total >> VCC;
		VB = R2_total / (R1 + R2_total) * VCC;
		cout << "\nVB = R2_total / (R1 + R2_total) * VCC\n";
		cout << "--> The value of VB is " << fixed << setprecision(2) << VB << " V.\n\n";
		break;

	case 3:
		cout << "Enter the value of VB (in V) and RE (in ohm): ";
		cin >> VB >> RE;
		IC_mA = (VB - 0.7) / RE; //note that the IC_mA at here is in A
		cout << "\nIC = (VB - 0.7) / RE\n";
		cout << "--> The value of IC is " << fixed << setprecision(2) << IC_mA * 1000 << " mA.\n\n";
		break;

	case 4:
		cout << "Enter the value of VCC (in V), IC (in mA), RC (in ohm) and RE (in ohm): ";
		cin >> VCC >> IC_mA >> RC >> RE;
		VCE = VCC - (IC_mA / 1000 * (RC + RE));
		cout << "\nVCE = VCC - IC * (RC + RE)\n";
		cout << "--> The value of VCE is " << fixed << setprecision(2) << VCE << " V\n\n";
		break;

	default:
		cout << "Invalid input! Please enter 1, 2, 3 or 4!\n\n";
	}

}

void simulator2_BJT()
{
	int calculate;
	double VCC, IC_mA, RC, VCE;
	cout << "\n\n\nQuestion 5: Determine the value of VCE when IC = 0.1mA and 0.2mA.\n\n";

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

	cout << "Enter the value of VCC (in V), IC (in mA) and RC (in ohm): ";
	cin >> VCC >> IC_mA >> RC;
	VCE = VCC - (IC_mA / 1000 * RC);

	cout << "\nVCE = VCC - (IC * RC)\n";
	cout << "The value for VCE is " << fixed << setprecision(2) << VCE << "V\n";

}

void simulator3_BJT()
{
	int calculate;
	double R1, R2, VB, VCC, RC, RE, betaAC, Rin_base, Rin_total, IE_mA, re, AV;

	cout << "\n\n\nQuestion 6: Find AV.\n\n";

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
	cout << " Hint: This is the Common-Emitter (CE) Amplifier with bypass capacitor (C2) in the emitter, not involving swapping process and no load resistance, RL.\n\n";

	cout << "\nChoose what you want to calculate:\n";
	cout << "(1. Rin_base, 2. Rin_total, 3. VB, 4. IE, 5. re, 6. AV): ";
	cin >> calculate;
	cout << endl;

	switch (calculate)
	{

	case 1:
		cout << "Enter the value of betaAC and RE (in ohm): ";
		cin >> betaAC >> RE;

		Rin_base = betaAC * RE;

		cout << "Rin_base = betaAC * RE\n";
		cout << "The value for Rin_base is " << fixed << setprecision(2) << Rin_base << "ohm\n";
		break;

	case 2:
		cout << "Enter the value of Rin_base (in ohm), R1 (in ohm) and R2 (in ohm): ";
		cin >> Rin_base >> R1 >> R2;

		if (Rin_base >= 10 * R2)
		{
			Rin_total = 1.0 / ((1.0 / R1) + (1.0 / R2));
		}

		else
		{
			Rin_total = 1.0 / ((1.0 / R1) + (1.0 / R2) + (1.0 / Rin_base));
		}

		cout << "\nif (Rin_base >= 10 * R2), Rin_total = 1.0 / ((1.0 / R1) + (1.0 / R2))";
		cout << "\n(Rin_base < 10 * R2), Rin_total = 1.0 / ((1.0 / R1) + (1.0 / R2) + (1.0 / Rin_base))\n";

		cout << "The value for Rin_total is " << fixed << setprecision(2) << Rin_total << "ohm\n";
		break;

	case 3:
		cout << "Enter the value of R1(in ohm), R2(in ohm) and VCC (in V): ";
		cin >> R1 >> R2 >> VCC;
		VB = R2 / (R1 + R2) * VCC;

		cout << "VB = R2 / (R1 + R2) * VCC\n";
		cout << "The value for VB is " << fixed << setprecision(2) << VB << "V\n";
		break;

	case 4:
		cout << "Enter the value of VB (in V) and RE (in ohm): ";
		cin >> VB >> RE;
		IE_mA = (VB - 0.7) / RE;

		cout << "IE = (VB - 0.7) / RE\n";
		cout << "The value for IE is " << fixed << setprecision(2) << IE_mA * 1000 << "mA\n";
		break;

	case 5:
		cout << "Enter the value of IE (in mA): ";
		cin >> IE_mA;
		re = 0.026 / (IE_mA / 1000);

		cout << "re = 0.026 / IE\n";
		cout << "The value for re is " << fixed << setprecision(2) << re << "ohm\n";
		break;

	case 6:
		cout << "Enter the value of RC (in ohm) and re (in ohm): ";
		cin >> RC >> re;
		AV = -RC / re;

		cout << "AV = -RC / re\n";
		cout << "The value of AV is " << fixed << setprecision(2) << AV << endl;
		break;

	default:
		cout << "Invalid input! Please enter 1, 2, 3, 4, 5 or 6!\n\n";
	}
}
// note for chapter 2
void notes_BJT()
{
	char study_analysis, dc_bias;

	cout << "Bipolar Junction Transistor (BJT) is 3 terminal device whose output current, voltage and power are controlled by its input current.\n";
	cout << "It is current-controlled device.\n";
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
	cout << "The above figure shows a PNP Bipolar Junction Transistor (BJT).\n\n";

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
	cout << "The above figure shows an NPN Bipolar Junction Transistor (BJT).\n\n";

	cout << "PNP BJTs are commonly used for calculations and related practical applications.\n\n";


	cout << "Note 1: In a BJT, VBE = 0.7V is because the base - emitter junction of the transistor is forward biased.\n";
	cout << "The 0.7 V is required to overcome the potential barrier(depletion region) of the PN junction.\n\n";

	cout << "Note 2: In a BJT, the emitter current is given by IE = IC + IB.\n";
	cout << "Since the base current IB is very small compared to the collector current IC(due to the large current gain beta), it is often neglected.\n";
	cout << "Therefore, IC is assumed to be approximately equal to IE.\n\n\n";

	do //if study_analysis not equal to 'Q', it will run this part again
	{
		cout << "Enter your choice of study (A for AC analysis, D for DC analysis, Q for quit):";
		cin >> study_analysis;
		study_analysis = toupper(study_analysis);
		cout << endl;

		if (study_analysis == 'A')
		{
			cout << "To analyze the ac operation of the amplifier in common emitter, we develop an ac equivalent circuit by using the following rules: \n";
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

			cout << "This is the Common-Emitter (CE) Amplifier with bypass capacitor (C2) in the emitter, not involving swapping process and no load resistance, RL.\n\n";

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
		}

		else if (study_analysis == 'D')
		{
			cout << "For DC analysis, the common-emitter configuration has two types of biasing methods: base bias and voltage divider bias.\n";
			cout << "To perform DC analysis, a DC equivalent circuit is developed by replacing the coupling and bypass capacitors with open circuits.\n";

			do //if dc_bias is not equal to 'B' or 'V',it will ask user to enter again
			{
				cout << "Enter your choice of bias (B for base bias, V for voltage divider bias): ";
				cin >> dc_bias;
				dc_bias = toupper(dc_bias);

				if (dc_bias == 'B')
				{
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

				}

				else if (dc_bias == 'V')
				{
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
					cout << "All equations are expressed in terms of voltage (V), current (A), and resistance (ohm), instead of using prefixes such as milli (m) or kilo (k).\n\n";

					cout << "[Equation 1 (for finding RIN_base)]: RIN_base = betaDC * RE\n\n\n";

					cout << "[Equation 2 (for finding R2_total)]: \n";
					cout << "\tCase 1: if RIN_base >= 10R2, R2_total = R2\n";
					cout << "\tCase 2: if RIN_base < 10R2, R2_total = 1 / ((1 / R2) + (1 / RIN_base))\n\n\n";

					cout << "[Equation 3 (for finding VB)]: VB = R2_total / (R1 + R2_total) * VCC\n\n\n";

					cout << "[Equation 4 (for finding IC)]: IC = (VB - 0.7) / RE\n\n\n";

					cout << "[Equation 5 (for finding VCE)]: VCE = VCC - IC * (RC + RE)\n\n\n";
				}

				else
					cout << "Invalid input! Please enter B or V!\n\n"; //if dc_bias is not equal to 'B' or 'V', it will ask user to enter again

			} while (dc_bias != 'B' && dc_bias != 'V');
		}

		else if (study_analysis == 'Q')
			cout << "Exiting notes program... Bye-bye (^-^)\n\n";

		else
			cout << "Invalid input! Please enter A, D or Q!\n\n"; //if study_analysis is not equal to 'A' or 'D' or 'Q', it will ask user to enter again

	} while (study_analysis != 'Q');
}

//notes for chapter 3
void notes_FET()
{
	char proceed;
		cout << "\n --------------------------------------------" << endl;
		cout << "| Chapter 3: Field Effect transistors (FETs) |" << endl;
		cout << " --------------------------------------------" << endl << endl;
		cout << "3.0 Introduction:" << endl;
		cout << "=================" << endl;
		cout << "the FET is a voltage-controlled device where voltage between" << endl;
		cout << "two of the terminals (gate and source) controls the current through the device." << endl << endl;
		cout << "A major feature of FETs is that they have very high input resistance." << endl;
		cout << "Hence, there are very useful in designing VLSI circuits since the devices draws " << endl;
		cout << "negligible currents due to there high input impedance." << endl << endl;
		cout << "There are two main types of FETs: " << endl;
		cout << "1) Junction field-effect transistor (JFET) " << endl;
		cout << "2) metal-oxide field-effect transistor (MOSFET)" << endl << endl;

		cout << "\nDo you want to proceed? ('Y' to proceed | 'N' to return notes selection): ";
		cin >> proceed;
		while (toupper(proceed) != 'Y' && toupper(proceed) != 'N')
		{
			cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
			cout << "Do you want to proceed? (Y/N): ";
			cin >> proceed;
		}
		if (toupper(proceed) == 'N') {
			cout << "Return to notes selection...";
			return;
		}


		cout << "\n3.1 Junction Field-Effect Transistor (JFET)" << endl;
		cout << "===========================================" << endl;
		cout << "the JFET has two regions: a p-type material and an n-type material." << endl;
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

		cout << "Note that the non-channel material axtually surrounds the channel like" << endl;
		cout << "\"a belt around the waist\". The non-channel material is diffused in the " << endl;
		cout << "relative material to form a channel and it is connected to the gate lead." << endl << endl;

		cout << "By providing a drain to source voltage Vds, it sypplying a current from the" << endl;
		cout << "drain to source (then we can say Id = Is , where is is Source current) " << endl;
		cout << "Next, by providing a negative voltage to gate-to-source and sets a reverse-bias " << endl;
		cout << "voltage between it and the pn junction become reverse biased." << endl << endl;

		cout << "In short, A JFET works by using the gate voltage to widen or narrow the" << endl;
		cout << "depletion layer, which controls the channel’s width and therefore regulates" << endl;
		cout << "the current flowing from drain to source." << endl << endl;

		cout << "\nDo you want to proceed? ('Y' to proceed | 'N' to return notes selection): ";
		cin >> proceed;
		while (toupper(proceed) != 'Y' && toupper(proceed) != 'N')
		{
			cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
			cout << "Do you want to proceed? (Y/N): ";
			cin >> proceed;
		}
		if (toupper(proceed) == 'N') {
			cout << "Return to notes selection...";
			return;
		}

		cout << "\n3.2 JFET Characteristics and Parameters" << endl;
		cout << "=======================================" << endl;
		cout << "The drain current can be determine by using the equation of the" << endl;
		cout << "JFET transfer characteristics:" << endl;
		cout << " _________________________________" << endl;
		cout << "| Id = Idss [1-(Vgs / Vgs_off)]^2 |" << endl;
		cout << " ---------------------------------" << endl;
		cout << "the meaning of parameters is shown below: " << endl;
		cout << "Id: Drain current \nIdss: maximum drain current \nVgs: volatge gate-to-source \nVgs_off: cutoff voltage" << endl;
		cout << "notes that the Idss and the Vgs_off can be found in related JFET datasheet." << endl << endl;

		cout << "Besides, the JFET forward transconductance (gm) is the slope of the curve." << endl;
		cout << "The unit of it is siemens (S), it is used to calculate the voltage gain in an amplifier." << endl;
		cout << "It can be determined by following equation: " << endl;
		cout << " ____________________________" << endl;
		cout << "| gm = gm_0[1-(Vgs/Vgs_off)] |" << endl;
		cout << " ----------------------------" << endl;
		cout << "Where gm_0 is the gm at Vgs =0V , and will be given in the data sheets." << endl << endl;

		cout << "\nDo you want to proceed? ('Y' to proceed | 'N' to return notes selection): ";
		cin >> proceed;
		while (toupper(proceed) != 'Y' && toupper(proceed) != 'N')
		{
			cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
			cout << "Do you want to proceed? (Y/N): ";
			cin >> proceed;
		}
		if (toupper(proceed) == 'N') {
			cout << "Return to notes selection...";
			return;
		}

		cout << "\n3.3 JFET Biasing" << endl;
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
		cout << "Note that the value of source resistor Rs must be greater than Rs_min = |Vgs/Id|,to establishing a JFET bias point" << endl;
		cout << "The step to determine Vgs and Vds can be explained in JFET self biasing simulation." << endl;
		cout << "\nDo you want jump to JFET simulation? (Y/N):";
		cin >> proceed;
		while (toupper(proceed) != 'Y' && toupper(proceed) != 'N') {
			cout << "INPUT ERROR, input (Y/N)." << endl;
			cout << "\nDo you want jump to JFET simulation? (Y/N):";
			cin >> proceed;
		}
		if (toupper(proceed) == 'Y') // added by Daniel to debug
			jfet();

		cout << "\nDo you want to proceed? ('Y' to proceed | 'N' to return notes selection): ";
		cin >> proceed;
		while (toupper(proceed) != 'Y' && toupper(proceed) != 'N')
		{
			cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
			cout << "Do you want to proceed? (Y/N): ";
			cin >> proceed;
		}
		if (toupper(proceed) == 'N') {
			cout << "Return to notes selection...";
			return;
		}

		cout << "\n3.4 The Metal-Oxide Semiconductor Field-Effect Transistor (MOSFET)" << endl;
		cout << "==================================================================" << endl;
		cout << "There are two types of MOSFET: D-MOSFET and E-MOSFET." << endl;
		cout << "Boths of them are having p and n channel. The construction of n-channel MOSFET was shown below." << endl << endl;

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
		cout << "When a positive gate - to - source voltage is applied, the n - channel MOSFET operates" << endl;
		cout << "in the enhancement - mode." << endl;
		cout << "*Note that E-MOSFET only can operates in enhancement mode while D-MOSFET can operates in both mode." << endl;

		cout << "\nDo you want to proceed? ('Y' to proceed | 'N' to return notes selection): ";
		cin >> proceed;
		while (toupper(proceed) != 'Y' && toupper(proceed) != 'N')
		{
			cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
			cout << "Do you want to proceed? (Y/N): ";
			cin >> proceed;
		}
		if (toupper(proceed) == 'N') {
			cout << "Return to notes selection...";
			return;
		}

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

		cout << "\nDo you want to proceed? ('Y' to proceed | 'N' to return notes selection): ";
		cin >> proceed;
		while (toupper(proceed) != 'Y' && toupper(proceed) != 'N')
		{
			cout << "Invalid input, please ENTER 'Y' or 'N'." << endl;
			cout << "Do you want to proceed? (Y/N): ";
			cin >> proceed;
		}
		if (toupper(proceed) == 'N') {
			cout << "Return to notes selection...";
			return;
		}

		cout << "\n3.6 E-MOSFET Biasing " << endl;
		cout << "=====================" << endl;
		cout << "The most common biasing for E-MOSFET is voltage-divider bias and drain-feedback bias" << endl;
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
		cin >> proceed;
		while (toupper(proceed) != 'Y' && toupper(proceed) != 'N') {
			cout << "INPUT ERROR, input (Y/N)." << endl;
			cout << "\nDo you want jump to E-MOSFET simulation? (Y/N):";
			cin >> proceed;
		}
		if (toupper(proceed) == 'Y') // added by Daniel to debug
			mosfet();

		cout << "\nCongrats!! you are done on reading the notes for Chapter 3. (*^V^*)/" << endl;
		cout << "PRESS any key to return to note selection\nor PRESS 'R' to return to the introduction of Chapter 3." << endl;
		cin >> proceed;
		if (toupper(proceed) == 'R')
			notes_FET();
}