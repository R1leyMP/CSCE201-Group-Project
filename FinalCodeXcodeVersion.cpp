//
//  main.cpp
//  Group Project
//  Animal Fact Questionaire
//  Kiera Chase, Riley Petty, and Hannah Trotter
//
//  Created by Kiera Chase on 11/6/23.
//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>

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
                if (j == a_index){
                    while (j==a_index){
                        j = rand() % (a_list.size()-1);
                    }
                }
            } while (findNum(j, options));
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
    
    // open answers.txt and questions.txt in order to get questions and answers
    ifstream inFS_Answers;
    ifstream inFS_Questions;

    // in Xcode for whatever reason in order for the program to run and access the files its requires the full path. Otherwise it would just be "answer.txt" and "questions.txt"
    inFS_Answers.open("/Users/hannahtrotter/Downloads/answers.txt");
    inFS_Questions.open("/Users/hannahtrotter/Downloads/questions.txt");
    
    vector<string> answers_v;
    vector<string> questions_v;

    /* Added by Riley Petty but code did not work as intended in Xcode/MacOS
     cout << "TITLE PAGE" << endl;
    system ("PAUSE");  //screen clear code
    system ("CLS");
    */
    
    
    // while loop stores each line from answers.txt and questions.txt in the corresponding vecotrs
    while ((!inFS_Answers.fail()) && (!inFS_Questions.fail())){
        // declaring temp variables for the loop
        string tempAnswer;
        string tempQuestion;
        
        // getting
        getline(inFS_Answers, tempAnswer);
        getline(inFS_Questions, tempQuestion);
        
        // put tempAnswer and tempQuestion in vectors
        answers_v.push_back(tempAnswer);
        questions_v.push_back(tempQuestion);
    }
    
    while (playAgain != 'N' && playAgain != 'n'){
        string question;
        int position = rand() % (sizeof(answers_v) - 1);
        cout << "Q" << (quesCount + 1) << ". ";
        char user_ans, correct_ans = generateAnswers(answers_v, position, questions_v, question);
        
        cin >> user_ans; //takes user guess
        
        if (user_ans == correct_ans) {
            ++userPoints;
            cout << "Correct!" << endl;
            cout << "Play again? (Y/N): ";
            cin >> playAgain;
            cout << endl;
            // did not work as intended in Xcode: system ("CLS"); //screen clear
        }
        else {
            cout << "Incorrect." << endl;
            cout << "Correct answer is: " << answers_v[position] << endl;
            cout << "Play again? (Y/N): ";
            cin >> playAgain;
            cout << endl;
            // did not work as intended in Xcode:system ("CLS");
        }

        ++quesCount; //updates question count to next num (i.e. Q1 -> Q2)
    }
    
    // closes questions.txt and answers.txt
    inFS_Answers.close();
    inFS_Questions.close();
    
    // displays score
    cout << "Total correct: " << userPoints << " of " << quesCount << endl;
    

}
