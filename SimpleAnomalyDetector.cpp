/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    correlatedFeatures cfStruct;
    // features info
    vector<string> features = ts.getFeatures();
    int featureSize = features.size();
    // data info
    map<string, vector<float>> data = ts.getData();
    int dataSize = ts.csvSize();
    // finding correlated couples
    for (int i = 0; i < featureSize; i++) {
        string f1 = features.at(i);
        auto tmp1 = data.find(f1)->second;
        float *v1 = tmp1.data();
        // most correlated to f1
        string c;
        // max correlation for f1
        float maxC = 0;
        for (int j = i + 1; j < featureSize; j++) {
            string f2 = features.at(j);
            auto tmp2 = data.find(f2)->second;
            float *v2 = tmp2.data();
            // correlation between f1 and f2
            float tmpC = fabs(pearson(v1, v2, dataSize));
            // the algorithm threshold for correlation is 0.9
            if (tmpC > maxC && tmpC >= 0.9) {
                maxC = tmpC;
                c = f2;
            }
        }
        if (maxC != 0) {
            cfStruct.corrlation = maxC;
            cfStruct.feature1 = f1;
            cfStruct.feature2 = c;
            // create linear reg line
            auto tmp2 = data.find(c)->second;
            float *v2 = tmp2.data();
            auto p = new Point *[dataSize];
            createPointArr(p, v1, v2, dataSize);
            cfStruct.lin_reg = linear_reg(p, dataSize);
            // find the dev of each line
            float maxDev = 0;
            for (int k = 0; k < dataSize; k++) {
                float d = dev(*p[k], cfStruct.lin_reg);
                if (d > maxDev) {
                    maxDev = d;
                }
            }
            cfStruct.threshold = maxDev * 1.1;
            // push the struct to vector of correlated features
            this->cf.push_back(cfStruct);
            deletePoints(p, dataSize);
            delete[] p;
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // return value
    vector<AnomalyReport> ar;
    // data info
    map<string, vector<float>> data = ts.getData();
    int dataSize = ts.csvSize();

    int cfSize = this->cf.size();
    for (int i = 0; i < cfSize; i++) {
        // create points arr of the correlated features
        correlatedFeatures cfStruct = this->cf.at(i);
        string f1 = cfStruct.feature1;
        string f2 = cfStruct.feature2;
        auto t1 = data.find(f1)->second;
        float *v1 = t1.data();
        auto t2 = data.find(f2)->second;
        float *v2 = t2.data();
        auto p = new Point *[dataSize];
        createPointArr(p, v1, v2, dataSize);

        // check if there are anomaly by Dev method and the cf threshold
        Line l = cfStruct.lin_reg;
        float t = cfStruct.threshold;
        for (int j = 0; j < dataSize; j++) {
            float d = dev(*p[j], l);
            if (d > t) {
                ar.push_back(AnomalyReport(f1 + "-" + f2, j + 1));
            }
        }
        deletePoints(p, dataSize);
        delete[] p;
    }
    return ar;
}




