//
//  main.cpp
//  Group Project
//
//  Created by Kiera Chase on 11/6/23.
//

#include <iostream>
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

char generateAnswers(vector<string> a_list, int a_index)
{
    /*
     Generates a list of random answers including the correct answer
     
     Inputs:
        a_list: vector of strings of the possible answers for user to select
        a_index: int of index in a_list with correct answer
     
     Outputs:
        Prints a list of answers for user to choose from. Returns char 'A', 'B', 'C', or 'D' corresponding to the position of the correct answer.
     */
    
    int j, options[4] = {-1, -1, -1, -1};
    
    // Randomly pick position of real answer
    int a_pos = rand() % 4;
    
    // Add real answer and wrong answers to options[]
    for (int i = 0; i < 4; i++) {
        // Put real answer into options[] at its location
        if (i == a_pos) {
            options[i] = a_index;
        }
        // Add wrong answers by randomly selecting unique indices from remaining a_list
        else {
            do {
                j = rand() % a_list.size();
            } while (findNum(j, options));
            options[i] = j;
        }
    }
    
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
    
    // answers_v short for "answers vector". Names subject to change, I just had to pick something
    vector<string> answers_v = {"Leopard", "Butterfly", "Tiger", "Lion", "Cheetah", "Magpie", "Goldfish", "Dog"};
    
    char user_ans, correct_ans = generateAnswers(answers_v, 5);
    
    // This can be improved for sure... just how I was testing the rest of my code
    cin >> user_ans;
    if (user_ans == correct_ans) {
        cout << "Correct" << endl;
    }
    else {
        cout << "Incorrect" << endl;
    }
}
