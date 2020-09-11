#include "../include/rand.hpp"
#include <ctime>
#include <stdlib.h>
#include <iostream>
using namespace std;

//rand constructor
Rand::Rand()
{
    srand(unsigned(time(0)));
}

int Rand::randNum(int x,int y)//random numb gen 
{
    int randNum;
    double random(double,double);
    randNum = int(random(x,y));
    return randNum;
}

double random(double start,double end)//limitations
{
    return start + (end - start)*rand()/(RAND_MAX + 1.0); //set limit for higher lower bound
}