/*
 Assignment 1 Question 6
 Kiera Chase
 CSCE A201
 Dr. Kamran Siddique
 October 16, 2023
 */

#include <iomanip>
#include <iostream>

using namespace std;

int findExtrema(int list[3][4], int s = 1)
{
    /*
     Finds the smallest or largest integer in an array
     
     Inputs:
        list: int array with three rows and four columns
        s: int initialized to 1 to find largest number, input -1 to find smallest number
     
     Output:
        Returns int of smallest or largest number
     */
    
    int extrema = list[0][0];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (extrema * s < list[i][j] * s) {
                extrema = list[i][j];
            }
        }
    }
    
    return extrema;
}

double calculateMean(int nums[], int size)
{
    /*
     Calculates the mean of an array of numbers
     
     Inputs:
        nums[]: array of ints to be the numbers
        size: int of the size of the array
     
     Outputs:
        The mean of the numbers as a double
     */
    
    double temp = 0;
    
    // Add up all numbers in array
    for (int i = 0; i < size; i++) {
        temp += nums[i];
    }
    
    // Divide by the number of numbers and return
    return temp / size;
}


int main()
{
    int marks[3][4] = {
        {78, 60, 79, 88},
        {85, 80, 77, 91},
        {89, 78, 81, 75}
    };
    
    // Print table header
    cout << "\t\t\t\t" << "subject[0]" << "\t\t" << "subject[1]" << "\t\t" << "subject[2]" << "\t\t" << "subject[3]" << endl;
    
    // Print table body
    for (int i = 0; i < 3; i++) {
        cout << "student[" << i << "]" << "\t\t";
        for (int j = 0; j < 4; j++) {
            cout << marks[i][j] << "\t\t\t\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Compute highest and lowest marks, print
    cout << "Lowest mark: " << findExtrema(marks, -1) << endl;
    cout << "Highest mark: " << findExtrema(marks) << endl;
    
    // Compute average mark for each student,
    for (int i = 0; i < 3; i++) {
        cout << "The average mark for student[" << i << "] is ";
        cout << fixed << setprecision(2) << calculateMean(marks[i], 4) << endl;
    }
    cout << endl;
}
