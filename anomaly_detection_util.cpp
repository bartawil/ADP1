/*
 * anomaly_detection_util.cpp
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + x[i];
    }
    return sum / size;
}

// returns the variance of X and Y
float var(float *x, int size) {
    float average = avg(x, size);
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + pow(x[i] - average, 2);
    }
    return sum / size;
}


// returns the covariance of X and Y
float cov(float *x, float *y, int size) {
    float averageX = avg(x, size);
    float averageY = avg(y, size);
    float mult[size];
    for (int i = 0; i < size; i++) {
        mult[i] = x[i] * y[i];
    }
    float averageXY = avg(mult, size);
    return averageXY - (averageX * averageY);
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size) {
    float covariance = cov(x, y, size);
    float stdX = sqrt(var(x, size));
    float stdY = sqrt(var(y, size));
    return covariance / (stdX * stdY);
}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size) {
    float x[size];
    float y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float a = cov(x, y, size) / var(x, size);
    float b = avg(y, size) - a * avg(x, size);
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    return fabs(l.f(p.x) - p.y);
}

//Creates a points Arr by using two arrays of floats
void createPointArr(Point **&p, float *f1, float *f2, int size) {
    for (int i = 0; i < size; i++) {
        p[i] = new Point(f1[i], f2[i]);
    }
}

// free all points form the Point array
void deletePoints(Point **&p, int size) {
    for (int i = 0; i < size; i++) {
        delete p[i];
    }
}





