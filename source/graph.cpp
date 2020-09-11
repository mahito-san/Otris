#include "../include/graph.hpp"
#include <unistd.h>

//graph is used to 
//make the commonplace for all he shape
//and context does the intrfacing part with the game logic  
void Gbase::printG(int color) //printing the block
{
    int i,j;
    CubePoint p;
    for(i = x; i < x+3; i++)
        for(j = y; j < y+3; j++)
        {
            if(a[i - x][j - y] == 1)
            {
                p.setLocate(i,j);
                p.setColor(color);
                p.printPoint();
            }
        }
}
int Gbase::move(int dir)//move the block
{
	switch(dir) //direction control
	{
		case DOWN:x++;break;
		case LEFT:y--;break;
		case RIGHT:y++;break;
		default:
				break;
	}
    return 0;
}

int Gbase::roll() //rolling the block
{
    int i,j;
    int b[3][3];
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            b[2-j][i] = a[i][j];
        }
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            a[i][j] = b[i][j];
        }
}


