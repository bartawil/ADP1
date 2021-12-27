/*
 * minCircle.cpp
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */
#include "minCircle.h"
#include <math.h>

// find the distance between two points
float dist(const Point& p1, const Point& p2) {
    float x = pow(p1.x - p2.x, 2);
    float y = pow(p1.y - p2.y, 2);
    return sqrt(x + y);
}

// check if point is in circle
bool inCircle(Circle c, Point p) {
    if (c.radius < dist(c.center, p)) {
        return false;
    }
    return true;
}

// check if all points in circle
bool checkCircle(Circle c, vector<Point> points) {
    for (Point p: points) {
        if (!inCircle(c, p)) {
            return false;
        }
    }
    return true;
}

// create circle by two points
Circle circleByTwo(Point p1, Point p2) {
    Point m = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    float r = dist(p1, p2) / 2;
    return Circle(m, r);
}

// finds circle by three points
Circle circleByThree(Point a, Point b, Point c){
    float m1 = (a.y - b.y)/(a.x - b.x);
    float m2 = (a.y - c.y)/(a.x - c.x);

    float m1vertical = (-1)/m1;
    float m2vertical = (-1)/m2;

    float abMidX = (a.x + b.x)/2;
    float abMidY = (a.y + b.y)/2;
    float acMidX = (a.x + c.x)/2;
    float acMidY = (a.y + c.y)/2;

    float xCenter = (acMidY - abMidY + m1vertical*abMidX - m2vertical*acMidX)/(m1vertical - m2vertical);
    float yCenter = m1vertical * (xCenter - abMidX) + abMidY;

    Point center = Point(xCenter, yCenter);
    return Circle(center, dist(a, center));
}

// create circle according the size of the tmp point vec
Circle trivialCircle(vector<Point> tmpVec) {
    if (tmpVec.empty()) {
        return Circle(Point(0, 0), 0);
    } else if (tmpVec.size() == 1) {
        return Circle(tmpVec[0], 0);
    } else if (tmpVec.size() == 2) {
        return circleByTwo(tmpVec[0], tmpVec[1]);
    } else {
        // check if we can create circle by two point
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Circle c = circleByTwo(tmpVec[i], tmpVec[j]);
                if (checkCircle(c, tmpVec)) {
                    return c;
                }
            }
        }
    }
    return circleByThree(tmpVec[0], tmpVec[1], tmpVec[2]);
}

// recursive function that helps to find the min circle
Circle recursiveHelper(Point **&points, vector<Point> tmpVec, size_t size) {
    // stop condition if we check all points from arr
    if (size == 0 ) {
        return trivialCircle(tmpVec);
    }

    // stop condition if we have found the current boundary
    if (tmpVec.size() == 3) {
        return trivialCircle(tmpVec);
    }

    // get the last point from the points arr
    Point p = *points[size - 1];

    // find the min circle for size-1 points arr
    Circle c = recursiveHelper(points, tmpVec, size - 1);

    // checks if the new circle contains the prv point
    if (inCircle(c, p)) {
        return c;
    }

    // else the prv point should be on the boundary
    tmpVec.push_back(p);

    // recursive call with points - {p} && tmpVec + {p}
    return recursiveHelper(points, tmpVec, size - 1);
}

// find the min circle of all points
Circle findMinCircle(Point **points, size_t size) {
    return recursiveHelper(points, {}, size);
}