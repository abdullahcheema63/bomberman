/*
 * BomberMan.cpp
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#include "BomberMan.h"

BomberMan::BomberMan():Character() {
	// TODO Auto-generated constructor stub
	lives=3;
	setPosition(0,0);
	motion='r';
}
void BomberMan::setPosition(int x,int y)
{
	x_cordinate=x;
	y_cordinate=y;
	getCellCordinates(x,y);

}
int& BomberMan::getLives()
{
	return lives;
}
BomberMan::~BomberMan() {
	// TODO Auto-generated destructor stub
}

void BomberMan::getCellCordinates(int &x,int &y)
{
	y=(810-(getY()-30))/60-1;
	x=(getX()-20)/60;
}

void BomberMan::turnLeft(int cell,int csize)
{
	if (cell==0)
	{
		x_cordinate-=csize;
	}
	int x,y;
	getCellCordinates(x,y);

}
void BomberMan::turnRight(int cell,int csize)
{
	if (cell==0)
	{
		x_cordinate+=csize;
	}
	int x,y;
	getCellCordinates(x,y);

}
void BomberMan::turnUp(int cell,int csize){
	if (cell==0)
	{
		y_cordinate+=csize;
	}
	int x,y;
	getCellCordinates(x,y);

}
void BomberMan::turnDown(int cell,int csize){
	if (cell==0)
	{
		y_cordinate-=csize;
	}
	int x,y;
	getCellCordinates(x,y);

}
char BomberMan::getMotion(){ return motion; }
void BomberMan::setMotion(char m){ motion=m; }
