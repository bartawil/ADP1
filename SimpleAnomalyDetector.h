/*
 * anomaly_detection_util.h
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Point point = Point(0,0);
    float radius = 0;
};


class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
    vector<correlatedFeatures> cf;
    float correlationThreshold = 0.9;
public:
    SimpleAnomalyDetector();

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }

    virtual void learnHelper(Point** points, correlatedFeatures &cf, size_t size)=0;

    virtual void detectHelper(Point** points, correlatedFeatures &cf, vector<AnomalyReport> &ar, size_t size)=0;

    float getCorrelationThreshold() {
        return correlationThreshold;
    }

    void setCorrelationThreshold(float newCorrelation) {
        this->correlationThreshold = newCorrelation;
    }
};


#endif /* SIMPLEANOMALYDETECTOR_H_ */
