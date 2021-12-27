/*
 * HybridAnomalyDetector.cpp
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnHelper(Point** points, correlatedFeatures &cf, size_t size) {
    Circle circle = findMinCircle(points, size);
    cf.point = circle.center;
    cf.radius = circle.radius * 1.1;
    cf.threshold = circle.radius * 1.1;
}

void HybridAnomalyDetector::detectHelper(Point** points, correlatedFeatures &cf, vector<AnomalyReport> &ar, size_t size) {
    Circle circle = Circle(cf.point, cf.radius);
    for (int i = 0; i < size; i++) {
        if (!inCircle(circle, *points[i])) {
            ar.push_back(AnomalyReport(cf.feature1 + "-" + cf.feature2, i + 1));
        }
    }
}
