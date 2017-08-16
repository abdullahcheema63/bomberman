/*
 * Character.h
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
//#include "Point.h"
class Character {
protected:
	int x_cordinate;
	int y_cordinate;
public:
	Character();
	void setPosition(int x,int y);
	int getX();
	int getY();
	void turnLeft(int cell,int csize);
	void turnRight(int cell,int csize);
	void turnUp(int cell,int csize);
	void turnDown(int cell,int csize);
	virtual int getCell(int x,int y)=0;
	virtual ~Character();

};

#endif /* CHARACTER_H_ */
