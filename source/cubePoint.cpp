#include"../include/cubePoint.hpp"
#include<cstdio>
#include <iostream>;
using namespace std;
void CubePoint::printPoint()
{

	//terminal colors
	Cur cur;
	cur.saveCur();
	cur.moveCur(x,y);
	//now coloring the cube points
	switch(color)
	{
		//using  cout to color the block
		 case BLACK     :cout<<"\033[40;30m  \033[0m";break;
		 case RED       :cout<<"\033[41;31m  \033[0m";break;
		 case GREEN     :cout<<"\033[42;32m  \033[0m";break;
		 case YELLOW    :cout<<"\033[43;33m  \033[0m";break;
		 case BLUE      :cout<<"\033[44;34m  \033[0m";break;
		 case PURPLE    :cout<<"\033[45;35m  \033[0m";break;
		 case DEEP_GREEN:cout<<"\033[46;36m  \033[0m";break;
		 case WHITE     :cout<<"\033[47;37m  \033[0m";break;
		 case CLEAR     :cout<<"\033[8m  ";
		 defaut:
		 break;
	}
	cur.resumeCur();
}
//the objective here is to color the blocks 