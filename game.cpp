//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef Bomberman_CPP_
#define Bomberman_CPP_
#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include "Point.h"
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include "Bomb.h"
using namespace std;
//bool bombStatus = false;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */

void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw = 6/*Enemy Width in Units*/,
		float gh = 7/*Enemy Height in Units*/) {
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float) gw / ogw, sy = (float) gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/,
		const ColorNames &colorname/*Bomberman Colour*/,char a='u') {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin (GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	if (a=='u')
	{
		for (int i = 0; i < npmvertices; ++i)
			glVertex4f(sx + pmvertices[i][1], sy - pmvertices[i][0], 0, 1);
	}
	if (a=='d')
	{
		for (int i = 0; i < npmvertices; ++i)
			glVertex4f(sx + pmvertices[i][1], sy + pmvertices[i][0], 0, 1);
	}
	if (a=='l')
	{
		for (int i = 0; i < npmvertices; ++i)
			glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	}
	if (a=='r')
	{
		for (int i = 0; i < npmvertices; ++i)
			glVertex4f(sx - pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	}

	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}
/*
 * Main Canvas drawing function.
 * */
Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	//
	if (b->gamestate==READY)
	{
		b->Draw();
		int x, y;
		//b->GetInitPinkyPosition(x, y);
		//cout << x << "  y= " << y << endl << flush;
		if (b->pinkyStatus==true)
			DrawEnemy(b->pinky.getX(), b->pinky.getY(), PINK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		if (b->blinkyStatus==true)
			DrawEnemy(b->blinky.getX(), b->blinky.getY(), RED, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		if (b->inkyStatus==WORKING)
			DrawEnemy(b->inky.getX(), b->inky.getY(), GREEN, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		if (b->clydeStatus==WORKING)
			DrawEnemy(b->clyde.getX(), b->clyde.getY(), ORANGE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		//b->GetInitBombermanPosition(x, y);
		DrawBomberman(b->bomberman.getX(), b->bomberman.getY(), b->GetCellSize() / 2 - 2, YELLOW,b->bomberman.getMotion());
		b->GetInitTextPosition(x, y);
		//cout << endl <<"Text Position = "<< x << "  y= " << y << endl << flush;
		DrawString(x, y, "Score = "+Num2Str(Board::score), colors[5]);
		DrawString(x+200, y, "Lives = "+Num2Str(b->bomberman.getLives()), colors[5]);
		DrawString(x+400, y, "Time = "+Num2Str(Board::time), colors[5]);
		DrawString(x+600, y, "Level = "+Num2Str(Board::levels), colors[5]);
		//	glPopMatrix();
		if (b->bombStatus == true) {
			DrawCircle(b->bomb->getX(),b->bomb->getY() , 15, colors[RED]); // To Draw a bomb. You will provide your own x and y relative to Bombermans position
			//bombStatus = false;
			if (b->bomb->bomb_time==0)
			{
				int x_g,y_g,x_bomb,y_bomb;
				b->bomberman.getCellCordinates(x_g,y_g);
				b->bomb->getCellCordinates(x_bomb,y_bomb);
				if ((x_g==x_bomb&&y_g==y_bomb)||(x_g==x_bomb+1&&y_g==y_bomb)||(x_g==x_bomb-1&&y_g==y_bomb)||(x_g==x_bomb&&y_g==y_bomb+1)||(x_g==x_bomb&&y_g==y_bomb-1))
				{
					b->bomberman.getLives()--;
					int x_b,y_b;
					b->GetInitBombermanPosition(x_b,y_b);
					b->bomberman.setPosition(x_b,y_b);
					b->reset(1);
				}
			}
		}
		if (b->bomberman.getLives()==0)
			b->gamestate=GAMEOVER;
		//b->ghost->move(b->ghost->bfs(Point(b->bomberman.getX(),b->bomberman.getY())));
		int x_b,y_b,x_g,y_g;
		b->bomberman.getCellCordinates(x_b,y_b);
		if (b->pinkyStatus==true)
		{
			b->pinky.getCellCordinates(x_g,y_g);
			if (x_b==x_g&&y_b==y_g)
			{
				b->bomberman.getLives()-=1;
				b->GetInitBombermanPosition(x_b,y_b);
				b->bomberman.setPosition(x_b,y_b);
				b->reset(1);
			}
		}
		if (b->blinkyStatus==true)
		{
			b->blinky.getCellCordinates(x_g,y_g);
			if (x_b==x_g&&y_b==y_g)
			{
				b->bomberman.getLives()-=1;
				b->GetInitBombermanPosition(x_b,y_b);
				b->bomberman.setPosition(x_b,y_b);
				b->reset(1);
			}
		}
		if (b->inkyStatus==WORKING)
		{
			b->inky.getCellCordinates(x_g,y_g);
			if (x_b==x_g&&y_b==y_g)
			{
				b->bomberman.getLives()-=1;
				b->GetInitBombermanPosition(x_b,y_b);
				b->bomberman.setPosition(x_b,y_b);
				b->reset(1);
			}
		}
		if (b->clydeStatus==WORKING)
		{
			b->clyde.getCellCordinates(x_g,y_g);
			if (x_b==x_g&&y_b==y_g)
			{
				b->bomberman.getLives()-=1;
				b->GetInitBombermanPosition(x_b,y_b);
				b->bomberman.setPosition(x_b,y_b);
				b->reset(1);
			}
		}
		if (b->inkyStatus==UNUSED)
		{
			if (b->remainingBrickPercentage()<70)
			{
				int x_i,y_i;
				b->getInitInkyPosition(x_i,y_i);
				b->inky.setPosition(x_i,y_i);
				b->inkyStatus=WORKING;
			}
		}
		if (b->clydeStatus==UNUSED)
		{
			if (b->remainingBrickPercentage()<30)
			{
				int x_c,y_c;
				b->getInitClydePosition(x_c,y_c);
				b->clyde.setPosition(x_c,y_c);
				b->clydeStatus=WORKING;
			}
		}
		if (b->pinkyStatus==false&&b->blinkyStatus==false&&b->inkyStatus==DESTROYED&&b->clydeStatus==DESTROYED)
		{
			b->gamestate=WINNER;
			b->reset(2);
		}
		if (b->time<=0)
			b->gamestate=GAMEOVER;
	}
	if (b->gamestate==START)
		DrawString(400,400,"press S to start",colors[5]);
	if (b->gamestate==PAUSE)
		DrawString(300,400,"game paused\n press R to resume",colors[5]);
	if (b->gamestate==GAMEOVER)
		DrawString(300,400,"GAMEOVER (Press S to restart)",colors[5]);
	if (b->gamestate==WINNER)
		DrawString(300,400,"YOU WIN",colors[5]);
	glutPostRedisplay();
	glutSwapBuffers(); // do not modify this line..

}
void Timer(int m) {

	// implement your functionality here
	if (b->gamestate==READY)
	{
		Board::time--;
		if (b->bombStatus==true)
		{
			if (b->bomb->bomb_time==0)
			{
				b->bomb->explode(b->bomb->getX(),b->bomb->getY());
				//delete b->bomb;
				b->bombStatus=false;
			}
			b->bomb->bomb_time--;
		}
		if (b->pinkyStatus==true)
		{
			b->pinky.move(b->pinky.bfs(Point(GetRandInRange(0,800),GetRandInRange(0,800))));
		}
		if (b->blinkyStatus==true)
		{
			if (b->chase==true)
			{
				b->blinky.move(b->blinky.bfs(Point(b->bomberman.getX(),b->bomberman.getY())));
				b->stateCount--;
				if (b->stateCount==0)
				{
					b->chase=false;
					b->scatter=true;
					b->stateCount=7;
				}
			}
			else if (b->scatter==true)
			{
				//Point arr[4]={Point(0,0),Point(800,800),Point(0,800),Point(800,0)};
				b->blinky.move(b->blinky.bfs(Point(800,800)));
				b->stateCount--;
				if (b->stateCount==0)
				{
					b->chase=true;
					b->scatter=false;
					b->stateCount=20;
				}
			}
			//cout<<b->stateCount<<endl;
		}
		if (b->inkyStatus==WORKING)
		{
			if (b->chase==true)
			{
				b->inky.move(b->inky.bfs(Point(b->bomberman.getX(),b->bomberman.getY())));
				b->stateCount--;
				if (b->stateCount==0)
				{
					b->chase=false;
					b->scatter=true;
					b->stateCount=7;
				}
			}
			else if (b->scatter==true)
			{
				//Point arr[4]={Point(0,0),Point(800,800),Point(0,800),Point(800,0)};
				b->inky.move(b->inky.bfs(Point(800,800)));
				b->stateCount--;
				if (b->stateCount==0)
				{
					b->chase=true;
					b->scatter=false;
					b->stateCount=20;
				}
			}
		}
		if (b->clydeStatus==WORKING)
		{
			if (b->chase==true)
			{
				b->clyde.move(b->clyde.bfs(Point(b->bomberman.getX(),b->bomberman.getY())));
				b->stateCount--;
				cout<<"clyde moving\n";
				if (b->stateCount==0)
				{
					b->chase=false;
					b->scatter=true;
					b->stateCount=7;
				}
			}
			else if (b->scatter==true)
			{
				//Point arr[4]={Point(0,0),Point(800,800),Point(0,800),Point(800,0)};
				b->clyde.move(b->clyde.bfs(Point(800,800)));
				b->stateCount--;
				if (b->stateCount==0)
				{
					b->chase=true;
					b->scatter=false;
					b->stateCount=20;
				}
			}

			//cout<<b->stateCount<<endl;

			//cout<<b->stateCount<<endl;
		}
	}

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}
void timer(int m)
{
	cout<<"timer 2"<<endl;
	glutTimerFunc(10.0,timer,0);
}


/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	//cout<<"key: "<<key<<endl;
	if (b->gamestate==READY)
	{
		if (key
				== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
			// what to do when left key is pressed...
			b->bomberman.turnLeft(b->bomberman.getCell(b->bomberman.getX()-b->GetCellSize(),b->bomberman.getY()),b->GetCellSize());
			b->bomberman.setMotion('l');
		} else if (key
				== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
			b->bomberman.turnRight(b->bomberman.getCell(b->bomberman.getX()+b->GetCellSize(),b->bomberman.getY()),b->GetCellSize());
			b->bomberman.setMotion('r');
		} else if (key
				== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
			b->bomberman.turnUp(b->bomberman.getCell(b->bomberman.getX(),b->bomberman.getY()+b->GetCellSize()),b->GetCellSize());
			b->bomberman.setMotion('u');
		}
		else if (key
				== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
			b->bomberman.turnDown(b->bomberman.getCell(b->bomberman.getX(),b->bomberman.getY()-b->GetCellSize()),b->GetCellSize());
			b->bomberman.setMotion('d');
		}

		//cout<<b->bomberman.getPosition()<<endl;

	}



	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/


}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	//cout<<"key: "<<key<<endl;
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	if (b->gamestate==READY)
	{

		if (key=='p'||key=='P')
			b->gamestate=PAUSE;
		if (key == 'b' || key == 'B' ) //Key for placing the bomb
				{
			if (b->bombStatus==false)
			{
				b->bombStatus = true;
				b->bomb=new Bomb(b->bomberman.getX(),b->bomberman.getY());

			}
			//glutTimerFunc(5000.0, Timer, 0);
		}

	}
	if (b->gamestate==START)
	{
		if (key=='s'||key=='S')
			b->gamestate=READY;
	}
	if (b->gamestate==PAUSE)
	{
		if (key=='r'||key=='R')
			b->gamestate=READY;
	}
	if (b->gamestate==GAMEOVER)
		if (key=='s'||key=='S')
		{
			b->reset(0);
			b->gamestate=START;
			b->bomberman.getLives()+=3;
		}
	//cout<<GameStates(b->gamestate);
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 0); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomber Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	//b->printBoardArray();
	//cout<<endl;
	b->blinky.initializeBfsArray();
	//b->ghost->printBFSArray();
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutTimerFunc(10.0,timer,0);
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
