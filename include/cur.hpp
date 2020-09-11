#ifndef CUR_HPP_
#define CUR_HPP_
//
//if we want to move the cursor in a program 
//
//we only need a cur object
//which we will use throughout the program files

#include<iostream>
using namespace std;

class Cur{
public:
		void saveCur();				//saves cursor
		void moveCur(const int x,const int y);	//moves cursor
		void resumeCur();			//resumes the cursor
};
#endif

