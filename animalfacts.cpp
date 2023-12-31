//
//  CSCE A201
//  Group Project
//  Animal Fact Questionaire
//  Kiera Chase, Riley Petty, and Hannah Trotter
//


#include <ctime>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

bool findNum(int num, int nums[], int size = 4)
{
    /*
     Determines if a value is an element in a given array

     Inputs:
        num: int to try to find
        nums: int array to search
        size: int of size of array

     Outputs:
        True if value is in array, else false
     */

    for (int i = 0; i < size; i++) {
        if (nums[i] == num) {
            return true;
        }
    }
    return false;
}


char generateAnswers(vector<string> a_list, int a_index, vector<string> q_list, string &correctQuestion)
{
    /*
     Generates a list of random answers including the correct answer

     Inputs:
        a_list: vector of strings of the possible answers for user to select
        a_index: int of index in a_list with correct answer
        q_list: vector of strings of the questions
        correctQuestion: question at same index as correct question

     Outputs:
        Prints a list of answers for user to choose from. Returns char 'A', 'B', 'C', or 'D' corresponding to the position of the correct answer.
        updates correctQuestion as a reference variable
     */

    int j, options[4] = {-1, -1, -1, -1};

    // Randomly pick position of real answer
    int a_pos = rand() % 4;

    // Add real answer and wrong answers to options[]
    for (int i = 0; i < 4; i++) {
        // Put real answer into options[] at its location
        if (i == a_pos) {
            options[i] = a_index;
            // stores question at a_index in correctQuestion (reference varaible)
            correctQuestion = q_list[a_index];
        }
        // Add wrong answers by randomly selecting unique indices from remaining a_list
        else {
            do {
                j = rand() % (a_list.size() - 1);
            } while (findNum(j, options) || (j == a_index));
            options[i] = j;
        }
    }

    // prints question
    cout << correctQuestion << endl;
    // Print answer list
    for (int i = 0; i < 4; i++) {
        // Print lettered list
        switch (i) {
            case 0:
                cout << "A. ";
                break;
            case 1:
                cout << "B. ";
                break;
            case 2:
                cout << "C. ";
                break;
            case 3:
                cout << "D. ";
                break;
        }
        // Print answer content
        cout << a_list.at(options[i]) << endl;
    }

    // Return position of correct answer
    switch (a_pos) {
        case 0:
            return 'A';
        case 1:
            return 'B';
        case 2:
            return 'C';
        case 3:
            return 'D';
    }
    return 'Z';
}


int main() {
    srand( static_cast<unsigned int>(time(nullptr)));

    char playAgain = 'Y';
    int quesCount = 0; //question # (i.e Q1)
    int userPoints = 0; //total correct guesses
    char xcode; // to customize code for Xcode users
    string answersTXT, questionsTXT;

    // open answers.txt and questions.txt in order to get questions and answers
    ifstream inFS_Answers;
    ifstream inFS_Questions;

    // for whatever reason Xcode seems to require the full path instead of just "answer.txt" and "questions.txt"
    cout << "Are you running this on Xcode? (Y/N): ";
    cin >> xcode;
    cout << endl;
    if (xcode == 'Y' || xcode == 'y') {
        // we used Hannah's path here for reference, other Xcode users must edit this to match them
        answersTXT = "/Users/hannahtrotter/Downloads/answers.txt";
        questionsTXT = "/Users/hannahtrotter/Downloads/questions.txt";
    }
    else {
        answersTXT = "answers.txt";
        questionsTXT = "questions.txt";
    }

    inFS_Answers.open(answersTXT);
    inFS_Questions.open(questionsTXT);

    vector<string> answers_v;
    vector<string> questions_v;

    cout << "----------------------------" << endl;
    cout << " Animal Facts Questionnaire" << endl;
    cout << "----------------------------" << endl;
    cout << "\tCreated by:" << endl;
    cout << "\tKiera Chase\n\tRiley Petty\n\tHannah Trotter" << endl;
    cout << "----------------------------\n" << endl;

    // while loop stores each line from answers.txt and questions.txt in the corresponding vecotrs
    while ((!inFS_Answers.fail()) && (!inFS_Questions.fail())){
        // declaring temp variables for the loop
        string tempAnswer;
        string tempQuestion;
        int i = 0;

        // getting
        getline(inFS_Answers, tempAnswer);
        getline(inFS_Questions, tempQuestion);

        // put tempAnswer and tempQuestion in vectors
        answers_v.push_back(tempAnswer);
        questions_v.push_back(tempQuestion);

        i++;

    }

    // while loop happens while user doesn't enter 'N' or 'n' and the size of the vectors is greater than 3 full multiple choice
    while ((playAgain != 'N') && (playAgain != 'n') && (quesCount < 20) ){
        string question;
        int position = rand() % (sizeof(answers_v) - 1);
        cout << "Q" << (quesCount + 1) << ". ";
        char user_ans, correct_ans = generateAnswers(answers_v, position, questions_v, question);

        cout << "\nYour answer: ";
        cin >> user_ans; //takes user guess

        if (user_ans == correct_ans) {
            ++userPoints;
            cout << "\nCorrect!\n" << endl;
            if (quesCount < 19){
                cout << "Play again? (Y/N): ";
                cin >> playAgain;
                cout << endl;
            }
        }
        else {
            cout << "\nIncorrect." << endl;
            cout << "Correct answer is: " << answers_v[position] << "\n" << endl;
            if (quesCount < 19){
                cout << "Play again? (Y/N): ";
                cin >> playAgain;
                cout << endl;
            }

        }
        
        // erases question and answer used from vectors to avoid duplicate
        answers_v.erase(answers_v.begin() + position);
        questions_v.erase(questions_v.begin() + position);
        

        ++quesCount; //updates question count to next num (i.e. Q1 -> Q2)
    }
    cout << "Total correct: " << userPoints << " of " << quesCount << endl;


    // closes answers.txt and questions.txt
    inFS_Answers.close();
    inFS_Questions.close();
}
