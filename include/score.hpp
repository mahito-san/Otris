#ifndef SCORE_HPP
#define SCORE_HPP
#include <iostream>
#include <string>
using namespace std;

class Score{
    string player;
    int score;
	

public:
    Score(){player = "";score = 0;};
    void setName(string name){player = name;};
    void setScore(int s){score = s;};

    void printMessege();
};

#endif
