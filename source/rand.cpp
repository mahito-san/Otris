#include "../include/rand.hpp"
#include <ctime>
#include <stdlib.h>
#include <iostream>

using namespace std;

Rand::Rand()
{
    srand(unsigned(time(0)));//seed
}

Rand::randNum(int x,int y)
{
    int randNum;
    double random(double,double); //function definition
    randNum = int(random(x,y));
    return randNum;
}

double random(double start,double end)
{
    return start+(end-start)*rand()/(RAND_MAX+1.0);//max random defined
}