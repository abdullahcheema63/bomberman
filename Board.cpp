/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"
#include "Ghost.h"
#include <cstdio>
#include "Bomb.h"
const int Board::BOARD_X = 17;
const int Board::BOARD_Y = 14;
bool Board::pinkyStatus=true;
bool Board::blinkyStatus=true;
Ghost Board::pinky=Ghost();
Ghost Board::blinky=Ghost();
Ghost Board::inky=Ghost();
GhostStatus Board::inkyStatus=UNUSED;
Ghost Board::clyde=Ghost();
GhostStatus Board::clydeStatus=UNUSED;
int Board::score=0;
int Board::time=180;
int Board::levels=1;
//here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
enum BoardParts {
	NILL, S_BRICK, G_BRICK, R_BRICK
};
// defining some utility functions...

static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };

#ifdef WITH_TEXTURES
const int nbricks = 3;

GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = {"solid.png", "brick.png", "brick-green.png"};
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...

void RegisterTextures()
/*Function is used to load the textures from the
 * files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	//ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each bricks data...

	for (int i = 0; i < nbricks; ++i) {

		// Read current brick

		ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			//ofile.write((char*) &length, sizeof(int));
		}
		//ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
				GL_UNSIGNED_BYTE, &data[0]);
	}
	//ofile.close();

}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
		float fheight)
/*Draws a specfic brick at given position coordinate
 * sx = position of x-axis from left-bottom
 * sy = position of y-axis from left-bottom
 * cwidth= width of displayed brick in pixels
 * cheight= height of displayed bricki pixels.
 * */
{

	glPushMatrix();
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
//	glTranslatef(0, 0, 0);
//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin (GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
#endif
// Destructor
Board::~Board(void) {
}
void Board::InitalizeBoard(int w, int h) {
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
			{
				board_array[i][j] =
						(GetRandInRange(0, 10)) < 8 ? NILL :
						(GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
			}
		}
	}
	initializedBricks=0;
	for (int i=0;i<14;i++)
	{
		for (int j=0;j<17;j++)
		{
			if (board_array[i][j]==G_BRICK||board_array[i][j]==R_BRICK)
			{
				initializedBricks++;
			}
		}
	}

}
//Constructor
Board::Board(int xsize, int ysize) {
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	int bpos_x,bpos_y;
	this->GetInitBombermanPosition(bpos_x,bpos_y);
	bomberman.setPosition(bpos_x,bpos_y);
	this->GetInitPinkyPosition(bpos_x,bpos_y);
	pinky.setPosition(bpos_x,bpos_y);
	this->getInitBlinkyPosition(bpos_x,bpos_y);
	blinky.setPosition(bpos_x,bpos_y);
	gamestate=START;
	bombStatus=false;
	pinkyStatus=true;
	blinkyStatus=true;
	chase=true;
	scatter=false;
	frightened=false;
	stateCount=20;
	inkyStatus=UNUSED;
	clydeStatus=UNUSED;
	this->getInitClydePosition(bpos_x,bpos_y);
	clyde.setPosition(bpos_x,bpos_y);
	this->getInitInkyPosition(bpos_x,bpos_y);
	inky.setPosition(bpos_x,bpos_y);
	score=0;
//set up board
}

void Board::Draw() {
	glColor3f(0, 0, 1);
	glPushMatrix();

#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
				case NILL:
				// Empty space
				break;
				case S_BRICK:
				case G_BRICK:
				case R_BRICK:
				float fwidth = (float) (xcellsize) / width * 2, fheight =
				(float) ycellsize / height * 2;
				float fx = (float) (x - 10) / width * 2 - 1, fy = (float) y
				/ height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				 fheight);*/
				Drawbrick((BoardParts) board_array[i][j], (float)x/width-1, (float)y/height-1, fwidth,
						fheight);
				break;
			}
		}
	}
#else
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout <<      " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case NILL:
				// Empty space
				break;
			case S_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
						colors[SLATE_GRAY]);
				//DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[BLACK]);
				break;
			case G_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
						colors[LIGHT_GREEN]);
				break;
			case R_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[RED]);
				break;
			}
			//cout<<board_array[i][j]<<" ";
		}
		//cout<<endl;
	}
#endif
	glPopMatrix();
}

void Board::GetInitPinkyPosition(int &x, int &y) {
	//x = xcellsize * 3;
	//y = (BOARD_Y - 3) * ycellsize;
	GetInitBombermanPosition(x,y);
	x+=(xcellsize*2)-20;
	y+=(xcellsize*3)-30;
}
void Board::getInitBlinkyPosition(int &x,int &y)
{
	GetInitBombermanPosition(x,y);
	x+=(xcellsize*6)-20;
	y+=(xcellsize*5)-30;
}
void Board::GetInitTextPosition(int &x, int &y) {
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}

int Ghost::getCell(int x,int y)
{
	return board_array[(810-(y))/60-1][x/60];
}
int BomberMan::getCell(int x,int y)
{
	return board_array[(810-(y-30))/60-1][(x-20)/60];
}
int& Bomb::getCell(int x,int y)
{
	return board_array[(810-(y-30))/60-1][(x-20)/60];
}

void Ghost::initializeBfsArray()
{
	for (int i=0;i<14;i++)
	{
		for (int j=0;j<17;j++)
		{
			if (board_array[i][j]==NILL)
				bfsArray[i][j]=NONE;
			else
				bfsArray[i][j]=BRICK;
		}
	}
}

void Bomb::getCellCordinates(int &x,int &y)
{
	y=(810-(getY()-30))/60-1;
	x=(getX()-20)/60;
}

void Bomb::explode(int x_c,int y_c)
{
	if (getCell(x_c,y_c+60*radius)==2)
	{
		getCell(x_c,y_c+60*radius)=0;
		Board::score+=50;
	}
	if (getCell(x_c,y_c+60*radius)==3)
	{
		explode(x_c,y_c+60*radius);
		getCell(x_c,y_c+60*radius)=0;
		Board::score+=100;
	}
	if (getCell(x_c,y_c-60*radius)==2)
	{
		getCell(x_c,y_c-60*radius)=0;
		Board::score+=50;
	}
	if (getCell(x_c,y_c-60*radius)==3)
	{
		explode(x_c,y_c-60*radius);
		getCell(x_c,y_c-60*radius)=0;
		Board::score+=100;
	}
	if (getCell(x_c+60*radius,y_c)==2)
	{
		getCell(x_c+60*radius,y_c)=0;
		Board::score+=50;
	}
	if (getCell(x_c+60*radius,y_c)==3)
	{
		explode(x_c+60*radius,y_c);
		getCell(x_c+60*radius,y_c)=0;
		Board::score+=100;
	}
	if (getCell(x_c-60*radius,y_c)==2)
	{
		getCell(x_c-60*radius,y_c)=0;
		Board::score+=50;
	}
	if (getCell(x_c-60*radius,y_c)==3)
	{
		explode(x_c-60*radius,y_c);
		getCell(x_c-60*radius,y_c)=0;
		Board::score+=100;
	}
	int x_g,y_g,x_bomb,y_bomb;
	/*b->bomberman.getCellCordinates(x_g,y_g);
	getCellCordinates(x_bomb,y_bomb);
	if (x_g==x_bomb&&y_g==y_bomb)
	{
		b->bomberman.getLives()--;
		int x_b,y_b;
		b->GetInitBombermanPosition(x_b,y_b);
		b->bomberman.setPosition(x_b,y_b);
	}*/
	if (Board::pinkyStatus==true)
	{
		Board::pinky.getCellCordinates(x_g,y_g);
		getCellCordinates(x_bomb,y_bomb);
		if (x_g==x_bomb+1&&y_g==y_bomb)
		{
			Board::pinkyStatus=false;
			Board::score+=200;
			//delete Board::ghost;
		}
		if (x_g==x_bomb-1&&y_g==y_bomb)
		{
			Board::pinkyStatus=false;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb+1)
		{
			Board::pinkyStatus=false;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb-1)
		{
			Board::pinkyStatus=false;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb)
		{
			Board::pinkyStatus=false;
			Board::score+=200;
		}

	}
	if (Board::blinkyStatus==true)
	{
		Board::blinky.getCellCordinates(x_g,y_g);
		getCellCordinates(x_bomb,y_bomb);
		if (x_g==x_bomb+1&&y_g==y_bomb)
		{
			Board::blinkyStatus=false;
			//delete Board::ghost;
			Board::score+=200;
		}
		if (x_g==x_bomb-1&&y_g==y_bomb)
		{
			Board::blinkyStatus=false;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb+1)
		{
			Board::blinkyStatus=false;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb-1)
		{
			Board::blinkyStatus=false;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb)
		{
			Board::blinkyStatus=false;
			Board::score+=200;
		}

	}
	if (Board::inkyStatus==WORKING)
	{
		Board::inky.getCellCordinates(x_g,y_g);
		getCellCordinates(x_bomb,y_bomb);
		if (x_g==x_bomb+1&&y_g==y_bomb)
		{
			Board::inkyStatus=DESTROYED;
			//delete Board::ghost;
			Board::score+=200;
		}
		if (x_g==x_bomb-1&&y_g==y_bomb)
		{
			Board::inkyStatus=DESTROYED;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb+1)
		{
			Board::inkyStatus=DESTROYED;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb-1)
		{
			Board::inkyStatus=DESTROYED;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb)
		{
			Board::inkyStatus=DESTROYED;
			Board::score+=200;
		}

	}
	if (Board::clydeStatus==WORKING)
	{
		Board::clyde.getCellCordinates(x_g,y_g);
		getCellCordinates(x_bomb,y_bomb);
		if (x_g==x_bomb+1&&y_g==y_bomb)
		{
			Board::clydeStatus=DESTROYED;
			//delete Board::ghost;
			Board::score+=200;
		}
		if (x_g==x_bomb-1&&y_g==y_bomb)
		{
			Board::clydeStatus=DESTROYED;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb+1)
		{
			Board::clydeStatus=DESTROYED;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb-1)
		{
			Board::clydeStatus=DESTROYED;
			Board::score+=200;
		}
		if (x_g==x_bomb&&y_g==y_bomb)
		{
			Board::clydeStatus=DESTROYED;
			Board::score+=200;
		}

	}

}

void Board::printBoardArray()
{
	for (int i=0;i<14;i++)
	{
		for (int j=0;j<17;j++)
			cout<<board_array[i][j]<<" ";
		cout<<endl;
	}
}
void Board::reset(int i)
{
	//0 for hard reset
	//1 for enemy hit
	//2 for level up
	if (i==0)
	{
		InitalizeBoard(1020,840);
		gamestate=START;
		pinkyStatus=true;
		blinkyStatus=true;
		inkyStatus=UNUSED;
		clydeStatus=UNUSED;
		score=0;
		time=180;
		levels=1;
	}
	if (i==1)
	{
		gamestate=READY;
	}
	if (i==2)
	{
		InitalizeBoard(1020,840);
		gamestate=READY;
		pinkyStatus=true;
		blinkyStatus=true;
		inkyStatus=UNUSED;
		clydeStatus=UNUSED;
		//score=0;
		time=180;
		levels++;
	}
	int bpos_x,bpos_y;
	this->GetInitBombermanPosition(bpos_x,bpos_y);
	bomberman.setPosition(bpos_x,bpos_y);
	this->GetInitPinkyPosition(bpos_x,bpos_y);
	pinky.setPosition(bpos_x,bpos_y);
	this->getInitBlinkyPosition(bpos_x,bpos_y);
	blinky.setPosition(bpos_x,bpos_y);

	bombStatus=false;
	//pinkyStatus=true;
	//blinkyStatus=true;
	chase=true;
	scatter=false;
	frightened=false;
	stateCount=20;
	//inkyStatus=UNUSED;
	//clydeStatus=UNUSED;
	this->getInitClydePosition(bpos_x,bpos_y);
	clyde.setPosition(bpos_x,bpos_y);
	this->getInitInkyPosition(bpos_x,bpos_y);
	inky.setPosition(bpos_x,bpos_y);
}
void Ghost::move(Directions d,int csize)
{
	int x,y;
	getCellCordinates(x,y);
	if (d==UP)
	{
		if (board_array[y-1][x]==0)
			turnUp(csize);
	}
	else if (d==DOWN)
	{
		if (board_array[y+1][x]==0)
			turnDown(csize);
	}
	else if (d==LEFT)
	{
		if (board_array[y][x-1]==0)
			turnLeft(csize);
	}
	else if (d==RIGHT)
	{
		if (board_array[y][x+1]==0)
			turnRight(csize);
	}
}
void Board::getInitInkyPosition(int &x,int &y)
{
	//GetInitBombermanPosition(x,y);
	//x+=(xcellsize*2)-20;
	//y-=30;
	getInitClydePosition(x,y);
}
void Board::getInitClydePosition(int &x,int &y)
{
	if (bomberman.getX()+xcellsize*5<1000)
		x=(bomberman.getX()+xcellsize*5)-20;
	else if (bomberman.getX()-xcellsize*5>0)
		x=(bomberman.getX()-xcellsize*5)-20;
	else
		x=(bomberman.getX())-20;
	if (bomberman.getY()+(60*2)<750)
		y=bomberman.getY()+(60*2)-30;
	else
		y=bomberman.getY()-(60*2)-30;
	cout<<x<<","<<y<<endl;
}
double Board::remainingBrickPercentage()
{
	int presentBricks=0;
	for (int i=0;i<14;i++)
	{
		for (int j=0;j<17;j++)
		{
			if (board_array[i][j]==G_BRICK||board_array[i][j]==R_BRICK)
				presentBricks++;
		}
	}
	return (double(presentBricks)/double(initializedBricks))*100;
}
