#ifndef CUR_H_
#define CUR_H_

#include<iostream>
using namespace std;

class Cur{
public:
		void saveCur();				//saves cursor
		void moveCur(const int x,const int y);	//moves cursor
		void resumeCur();			//resumes the cursor
};
#endif