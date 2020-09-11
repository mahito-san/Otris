//Game.cpp file

#include "../include/game.hpp"
#include "../include/rand.hpp"
#include <cstring>
#include<cstdio>
#include<pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define SPEED 500000
#define PENAL_SIZE (17*24*sizeof(int)) // the size of background
#define CUBE_SIZE (3*3*sizeof(int))

pthread_mutex_t	mutex_lock;///////
//safe threading
// mutex class is a synchronization primitive that can be used to protect 
//shared data from being simultaneously accessed by multiple threads.
//as there will be two threads,mutex lock will protect
//from accessing data that the otehr thread isn't allowed of getting access
int num = 0;

static int stop_flag;
//In order to call the srand function only once, 
//so that random numbers generated at similar times
// will not be repeated
static Rand r;

/////////////////////////////////////////////
//print of next cube 
void Game::printNextCube(Context* graph)
{
int x = 7;
int y = 19;
    int i,j;
   Cur c;
    CubePoint p;   

c.saveCur();
   c.moveCur(6,19);
   cout<<"next : ";
   c.resumeCur();

    int a[3][3] = {0};  //get block array
    memcpy(a,graph->getArray(),CUBE_SIZE);
    for(i = x; i < x+3; i++)
        for(j = y; j < y+3; j++)
        {       p.setLocate(i,j);
		p.setColor(CLEAR);
                p.printPoint();
            if(a[i - x][j - y] == 1)
            {

                p.setColor(graph->getColor());
                p.printPoint();
            }
        }
}
//User Interface with Cursor Class named as Cur
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

MARK Game::getMark()
{
	return mark;
}
void Game::setMark( MARK mark )
{
	this->mark = mark;
}

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

//////////////////////////////////////////////
//game constructor
//constructing the game object
Game::Game()
{
    m_graph = NULL;
    x = 1;
    y = 7;
    CubePoint p;//position defined
    int i;
    s.printMessege();

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
   /*Test whether the panel value is normal
   for(i = 0; i < 24; i++)
   {
        for(int j = 0; j < 17; j++)
            cout << m_penal[i][j] <<" ";
        cout << endl;
   }
   */
   fflush(stdout);
}
//get the shape
char Game::getShape()
{
    char ch;
    switch(r.randNum(1,6))//chose from 1to5
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
    int b[3][3] = {0}; //get the block array

    m_graph->printG(CLEAR);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);//cube szie and block defined
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
    int b[3][3] = {0}; //the block array

    memcpy(b,m_graph->getArray(),CUBE_SIZE);
    for(i = x; i < x + 3; i++)
        for(j = y; j < y + 3; j++)
        {
            m_penal[i][j] += b[i-x][j-y];
		m_color[i][j] = m_graph->getColor();////////the color of the block///////
        }
    return true;

}

bool Game::setPenal()
{
    int i,j;
    int b[3][3] = {0}; //getting the block array

    m_graph->getLocate(&x,&y);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);
    /*Test whether the block array is normal
    for(i = 0;i < 3; i++)
    {
        for(j = 0; j < 3; j++)
            cout<<b[i][j]<< " ";
        cout<<endl;
    }
    */

    //if it touches th upper ground game over
    for(i = x; i < x + 3; i++)
        for(j = y; j < y + 3; j++)
        {
            m_penal[i][j] += b[i-x][j-y];
            if(m_penal[i][j] > 1)
            {
                cout<<"game over"<<endl;
                //Add score statistics rankings, etc.
                system("stty icanon echo");//system call
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
    /*
   for(int i = 0; i < 24; i++)
   {
        for(int j = 0; j < 17; j++)
            cout << m_penal[i][j] <<" ";
        cout << endl;
   }
   */
}

void Game::move(int dir)//moving the block
{

	if(GAME_RUN != mark)
		return;
    erasePenal();
    pthread_mutex_lock(&mutex_lock);///////////////////////////////////////
    switch(dir)
    {
        case DOWN:
            if(false == isAttachBottom()) //if its not touching the floor
            {
                m_graph->move(DOWN); //it stays on course
                setPenal();
                m_graph->printG(YELLOW);
            }
            else
            {
                recoverPenal();
                m_graph->printG(YELLOW); //if it touches then recovar
                erase();
                stop();
            }
            break;
        case LEFT:
            if(false == isAttachLeft()) //not left
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
            if(false == isAttachRight()) //not right
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
pthread_mutex_unlock(&mutex_lock);//////////thread unlcoking//////////
}
void Game::roll()
{
    //Take the value of the square and put it in an array firs
    int i,j;
    int flag = 0;
    int b[3][3] = {0}; //get blovk array
    int temp[3][3] = {0};

    m_graph->getLocate(&x,&y);
    memcpy(b,m_graph->getArray(),CUBE_SIZE);
    erasePenal();
    //Rotate the array
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            temp[2-j][i] = b[i][j];
        }
    //Determine whether it will coincide with the panel after rotation
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
    //If they do not overlap, rotate the square and 
    //set the value of the panel
    if(flag == 0)
    {
        m_graph->roll();
    }
    setPenal();
    m_graph->printG(YELLOW);
}
void Game::stop() //stops
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
    int b[3][3] = {0};  //get the block array
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
    int b[3][3] = {0}; //get the block array
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
    int b[3][3] = {0}; //get the block array
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
void Game::erase()
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
            //adding the points
            count++;
            s.setScore(count);
            s.printMessege();

            //The graphics above the row are located as a whole
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
    //refresh panel
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


//main function and related listenKey function starts here
//listenkey is used as the function for taking inputs
void* listenKey(void *ptr)
{
    Game* ptrg = (Game*)ptr;
    //object pointrt
    char key;
    while(1)
    {
        system("stty -icanon -echo");//setting up no input cache,system call to clear the buffer
        key = getchar();
        system("stty icanon echo");//system call to clear the buffer
        switch(key)
        {
            case 'a':
                ptrg->move(LEFT);break; //keys are distributed as inside switch
            case 'd':
                ptrg->move(RIGHT);break;
            case 'w':
                ptrg->roll();break;
            case 's':
                //Downhill
                while(1)
                {
                    if(stop_flag == 1)
                    {
                        stop_flag = 0;
                        break;
                    }
                    ptrg->move(DOWN);
                }
                break;
            case 68: //ASCII
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
		if(GAME_RUN == ptrg->getMark())
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
    pthread_t t1; //threading 
    //created thread t1
pthread_mutex_init(&mutex_lock, NULL);//thread safety
	system("clear");
    Game g;
    //g.createCube();
	g.gameInit();
    pthread_create(&t1,NULL,listenKey,(void*)(&g));

    while(1)
    {
        fflush(stdout); //flushes the outpu of a buffer in std output
        usleep(SPEED);//calculates in milisec
        g.move(DOWN);//the blocks tend to get down
    }
	return 0;
}
