#ifndef CUR_H
#define CUR_H_

#include<iostream>
using namespace std;

class Cur
{
public:
    void saveCur(); //save cursor position
    void moveCur(const int x,const int y);
    // move the cursor position to (x,y) position
    void resumeCur();   //restore cursor position

};

#endif // CUR_H_
