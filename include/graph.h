#include <iostream>
using namespace std;
#include <studio.h>
#include <stdlib.h>
#define DOWN 0
#define LEFT 1
#definr RIGHT 2

class Gbase{
    protected:
    int x;
    int y;
    int a[3][3];
    public:
    Gbase()
    {
        int i,j;
        x = 0;
        y = 0;
        for(j=0;j<3;j++)
        {
            for(i=0;i<3;i++)
            {
                a[i][j]=0;
            }
        }
    }
        int move(int dir);
        virtual int roll();
        virtual void draw(){}
        void setLocate(int a,int b){x = a;y = b;}
        void getLocate(int *a,int *b){*a = x,*b = y;}
        void printG(int color);
        void* getArray(){return (void*)a;}
    
};