/*
 * Ghost.cpp
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#include "Ghost.h"

Ghost::Ghost() :Character(),bfsArray({{NONE}}){
	// TODO Auto-generated constructor stub
}

Ghost::~Ghost() {
	// TODO Auto-generated destructor stub
}

void Ghost::getCellCordinates(int &x_,int &y_)
{
	y_=(810-(getY()))/60-1;
	x_=getX()/60;
}
void Ghost::setPosition(int x,int y)
{
	x_cordinate=x;
	y_cordinate=y;

}
void Ghost::turnLeft(int csize)
{
	x_cordinate-=csize;
}
void Ghost::turnRight(int csize)
{
	x_cordinate+=csize;
}
void Ghost::turnUp(int csize){
	y_cordinate+=csize;
	int x,y;
}
void Ghost::turnDown(int csize){

	y_cordinate-=csize;
	int x,y;

}


void Ghost::printBFSArray()
{
	for (int i=0;i<14;i++)
	{
		for (int j=0;j<17;j++)
			cout<<bfsArray[i][j]<<" ";
		cout<<endl;
	}
}

void getBfsCellCordinates(Point p,int &x,int &y)
{
	y=(810-(p.getY()))/60-1;
	x=p.getX()/60;
}
Directions Ghost::bfs(Point target)
{
	initializeBfsArray();
	bfsQueue.clear();
	double minDistance=Point(x_cordinate,y_cordinate).distance(target);
	double distance;
	Directions ret;
	int x,y;
	getBfsCellCordinates(Point(x_cordinate,y_cordinate),x,y);
	//cout<<"x: "<<x<<" y: "<<y-1<<endl;
	//cout<<"bfsArray: "<<bfsArray[y-1][x]<<endl;
	if (bfsArray[y+1][x]==0)//checking for down
	{
		//cout<<"down"<<endl;
		bfsQueue.push_back(Point(x_cordinate,y_cordinate-60));
		getBfsCellCordinates(Point(x_cordinate,y_cordinate-60),x,y);
		bfsArray[y][x]=DOWN;
	}
	getBfsCellCordinates(Point(x_cordinate,y_cordinate),x,y);
	if (bfsArray[y-1][x]==0)//checking for up
	{
		//cout<<"up"<<endl;
		bfsQueue.push_back(Point(x_cordinate,y_cordinate+60));
		getBfsCellCordinates(Point(x_cordinate,y_cordinate+60),x,y);
		bfsArray[y][x]=UP;
	}
	getBfsCellCordinates(Point(x_cordinate,y_cordinate),x,y);
	if (bfsArray[y][x-1]==0)//checking for left
	{
		//cout<<"left"<<endl;
		bfsQueue.push_back(Point(x_cordinate-60,y_cordinate));
		getBfsCellCordinates(Point(x_cordinate-60,y_cordinate),x,y);
		bfsArray[y][x]=LEFT;
	}
	getBfsCellCordinates(Point(x_cordinate,y_cordinate),x,y);
	if (bfsArray[y][x+1]==0)//checking for right
	{
		//cout<<"right"<<endl;
		bfsQueue.push_back(Point(x_cordinate+60,y_cordinate));
		getBfsCellCordinates(Point(x_cordinate+60,y_cordinate),x,y);
		bfsArray[y][x]=RIGHT;
	}
	getBfsCellCordinates(Point(x_cordinate,y_cordinate),x,y);
	Point temp;
	while (!bfsQueue.empty())
	{
		temp=bfsQueue.front();
		bfsQueue.pop_front();
		distance=temp.distance(target);
		if (distance<=minDistance)
		{
			minDistance=distance;
			int x_,y_;
			getBfsCellCordinates(temp,x_,y_);
			ret=bfsArray[y_][x_];
		}
		getBfsCellCordinates(temp,x,y);
		if (bfsArray[y+1][x]==0)//checking for down
		{
			bfsQueue.push_back(Point(temp.getX(),temp.getY()-60));
			getBfsCellCordinates(Point(temp.getX(),temp.getY()-60),x,y);
			int x_,y_;
			getBfsCellCordinates(temp,x_,y_);
			bfsArray[y][x]=bfsArray[y_][x_];
		}
		getBfsCellCordinates(temp,x,y);
		if (bfsArray[y-1][x]==0)//checking for up
		{
			bfsQueue.push_back(Point(temp.getX(),temp.getY()+60));
			getBfsCellCordinates(Point(temp.getX(),temp.getY()+60),x,y);
			int x_,y_;
			getBfsCellCordinates(temp,x_,y_);
			bfsArray[y][x]=bfsArray[y_][x_];
		}
		getBfsCellCordinates(temp,x,y);
		if (bfsArray[y][x-1]==0)//checking for left
		{
			bfsQueue.push_back(Point(temp.getX()-60,temp.getY()));
			getBfsCellCordinates(Point(temp.getX()-60,temp.getY()),x,y);
			int x_,y_;
			getBfsCellCordinates(temp,x_,y_);
			bfsArray[y][x]=bfsArray[y_][x_];
		}
		getBfsCellCordinates(temp,x,y);
		if (bfsArray[y][x+1]==0)//checking for right
		{
			bfsQueue.push_back(Point(temp.getX()+60,temp.getY()));
			getBfsCellCordinates(Point(temp.getX()+60,temp.getY()),x,y);
			int x_,y_;
			getBfsCellCordinates(temp,x_,y_);
			bfsArray[y][x]=bfsArray[y_][x_];
		}
	}
	//printBFSArray();
	//cout<<"bfs found"<<endl;
	return ret;
}
