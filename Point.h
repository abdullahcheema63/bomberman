/*
 * Point.h
 *
 *  Created on: May 7, 2017
 *      Author: abdullah
 */

#ifndef POINT_H_
#define POINT_H_
#include <iostream>
#include <cmath>
using namespace std;
class Point {
	double x_cordinate;
	double y_cordinate;
public:
	Point(double x=0,double y=0);
	void set(double x,double y);
	int getX();
	int getY();
	bool operator==(Point &p);
	double distance(Point& a);
	virtual ~Point();
};
ostream& operator<<(ostream&out,Point& p);
#endif /* POINT_H_ */
