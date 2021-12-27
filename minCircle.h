/*
 * aminCircle.h
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

bool inCircle(Circle c, Point p);

bool checkCircle(Circle c, vector<Point> points);

Circle circleByTwo(Point p1, Point p2);

Circle circleByThree(Point p1, Point p2, Point p3);

Circle trivialCircle(vector<Point> tmpVec);

Circle findMinCircle(Point** points,size_t size);

float dist(const Point& p1, const Point& p2);

// you can add here additional methods

#endif /* MINCIRCLE_H_ */
