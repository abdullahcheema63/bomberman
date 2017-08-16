/*
 * Bomb.cpp
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#include "Bomb.h"

Bomb::Bomb(int x,int y,int r,int bt) {
	// TODO Auto-generated constructor stub
	x_cordinate=x;
	y_cordinate=y;
	radius=r;
	bomb_time=bt;
}
int Bomb::getX(){ return x_cordinate; }
int Bomb::getY(){ return y_cordinate; }

Bomb::~Bomb() {
	// TODO Auto-generated destructor stub
	explode(x_cordinate,y_cordinate);
}

