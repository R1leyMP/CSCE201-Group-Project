#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ifstream questions, answers;
    string quesElement, ansElement; //variables to store each q&a respectively
    vector<string> questionVec; //vector for questions
    vector<string> answerVec; //vector for answers

//handles question file
    questions.open("questions.txt");

    if (!questions.is_open()){
        cout << "error" << endl;
    }

    while (!questions.eof()){    //iterates through file and stores each question in q-vector
        getline(questions, quesElement);
        questionVec.push_back(quesElement);
    }


//handles answer file
    answers.open("answers.txt");

    if (!answers.is_open()){
        cout << "error" << endl;
    }

    while (!answers.eof()){    //iterates through file and stores each answer in ans-vector
        getline(answers, ansElement);
        answerVec.push_back(ansElement);
    }

    questions.close();
    answers.close();

    return 0;
}
