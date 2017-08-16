/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include "util.h"
#include "BomberMan.h"
#include "Ghost.h"
#include "Bomb.h"
//#define WITH_TEXTURES
enum GameStates{
	READY,GAMEOVER,PAUSE,START,WINNER
};
enum GhostStatus{
	DESTROYED,WORKING,UNUSED
};
using namespace std;
class Board {
private:
	int xcellsize, ycellsize;
	int width, height;
	ColorNames pcolor, bcolor, gcolor;
	int initializedBricks;
public:
	static int score;
	static int time;
	GameStates gamestate;
	BomberMan bomberman;
	static Ghost pinky;
	static Ghost blinky;
	Bomb* bomb;
	bool bombStatus;
	static bool pinkyStatus;
	static bool blinkyStatus;
	static GhostStatus inkyStatus;
	static Ghost inky;
	static Ghost clyde;
	static GhostStatus clydeStatus;
	bool chase;
	bool frightened;
	bool scatter;
	int stateCount;
	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize = 8, int ysize = 8);
	~Board(void);
	void InitalizeBoard(int, int);
	//draw the board
	void Draw();
	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	void GetInitBombermanPosition(int &x, int &y) {
		x = xcellsize+xcellsize/3;
		y = ycellsize+ycellsize /2;
	}

	void GetInitTextPosition(int &x, int &y);
	void GetInitPinkyPosition(int &x, int &y);
	void getInitBlinkyPosition(int &x,int &y);
	void getInitInkyPosition(int &x,int &y);
	void getInitClydePosition(int &x,int &y);
	double remainingBrickPercentage();
	void printBoardArray();
	void reset(int i);
	static int levels;
//	int GetMidx
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif
