#ifndef CUBEPOINT_HPP_
#define CUBEPOINT_HPP_
//
// goal :: printing small squares as color blocks
//
//
//
//
//
#include<iostream>
#include "cur.hpp"
using namespace std;
enum color{			//enumaration
	CLEAR = 0,
	BLACK = 30,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	DEEP_GREEN,
	WHITE
};

/*
    *We see the display panel as a lot of square dots
    * Each point obviously has a coordinate value
    * Each point has a color
 
 */
class CubePoint{
protected:
	int color;
	int x;
	int y; //Each grid point has color attributes and coordinate attributes
public:
	CubePoint()
	{
		color = CLEAR;
		x = 0;
		y = 0;
	}
	CubePoint(int a,int b,int c)
	{
		color = a;
		x = b;
		y = c;
	}
	void setLocate(const int x,const int y){this->x = x;this->y = y;}
	void setColor(const int color){this->color = color;}
	
	int getColor(){return color;}
	void getLocate(int&x,int &y){x = this->x;y = this->y;}
	//How to print dots
	void printPoint();
};
#endif

