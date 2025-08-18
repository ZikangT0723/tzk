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
void userlist(User *);
void menu(int,User[],int);
int findslot(User[]);
int check(float*,int&);
float fun1();
float fun2();
float fun3();
void clamper();
const int num = 100;


int main() {
	int opt,userindex=-1;
	
	cout << "Welcome to Basic Electronic." << endl;
	User stu[num] = {};
	stu[1].Name = "Teng Zi Kang";
	stu[1].ID = 2404458;
	stu[1].score = 5;
	fstream list;
	list.open("Userlist",ios::app);
	list.close();
	userindex = findslot(stu);
	getinfo(stu[userindex]);

	
	userlist(stu);

    do {
			cout << "Choose the action you want to proceed 1. note, 2. quiz, 3. stimulator, 4. userlist, 5. end:(i.e. 1,2,3,4,5 out)";
			cin >> opt;
			menu(opt, stu, userindex);
	} while (opt != 4);
	
	return 0;
}
void menu(int opt, User stu[], int userindex) {
	int a,b;
	switch (opt) {
	case 1:
		note();
		break;
	case 2:

		//stu[userindex].score = quiz();
		b = quiz();
		cout << "Score updated:" << b  << endl;
		break;
	case 3:
		do {
			cout << "Select the type of stimulator(1.,2.clamper,3., 4.return):";
			cin >> a;
			cal(a); //select stimular in menu
		} while (a != 4);
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
	int b,points;
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
			cout << "7";
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
		case 8:
			cout << "8";
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
			cin >> answer[9];
			break;
		case 9:
			cout << "9";
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
			cin >> answer[10];
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
				cin >> answer[11];
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
			cin >> answer[12];
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
			cin >> answer[13];
			break;
		case 13:
			cout << "You have returned to main function." << endl;
			break;
		default:
			cout << "Invalid input." << endl;
			break;
		}
		
		
		
		} while(b != 13);
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
		cout << "You have returned to quizz" << endl;
		break;

	default:
		cout << "Invalid input" << endl;
		break;
	 }
	
}
void getinfo(User &r) {
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

int check(float* a,int &points) {
	points=0;
	float checkans[20] = { 1,24.3,4.3,-6.8,-36.8,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 }; //insert your answer here
	for (int i = 0; i < 20; i++) {
		if (checkans[i] >= 0) {
			if ((checkans[i] - (checkans[i] * 5 / 100)) <= *(a + i) && *(a + i) <= (checkans[i] + (checkans[i] * 5 / 100))) {
				points++;
				
			}
		}
		else{
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


