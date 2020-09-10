#include ".../include/game.hpp"
#include "../include/rand.hpp"
#include <cstring>
#include <cstdio>
#include <thread>
#include <unistd.h>
#include <semaphore.h>//semaphore operations


#define SPEED 500000
#define PENAL_SIZE(17*24*sizeof(int))
#define  CUBE_SIZE(3*3*sizeof(int))

pthread_mutex_t mutex_lock;//threading sync,safe threading

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

    c.saveCur();        //
    c.moveCur(6,19);    //
    c.resumeCur();      //
                        //

    int a[3][3]={0};

    memcpy(a,graph->getArray(),CUBE_SIZE);
    
    
    for(i=x;i<x+3;i++)
    {
        for(j=y;j<y+3;j++)
        {
            p.setLocate(i,j);
            p.setColor(CLEAR);
            p.printPoint();

            if(a[i-x][j-y] == 1) 
            {
                p.setColor(graph->getColor());
                p.printPoint();
            }

        }
    }
}


void Game::printHelep()
{
    Cur c;
	c.saveCur();
   	c.moveCur(10,19);
   	cout<<"a: go to left" << endl;
    c.resumeCur();
    c.saveCur();
   	c.moveCur(11,19);
   	cout<<"d: go to right" << endl;
    c.resumeCur();
    c.saveCur();
   	c.moveCur(12,19);
   	cout<<"w: roll cube" << endl;
    c.resumeCur();
    c.saveCur();
   	c.moveCur(13,19);
   	cout<<"s: go to down" << endl;
    c.resumeCur();
    c.saveCur();
   	c.moveCur(14,19);
   	cout<<"p: run or pause" << endl;
    c.resumeCur();
}



void Game::gameInit()
{
    printHelep();

    nextGraph = new Context(getShape());
    nextGraph->draw();
    nextGraph->setLocate(1,7);

    createCube();
}

//
MARK Game::getMark() 
{
    return mark;
}


//
void Game::setMark(Mark mark)
{
    this->mark = mark;
}


//destructor
Game::~Game()
{
    if( NULL != m_graph )
	{
		delete m_graph;
		m_graph = NULL;
	}

	if( NULL != nextGraph )
	{
		delete nextGraph;
		nextGraph = NULL;
	}
}

Game::Game()
{
    m_graph = NULL;
    x = 1;
    y = 7;
    CubePoint p;
    int i;
    s.printMessage();

	mark = GAME_RUN;////////////////////////////////////////////////

    memset((void*)m_penal,0,PENAL_SIZE); 
	memset((void*)m_color,0,PENAL_SIZE);///////////////////
   for(i = 0; i < 24; i++)
   {
        p.setLocate(i,0);
        p.setColor(BLUE);
        p.printPoint();
        p.setLocate(i,16);
        p.setColor(BLUE);
        p.printPoint();
        m_penal[i][0] = 1;
        m_penal[i][16] = 1;
   }
   for(i = 0; i < 17; i++)
   {
        p.setLocate(23,i);
        p.setColor(BLUE);
        p.printPoint();
        p.setLocate(0,i);
        p.setColor(RED);
        p.printPoint();
        m_penal[23][i] = 1;
        m_penal[0][i] = 1;
   }
  
   fflush(stdout);
}

char Game::getShape()
{
    char ch;
    switch(r.randNum(1,6))
    {
        case 1:ch = 'Z';break;
        case 2:ch = 'T';break;
        case 3:ch = 'O';break;
        case 4:ch = 'I';break;
        case 5:ch = 'L';break;
        default:
               cout<<"no this shape type"<<endl;
               ch = '\0';
               break;
    }
    return ch;
}

bool Game::erasePenal()
{
    int i,j;
    int b[3][3] = {0}; 

    m_graph->printG(CLEAR);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            m_penal[i + x][j + y] -= b[i][j];
		m_color[i][j] = CLEAR;//////////////////////////
        }
    return true;
}

bool Game::recoverPenal()
{
    int i,j;
    int b[3][3] = {0};

    memcpy(b,m_graph->getArray(),CUBE_SIZE);
    for(i = x; i < x + 3; i++)
        for(j = y; j < y + 3; j++)
        {
            m_penal[i][j] += b[i-x][j-y];
		m_color[i][j] = m_graph->getColor();///////////////////////////
        }
    return true;

}

bool Game::setPenal()
{
    int i,j;
    int b[3][3] = {0};

    m_graph->getLocate(&x,&y);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);
   
    for(i = x; i < x + 3; i++)
        for(j = y; j < y + 3; j++)
        {
            m_penal[i][j] += b[i-x][j-y];
            if(m_penal[i][j] > 1)
            {
                cout<<"game over"<<endl;
                
                system("stty icanon echo");
                exit(0);
            }
        }
    return true;
}

void Game::createCube()
{
    	m_graph = nextGraph;
	setPenal();
	m_graph->printG(YELLOW);

	nextGraph = new Context(getShape());
	nextGraph->draw();
	nextGraph->setLocate(1,7);
	printNextCube(nextGraph);
 
}


void Game::move(int dir)
{

	if(GAME_RUN != mark)
		return;
    erasePenal();
pthread_mutex_lock(&mutex_lock);///////////////////////////////////////
    switch(dir)
    {
        case DOWN:
            if(false == isAttachBottom())
            {
                m_graph->move(DOWN);
                setPenal();
                m_graph->printG(YELLOW);
            }
            else
            {
                recoverPenal();
                m_graph->printG(YELLOW);
                erase();
                stop();
            }
            break;
        case LEFT:
            if(false == isAttachLeft())
            {
                m_graph->move(LEFT);
                setPenal();
                m_graph->printG(YELLOW);
            }
            else
            {
                recoverPenal();
                m_graph->printG(YELLOW);
            }
 
            break;
        case RIGHT:
            if(false == isAttachRight())
            {
                m_graph->move(RIGHT);
                setPenal();
                m_graph->printG(YELLOW);
            }
            else
            {
                recoverPenal();
                m_graph->printG(YELLOW);
            }
            break;
        default:
            break;
    }
pthread_mutex_unlock(&mutex_lock);/////////////////////////////////////
}
void Game::roll()
{
    
    int i,j;
    int flag = 0;
    int b[3][3] = {0}; 
    int temp[3][3] = {0};

    m_graph->getLocate(&x,&y);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);
    erasePenal();
    //旋转数组
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            temp[2-j][i] = b[i][j];
        }
    
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if (temp[i][j] == 1 && m_penal[x + i][y + j] == 1)   
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }
    
    if(flag == 0)
    {
        m_graph->roll();
    }
    setPenal();
    m_graph->printG(YELLOW);
}
void Game::stop()
{
    delete m_graph;
	m_graph = NULL;
    stop_flag = 1;
    createCube();
}

bool Game::isAttachBottom()
{
    int i,j;
    int cube_x,cube_y;
    int b[3][3] = {0};  
    int flag = false;

    m_graph->getLocate(&cube_x,&cube_y);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
           if (b[i][j] == 1 && m_penal[i + cube_x + 1][j + cube_y] == 1)
           {
                flag = true;
                break;
           }
        }
        if (flag == true)
            break;
    }
    return flag;
}
bool Game::isAttachLeft()
{
    int i,j;
    int cube_x,cube_y;
    int b[3][3] = {0}; 
    int flag = false;

    m_graph->getLocate(&cube_x,&cube_y);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
           if (b[i][j] == 1 && m_penal[i + cube_x][j + cube_y - 1] == 1)
           {
                flag = true;
                break;
           }
        }
        if (flag == true)
            break;
    }
    return flag;

}
bool Game::isAttachRight()
{
    int i,j;
    int cube_x,cube_y;
    int b[3][3] = {0}; 
    int flag = false;

    m_graph->getLocate(&cube_x,&cube_y);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
           if (b[i][j] == 1 && m_penal[i + cube_x][j + cube_y + 1] == 1)
           {
                flag = true;
                break;
           }
        }
        if (flag == true)
            break;
    }
    return flag;
}
void Game::erase()//gets earse if one line is completed
{
   int i,j;
   int flag = 0;
   static int count = 0;
   for(i = 22; i > 0; i--)
   {
        for(j = 1; j < 16; j++)
        {
            if(m_penal[i][j] == 0)
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            
            count++;
            s.setScore(count);
            s.printMessage();


            down(i);
            i++;
        }
        flag = 0;
   }
}
void Game::down(int level)
{
    int i,j;
    int flag = 1;

    for(i = level; i > 1; i--)
        for(j = 1; j < 16; j++)
        {
            m_penal[i][j] = m_penal[i - 1][j];
        }

    CubePoint p;
    for(i = 1; i < 23; i++)
        for(j = 1; j < 16; j++)
        {
            if(m_penal[i][j] == 1)
            {
                p.setLocate(i,j);
                //p.setColor(YELLOW);
		p.setColor(m_color[i][j]);
                p.printPoint();
            }
            if(m_penal[i][j] == 0)
            {
                p.setLocate(i,j);
                p.setColor(CLEAR);
                p.printPoint();
            }
        }
}

//listens the key,main control happens here
//thread init ed for taking input and animation simultaneously
void* listenKey(void *ptr)
{
    Game* ptrg = (Game*)ptr;
    char key;
    while(1)
    {
        system("stty -icanon -echo");
        key = getchar();
        system("stty icanon echo");
        switch(key)
        {
            //goes for every a,d,w,s
            case 'a':
                ptrg->move(LEFT);break;
            case 'd':
                ptrg->move(RIGHT);break;
            case 'w':
                ptrg->roll();break;//one roll at a time
            case 's':
                
                while(1)
                {
                    if(stop_flag == 1)//the floor 
                    {
                        stop_flag = 0;
                        break;
                    }
                    ptrg->move(DOWN);
                }
                break;
            case 68:
                ptrg->move(LEFT);
                break;
            case 67:
                ptrg->move(RIGHT);
                break;
            case 65:
                ptrg->roll();
                break;
            case 66:
                while (1) {
                    if (stop_flag == 1) {
                        stop_flag = 0;
                        break;
                    }
                    ptrg->move(DOWN);
                }
                break;

            case 'p':
		if(GAME_RUN == ptrg->getMark())//pause and run system
			ptrg->setMark(GAME_PAUSE);
		else ptrg->setMark(GAME_RUN);
                break;

            default:
                break;
        }
    }
}
int main()
{
    pthread_t t1;
    pthread_mutex_init(&mutex_lock, NULL);//thread initialization
	system("clear");
    Game g;
    //g.createCube();
	g.gameInit();
    pthread_create(&t1,NULL,listenKey,(void*)(&g));//thread creation

    while(1)
    {
        fflush(stdout);
        usleep(SPEED);//framerate
        g.move(DOWN);//automatically cubes going down
    }
	return 0;
}