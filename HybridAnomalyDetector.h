/*
 * HybridAnomalyDetector.h
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual void learnHelper(Point** points, correlatedFeatures &cf, size_t size);
    virtual void detectHelper(Point** points, correlatedFeatures &cf, vector<AnomalyReport> &ar, size_t size);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
