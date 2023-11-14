//
//  main.cpp
//  Group Project
//
//  Created by Kiera Chase on 11/6/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

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
                j = rand() % a_list.size();
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
    srand( static_cast<unsigned int>(time(nullptr))); // This is needed in Xcode to make rand() work
    
    
    // open answers.txt and questions.txt in order to get questions and answers
    ifstream inFS_Answers;
    ifstream inFS_Questions;
        // this is one of the weird xcode things. It needs the full path to open the file. In other compilers it should just be "answers.txt" and "questions.txt"
    inFS_Answers.open("/Users/hannahtrotter/Downloads/answers.txt");
    inFS_Questions.open("/Users/hannahtrotter/Downloads/questions.txt");
    
    
    // answers_v short for "answers vector". Names subject to change, I just had to pick something
    vector<string> answers_v;
    vector<string> questions_v;
        // (delete later) Kiera's original test vector = {"Leopard", "Butterfly", "Tiger", "Lion", "Cheetah", "Magpie", "Goldfish", "Dog"};
    
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
    
    string question;
    int position = rand()% sizeof(answers_v);
    char user_ans, correct_ans = generateAnswers(answers_v, position, questions_v, question);
    
    // This can be improved for sure... just how I was testing the rest of my code
    cin >> user_ans;
    if (user_ans == correct_ans) {
        cout << "Correct" << endl;
    }
    else {
        cout << "Incorrect" << endl;
    }
    
}
