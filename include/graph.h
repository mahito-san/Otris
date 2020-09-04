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

class Zgraph : public Gbase{
    public:
    void draw()
    {
        a[0][0] = 1;
		a[0][1] = 1;
		a[0][2] = 0;
		a[1][0] = 0;
		a[1][1] = 1;
		a[1][2] = 1;
		a[2][0] = 0;
		a[2][1] = 0;
		a[2][2] = 0;
    }
};
class Tgraph : public Gbase{
    public:
    void draw()
    {
        a[0][0] = 1;
        a[0][1] = 1;
        a[0][2] = 1;
		a[1][0] = 0;
		a[1][1] = 1;
		a[1][2] = 0;
		a[2][0] = 0;
		a[2][1] = 0;
		a[2][2] = 0;
    }
};

class Ograph : public Gbase{
    public:
    void draw()
    {
        a[0][0] = 1;
		a[0][1] = 1;
		a[0][2] = 0;
		a[1][0] = 1;
		a[1][1] = 1;
		a[1][2] = 0;
		a[2][0] = 0;
		a[2][1] = 0;
		a[2][2] = 0;
    }
    virtual int roll(){};
};

class Igraph : public Gbase{
    public:
    void draw()
    {
        a[0][0] = 0;
		a[0][1] = 1;
		a[0][2] = 0;
		a[1][0] = 0;
		a[1][1] = 1;
		a[1][2] = 0;
		a[2][0] = 0;
		a[2][1] = 1;
		a[2][2] = 0;
    }
};









