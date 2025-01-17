/*
 * anomaly_detection_util.h
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */
#ifndef ANOMALYDETECTORUTIL_H_
#define ANOMALYDETECTORUTIL_H_

float avg(const float* x, int size);

// returns the variance of X and Y
float var(float* x, int size);

// returns the covariance of X and Y
float cov(float* x,  float* y, int size);


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size);

class Line{
public:
	float a,b;
	Line():a(0),b(0){}
	Line(float a, float b):a(a),b(b){}
	float f(float x){
		return a*x+b;
	}
};

class Point{
public:
	float x,y;
	Point(float x, float y):x(x),y(y){}
};

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size);

// returns the deviation between point p and the line
float dev(Point p,Line l);

//Creates a points Arr by using two arrays of floats
void createPointArr(Point **&p, float *f1, float *f2, int size);

// free all points form the Point array
void deletePoints(Point **&p, int size);

#endif
