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

    c.saveCur();
    c.moveCur(6,19);
    
}