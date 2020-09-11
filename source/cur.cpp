<<<<<<< HEAD
#include"../include/cur.hpp"
#include<cstdio>
#include<cstdlib>
//cursor related ,see cur.h for more documentation
void Cur::moveCur(const int x,const int y) //moving the cursor ,const for safety
{
	int i;
	for(i = 0; i < y; i++)
		printf("\33[2C"); 
	for(i = 0; i < x; i++)
		printf("\33[1B");
}
void Cur::saveCur()
{
	//save cur and move to destination
	printf("\33[s");	
}
void Cur::resumeCur()
{
	printf("\33[u");
}

=======
#include"../include/cur.h"
#include<cstdio>
#include<cstdlib>

void Cur::moveCur(const int x,const int y)
{
	int i;
	for(i = 0; i < y; i++)
		printf("\33[2C");
	for(i = 0; i < x; i++)
		printf("\33[1B");
}
void Cur::saveCur()
{
	//save cur and move to destination
	printf("\33[s");
}
void Cur::resumeCur()
{
	printf("\33[u");
}










>>>>>>> 0165dfbde52b37f892601f7392f4dd50b97aa30d
