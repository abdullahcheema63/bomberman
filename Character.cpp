/*
 * Character.cpp
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#include "Character.h"

Character::Character() {
	// TODO Auto-generated constructor stub

}

void Character::setPosition(int x,int y)
{
	x_cordinate=x;
	y_cordinate=y;

}
int Character::getX(){ return x_cordinate; }
int Character::getY(){ return y_cordinate; }

void Character::turnLeft(int cell,int csize)
{
	if (cell==0)
	{
		x_cordinate-=csize;
	}
}
void Character::turnRight(int cell,int csize)
{
	if (cell==0)
	{
		x_cordinate+=csize;
	}
}
void Character::turnUp(int cell,int csize){
	if (cell==0)
	{
		y_cordinate+=csize;
	}
}
void Character::turnDown(int cell,int csize){
	if (cell==0)
	{
		y_cordinate-=csize;
	}
}


Character::~Character() {
	// TODO Auto-generated destructor stub
}
