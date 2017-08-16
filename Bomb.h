/*
 * Bomb.h
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#ifndef BOMB_H_
#define BOMB_H_

class Bomb {
	int radius;
	int x_cordinate;
	int y_cordinate;
public:
	int bomb_time;
	Bomb(int x,int y,int r=1,int bt=2);
	void explode(int x_c,int y_c);
	int getX();
	int getY();
	int& getCell(int x,int y);
	void getCellCordinates(int &x,int &y);
	virtual ~Bomb();
};

#endif /* BOMB_H_ */
