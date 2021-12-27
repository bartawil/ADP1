/*
 * timeseries.cpp
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */
#include "timeseries.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

TimeSeries::TimeSeries(const char *CSVfileName) {
    // create an input filestream
    ifstream file(CSVfileName);

    // make sure the file is open
    if(!file.is_open()) throw runtime_error("Could not open file");

    // extract the features name from the first line into string
    string line;
    getline(file, line);
    // helper
    string val;
    // create a string stream from the first line
    stringstream ss(line);
    // column values
    vector<float> values;
    // read the features names
    while (getline(ss, val, ',')) {
        this->features.push_back(val);
        // insert the map
        this->data[val] = values;
        //this->data.insert({ val, values });
    }

    // extract all values line by line
    while (getline(file, line)) {
        // helper
        int col = 0;
        // current line string stream
        stringstream ss(line);

        // extract each value to the correct vector in the map
        while (getline(ss, val, ',')) {
            data.find(features[col])->second.push_back(stof(val));
            col++;
        }
    }
    file.close();
}

vector<string> TimeSeries::getFeatures() const{
    return this->features;
}

map<string, vector<float>> TimeSeries::getData() const {
    return this->data;
}

int TimeSeries::csvSize() const {
    return this->data.find(this->features[0])->second.size();
}


