/*
 * Point.cpp
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#include "Point.h"

Point::Point(double x,double y) {
	// TODO Auto-generated constructor stub
	x_cordinate=x;
	y_cordinate=y;
}
void Point::set(double x,double y)
{
	x_cordinate=x;
	y_cordinate=y;
}
int Point::getX()
{
	return x_cordinate;
}
int Point::getY()
{
	return y_cordinate;
}
Point::~Point() {
	// TODO Auto-generated destructor stub
}

double Point::distance(Point& a)
{
	return sqrt(abs(pow(y_cordinate-a.getY(),2)+pow(x_cordinate-a.getX(),2)));
}
ostream& operator<<(ostream& out,Point& p)
{
	out<<"("<<p.getX()<<","<<p.getY()<<")";
	return out;
}
bool Point::operator ==(Point& p)
{
	return (x_cordinate==p.x_cordinate&&y_cordinate==p.y_cordinate);
}
