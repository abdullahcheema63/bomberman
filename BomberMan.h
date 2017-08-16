/*
 * BomberMan.h
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#ifndef BOMBERMAN_H_
#define BOMBERMAN_H_

#include "Character.h"

class BomberMan: public Character {
	int lives;
	char motion;
public:
	BomberMan();
	char getMotion();
	void setMotion(char m);
	void setPosition(int x,int y);
	int getCell(int x,int y);
	void getCellCordinates(int &x,int &y);
	int& getLives();
	void turnLeft(int cell,int csize);
	void turnRight(int cell,int csize);
	void turnUp(int cell,int csize);
	void turnDown(int cell,int csize);
	virtual ~BomberMan();
};

#endif /* BOMBERMAN_H_ */
