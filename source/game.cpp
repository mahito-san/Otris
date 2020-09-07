#include ".../include/game.h"
#include "../include/rand.h"
#include <cstring>
#include <cstdio>
#include <pthread>
#include <unistd.h>
#include <semaphore.h>


#define SPEED 500000
#define PENAL_SIZE(17*24*sizeof(int))
#define  CUBE_SIZE(3*3*sizeof(int))

pthread_mutex_t mutex_lock;//threading sync

int num = 0;

static int stop_flag;


//in order to call the srand function only once
//so that random numbers generated at similar times 
//will not be repeated.

static Rand r;

void Game::printNextCube(Context* graph)
{
    int x = 7;
    int y = 19;

    int i,j;
    Cur c;
    CubePoint p;

    c.saveCur();        //need
    c.moveCur(6,19);    //
    c.resumeCur();      //
                        //clarification

    int a[3][3]={0};

    memcpy(a,graph->getArray(),CUBE_SIZE);//need clarification
    
    //need clarification
    for(i=x;i<x+3;i++)
    {
        for(j=y;j<y+3;j++)
        {
            p.setLocate(i,j);
            p.setColor(CLEAR);
            p.printPoint();

            if(a[i-x][j-y] == 1) //need clarification
            {
                p.setColor(graph->getColor());
                p.printPoint();
            }

        }
    }
}


void Game::printHelep()
{
    //left out
    //needs proper clarification
}


//game init needs proper clarification
void Game::gameInit()
{
    printHelep();

    nextGraph = new Context(getShape());

    nextGraph = new Context(getShape());
    nextGraph->draw();
    nextGraph->setLocate(1,7);

    createCube();
}

//description
//what is mark?
MARK Game::getMark() 
{
    return mark;
}

//needs more clarification
void Game::getMark()
{
    this->mark = mark;
}

//setmark

void Game::setMark(Mark mark)
{
    this->mark = mark;
}


//destructor
Game::~Game()
{
    //needs code
}

Game::Game()
{
    //needs proper clarificaton
    //needs proper diagram and function definitions
}
char Game::getShape()
{
    //needs code
    return ch;
}

bool Game::erasePenal()
{
    int i,j;
    int b[3][3]={0};//get the block array

    m_graph->printG(clear)//needs clarification
    mmcpy(//code);

    //two for loops

    return true;

}

bool Game::recoverPanel()
{
    int i,j;
    int b[3][3]={0};

    memcpy(//code);

    //code two for loops

    return true;
}

bool Game::setPenal()
{
    int i,j;
    int b[3][3]={0};
    
    m_graph->getLocate(&x,&y)//what is it doing with x and y co ordinates

    //codes that left uncleared

    return true;
}