
#include"../include/cur.hpp"
#include<cstdio>
#include<cstdlib>
//cursor related ,see cur.h for more documentation
void Cur::moveCur(const int x,const int y) //moving the cursor ,const for safety 
{
	int i;
	for(i = 0; i < y; i++)
		printf("\33[2C"); //works for x axis line 10
	for(i = 0; i < x; i++)
		printf("\33[1B"); //works for y axis line 11
void Cur::saveCur()
{
	//save cur and move to destination
	printf("\33[s");	
}
void Cur::resumeCur()
{
	printf("\33[u");
}












