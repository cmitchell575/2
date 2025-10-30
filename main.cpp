/***************************************
Strongest Link
Author: Chase Mitchell
Date Completed: 10/29/25
Description: Create a prototype of a trivia game using a linked list to parse specific information from a .txt file
***************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include "LinkedList.hpp"
using namespace std;

class Question {
    string prompt_;
    array<string,4> options_;
    int correct_;
public:
    Question(const string& prompt,
             const string& a1,
             const string& a2,
             const string& a3,
             const string& a4,
             int correctIndex)
        : prompt_(prompt), options_{a1,a2,a3,a4}, correct_(correctIndex) {}
    const string& getPrompt() const { return prompt_; }
    const string& getAnswerOption(int i) const { return options_.at(i); }
    int getCorrectAnswerIndex() const { return correct_; }
};

bool populateQuestionListFromFile(LinkedList<Question>& list) {
    ifstream in("SampleQuestions.txt");
    if (!in.is_open()) return false;
    string line;
    while (getline(in,line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string prompt, correctStr, a1, a2, a3, a4;
        if (!getline(ss,prompt,';')) continue;
        if (!getline(ss,correctStr,';')) continue;
        if (!getline(ss,a1,';')) continue;
        if (!getline(ss,a2,';')) continue;
        if (!getline(ss,a3,';')) continue;
        if (!getline(ss,a4,'\n')) continue;
        int correctNum = 0;
        stringstream convert(correctStr);
        convert >> correctNum;
        list.pushBack(Question(prompt,a1,a2,a3,a4,correctNum - 1));
    }
    return true;
}

int main() {
    LinkedList<Question> questions;
    if (!populateQuestionListFromFile(questions)) return 0;
    cout << "Welcome to The Strongest Link!\n\n";
    int currentStreak = 0, bestStreak = 0, qnum = 1;
    while (!questions.empty()) {
        Question q = questions.popFront();
        cout << "Question " << qnum++ << ":\n";
        cout << q.getPrompt() << "\n\n";
        for (int i = 0; i < 4; ++i) cout << i+1 << ". " << q.getAnswerOption(i) << "\n";
        cout << "\nEnter answer number: ";
        int ans;
        if (!(cin >> ans)) return 0;
        if (ans-1 == q.getCorrectAnswerIndex()) {
            cout << "Correct!\n\n";
            ++currentStreak;
            if (currentStreak > bestStreak) bestStreak = currentStreak;
        } else {
            cout << "Incorrect!\n\n";
            currentStreak = 0;
        }
    }
    cout << "Your strongest link was " << bestStreak << " correctly answered question(s) in a row. Thanks for playing!\n";
    return 0;
}