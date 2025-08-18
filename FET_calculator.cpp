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
};
void cal(int);
void note();
int quiz();
void getinfo(User&);
void userlist(User*);
void menu(int, User[], int);
int findslot(User[]);
int check(float*, int&);
float fun1();
float fun2();
float fun3();
void clamper();
void jfet(); //Daniel
void mosfet(); //Daniel
const int num = 100;


int main() {
	int opt, userindex = -1;

	cout << "Welcome to Basic Electronic." << endl;
	User stu[num] = {};
	stu[1].Name = "Teng Zi Kang";
	stu[1].ID = 2404458;
	stu[1].score = 5;
	fstream list;
	list.open("Userlist", ios::app);
	list.close();
	userindex = findslot(stu);
	getinfo(stu[userindex]);


	userlist(stu);

	do {
		cout << "Choose the action you want to proceed: \n1. note \n2. quiz \n3. stimulator \n4. userlist \n5. end:" << endl;
		cout<< "Enter your choice (i.e. 1, 2, 3, 4, 5 out):";
		cin >> opt;
		menu(opt, stu, userindex);
	} while (opt != 4);

	return 0;
}
void menu(int opt, User stu[], int userindex) {
	int a, b;
	switch (opt) {
	case 1:
		note();
		break;
	case 2:

		//stu[userindex].score = quiz();
		b = quiz();
		cout << "Score updated:" << b << endl;
		break;
	case 3:
		do {
			cout << "Select the type of stimulator(\n1.belum ada,\n2.clamper,\n3.belum siap, \n4. empty "
				<<"\n5.JFET(Self bias) \n6.MOSFET(voltage divider bias) \n* Enter '-999' to return):";
			cin >> a;
			cal(a); //select stimulator in menu
		} while (a != -999);
		break;
	case 4:
		userlist(stu);
		break;
	case 5:
		cout << "Programme end." << endl;

		break;
	default:
		cout << "Invalid input try to choose again.(1,2,3,4)" << endl;
	}
}
int quiz() {
	int b, points;
	char a;
	float answer[20] = {};
	do {
		cout << "Choose the question you want to answer(13 out):";
		cin >> b;
		switch (b) {
		case 1:
			cout << "1";//insert your question here
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					fun1();
				}
				//insert your calculator here
			} while (a == 'Y' || a == 'y');
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


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					clamper();
				}
			} while (a == 'Y' || a == 'y');
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


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					clamper();
				}
			} while (a == 'Y' || a == 'y');
			cout << "Enter the answer of Vout(+ve):";
			cin >> answer[3];
			cout << "Enter the answer of Vout(-ve):";
			cin >> answer[4];
			break;
		case 4:
			cout << "4";
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					fun1();
				}
			} while (a == 'Y' || a == 'y');
			cout << "Enter the answer:";
			cin >> answer[5];
			break;
		case 5:
			cout << "5";
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					fun1();
				}
			} while (a == 'Y' || a == 'y');
			cout << "Enter the answer:";
			cin >> answer[6];
			break;
		case 6:
			cout << "6";
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					fun1();
				}
			} while (a == 'Y' || a == 'y');
			cout << "Enter the answer:";
			cin >> answer[7];
			break;
		case 7:
			cout << "Qustion 7 Drain current calculation from datasheet";
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					fun1();
				}
			} while (a == 'Y' || a == 'y');
			cout << "Enter the answer:";
			cin >> answer[8];
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
				}
				if (toupper(a) == 'Y') // added by Daniel to debug
					jfet();
			} while (toupper(a) == 'Y');
			cout << "Enter the answer for V_DS (in volts and round to two decimals):";
			cin >> answer[9];
			cout << "Enter the answer for V_GS (in volts and round to two decimals):";
			cin >> answer[10];

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
				}
				if (toupper(a) == 'Y') // added by Daniel to debug
					mosfet();
			} while (toupper(a) == 'Y');
			cout << "Enter the answer for V_DS (in volts and round to two decimals):";
			cin >> answer[11];
			cout << "Enter the answer for V_GS (in volts and round to two decimals):";
			cin >> answer[12];
			break;

		case 10:
			cout << "10";

			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					fun1();
				}
			} while (a == 'Y' || a == 'y');
			cout << "Enter the answer:";
			cin >> answer[13];
			break;
		case 11:
			cout << "11";
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					fun1();
				}
			} while (a == 'Y' || a == 'y');
			cout << "Enter the answer:";
			cin >> answer[14];
			break;
		case 12:
			cout << "12";
			do {
				cout << "\nDo you want to use a stimulator?(Y/N):";
				cin >> a;


				while (a != 'Y' && a != 'y' && a != 'N' && a != 'n') {
					cout << "INPUT ERROR, input (Y/N)." << endl;
				}
				if (a == 'Y' || a == 'y') {
					fun1();
				}
			} while (a == 'Y' || a == 'y');
			cout << "Enter the answer:";
			cin >> answer[15];
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
			break;
		case 3:
			cout << "chap 3." << endl;
			break;
		case 4:
			cout << "chap 4." << endl;
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
		fun3();
		break;
	case 4:
		cout << "equation" << endl;
		break;
	case 5:
		//jfet self biase configuration
		jfet();
		break;
	case 6:
		//mosfet 
		mosfet();
		break;
	case -999:
		cout << "You have returned to quizz" << endl;
		break;
	default:
		cout << "Invalid input" << endl;
		break;
	}

}
void getinfo(User& r) {
	cout << "Enter your name:";
	cin.ignore();//ignore \n from menu.
	getline(cin, r.Name);
	cout << "Enter your student ID:";
	cin >> r.ID;
	r.score = 0;

}
void userlist(User p[]) {
	for (int i = 0; i < 10; i++) {
		cout << p[i].Name << endl;
		cout << p[i].ID << endl;
		cout << p[i].score << endl;

	}
}

int findslot(User stu[]) {
	for (int i = 0; i < num; i++) {
		if (stu[i].ID == 0) {
			return i;
		}
		else {
			return -1;
		}
	}
}

int check(float* a, int& points) {
	points = 0;
	float checkans[20] = { 0,24.3,4.3,-6.8,-36.8,5,6,7,8,8.9,-1.1,12.7,3.13,14,15,16,17,18,19,20 }; //insert your answer here
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
float fun2() {
	int a = 4;
	return a;
}
float fun3() {
	int a = 5;
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
