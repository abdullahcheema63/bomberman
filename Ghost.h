/*
 * Ghost.h
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#ifndef GHOST_H_
#define GHOST_H_
#include <iostream>
#include <deque>
#include "Character.h"
#include "Point.h"
using namespace std;
enum Directions{
	NONE,UP,DOWN,LEFT,RIGHT,BRICK
};
class Ghost: public Character {
	Directions bfsArray[14][17];
	deque<Point> bfsQueue;
public:
	Ghost();
	int getCell(int x,int y);
	void setPosition(int x,int y);
	void initializeBfsArray();
	Directions bfs(Point target);
	void getCellCordinates(int& x,int &y);
	void printBFSArray();
	void turnLeft(int csize);
	void turnRight(int csize);
	void turnUp(int csize);
	void turnDown(int csize);
	void move(Directions d,int csize=60);
	virtual ~Ghost();
};

#endif /* GHOST_H_ */
