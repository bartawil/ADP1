/*
 * timeseries.h
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <map>
#include <vector>

using namespace std;

class TimeSeries{
    // reads a CSV file into a map of <string, vec<float>>
    map<string, vector<float>> data;
    // features name vector
    vector<string> features;
public:

	TimeSeries(const char* CSVfileName);

    vector<string> getFeatures() const;

    map<string, vector<float>> getData() const;

    int csvSize() const;
};



#endif /* TIMESERIES_H_ */
