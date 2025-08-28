#include <iostream>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

struct Test1 {
    int num; //Qustion No.
    string question;
    string objective_A;
    string objective_B;
    string objective_C;
    string objective_D;
    char ans;
    bool isDeleted;
};

Test1 Quizz[10]; //store 10 test1 questions
int Test1Count = 0; //count question from file
const int Question_Numbers = 10;

// quizz function for user
void quizz();
int checkAns(char ans, char answer);
void shuffle(int* temp, int Question_Numbers);//temporary storage for the sequence array

//quizz function for host
void createQuizz();
void editQuizz();
void deleteQuizz(int num);

//file operation
void saveTest1();
void LoadTest1();

int main()
{
    int tryrun;
    LoadTest1();
    cout << "Test count:" << Test1Count <<endl;//@@@test@@@
    cout << "press int to start (0 to end create question)" << endl;
	cin >> tryrun;
	cin.ignore();
    while (tryrun != 0)
    { 
        createQuizz(); 
        cout << "Test count:" << Test1Count << endl;//@@@test@@@
        cout << "press int to start (0 to end create question)" << endl;
        cin >> tryrun;
        cin.ignore();
    } 
    cout << "press 1 to end edit and jump to quizz:";
    cin >> tryrun;
    while (tryrun != 1)
    {
        editQuizz();
        cout << "Test count:" << Test1Count << endl;//@@@test@@@
        cout << "press int to start (1 to end edit question)" << endl;
        cin >> tryrun;
        cin.ignore();
    }
    
	quizz();
	return 0;
}

void quizz()
{
	/* this function is to let user answer 10 question made 
    by host and each user the sequence will be shuffled*/
	
	int sequence[Question_Numbers] = { 1,2,3,4,5,6,7,8,9,10 };
    int Num = 1, score=0;
    char ans;
    
    shuffle(sequence,Question_Numbers);
	
    for (int i = 0; i < Question_Numbers; i++) //i<10
    {
        if ((!Quizz[sequence[i] - 1].question.empty()) && (Quizz[sequence[i] - 1].isDeleted == false)) {
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
    cout << "End of Quizz. Your total score is " << score << " Out of " << Num-1 << endl;
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

int checkAns(char response,char answer )
{
    int score = 0;
    if (response==answer)
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

void createQuizz()
{
    
    Test1 newQuizz;
    newQuizz.num = Test1Count+1;
    
    if (Test1Count >= 10) {
        cout << "The questions are full. Please delete before creating.\n";
        return;
    }

    cout << "Enter your question for Question " << newQuizz.num << ": " << endl;
    getline(cin, newQuizz.question);

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

    cout << "Answer for Question " << newQuizz.num << " : ";
    cin >> newQuizz.ans;
    cin.ignore();

    newQuizz.isDeleted = false;

    Quizz[Test1Count++] = newQuizz;
    saveTest1();
    cout << "\nThe Question was save successfully..." << endl;

    //back to menu....
}

void editQuizz()
{
    int number,option;
    Test1 EditQuizz;
    do
    {
        cout << "Test count:" << Test1Count << endl;//@@@test@@@
    for (int i = 0;i < Test1Count;i++)
    {
        if (Quizz[i].isDeleted == false) {
            cout << "Question " << Quizz[i].num << ": " << endl;
            cout << Quizz[i].question << endl << endl;
        }
    }
   
    cout << "Enter the question you want to eddit (0 to cancel):";
    cin >> number;
    if (number == 0) {
        cout << "Cancel successfully, exit to menu..." << endl;
        return;
    }
        EditQuizz = Quizz[number - 1]; //temporary storage
        do {
            cout << "Enter the part you want to edit in Question " << number << ":\n"
                << "1. Question\n"
                << "2. Option A\n"
                << "3. Option B\n"
                << "4. Option C\n"
                << "5. Option D\n"
                << "6. Correct answer\n"
                << "7. Delete\n"
                << "8. cancel\n"
                << "Enter (1-8):";
            cin >> option;
            cin.ignore();
            if (option == 7)
            {
                deleteQuizz(number - 1);
                break;
            }
            else if (option == 8) break;
            else{
                switch (option)
                {
                case 1:
                {
                    cout << "Question: " << EditQuizz.question << endl;
                    cout << "Enter your new Question:" << endl;
                    getline(cin, EditQuizz.question);
                    break;
                }
                case 2:
                {
                    cout << "A: " << EditQuizz.objective_A << endl;
                    cout << "Enter your new Option A:" << endl;
                    getline(cin, EditQuizz.objective_A);
                    break;
                }
                case 3:
                {
                    cout << "B: " << EditQuizz.objective_B << endl;
                    cout << "Enter your new Option B:" << endl;
                    getline(cin, EditQuizz.objective_B);
                    break;
                }
                case 4:
                {
                    cout << "C: " << EditQuizz.objective_C << endl;
                    cout << "Enter your new Option C:" << endl;
                    getline(cin, EditQuizz.objective_C);
                    break;
                }
                case 5:
                {
                    cout << "D: " << EditQuizz.objective_D << endl;
                    cout << "Enter your new Option D:" << endl;
                    getline(cin, EditQuizz.objective_D);
                    break;
                }
                case 6:
                {
                    cout << "Answer: " << EditQuizz.ans << endl;
                    cout << "Enter your new Answer:" << endl;
                    cin >> EditQuizz.ans;
                    cin.ignore();
                    break;
                }
                default: cout << "Invalid option, please Enter (1-7)";
                }
                Quizz[number - 1] = EditQuizz;
                Quizz[number - 1].isDeleted = false;
                saveTest1();
                cout << "Editted successfully..." << endl;
            }
        } while (option != 8);
        
    }while (number != 0);
}

void deleteQuizz(int num)
{
    Quizz[num].isDeleted = true;
    for (int i = num + 1; i < Test1Count; i++)
        Quizz[i].num = i;
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
        if(!getline(inFile, line)) break;
        tempQuizz.ans = line[0]; //store ans to char from string line[0] means the first character.
        tempQuizz.isDeleted = false;
        Quizz[Test1Count++] = tempQuizz;

		if (Test1Count >= Question_Numbers) break; //break if exceed the limit
        if (line.empty()) break;
    }
    inFile.close();
    
}