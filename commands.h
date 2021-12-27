/*
 * commands.h
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <sstream>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

#include <iostream>
#include <fstream>

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    void createFile(string fileName) {
        ofstream out(fileName);
        string line = this->read();
        while( line != "done" )
        {
            out << line << endl;
            line = this->read();
        }
        out.close();
    }

    // you may add additional methods here
};

// you may add here helper classes
class Data{
public:
    HybridAnomalyDetector hd;
    vector<AnomalyReport> ar;
    TimeSeries *tsTrain;
    TimeSeries *tsTest;
};

// you may edit this class
class Command {
protected:
    DefaultIO *dio;
    Data* data;
public:
    Command(DefaultIO *dio, Data* data) : dio(dio), data(data) {}

    virtual void execute() = 0;

    virtual ~Command() {}
};

// implement here your command classes
class UploadFiles : public Command {
public:
    UploadFiles(DefaultIO *dio, Data *data) : Command(dio, data) {}
    void execute() {
        dio->write("Please upload your local train CSV file.\n");
        dio->createFile( "anomalyTrain.csv");
        this->data->tsTrain = new TimeSeries("anomalyTrain.csv");
        dio->write("Upload complete.\n"
                   "Please upload your local test CSV file.\n");
        dio->createFile("anomalyTest.csv");
        this->data->tsTest = new TimeSeries("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }
};

class Correlation : public Command {
public:
    Correlation(DefaultIO *dio, Data *data) : Command(dio, data) {}
    void execute() {
        dio->write("The current correlation threshold is ");
        dio->write(this->data->hd.getCorrelationThreshold());
        dio->write("\nType a new threshold\n");
        float newCorr = stof(dio->read());
        while (newCorr < 0 || newCorr > 1) {
            dio->write("“please choose a value between 0 and 1");
            newCorr = stof(dio->read());
        }
        this->data->hd.setCorrelationThreshold(newCorr);
    }
};

class AnomalyCheck : public Command{
public:
    AnomalyCheck(DefaultIO *dio, Data *data) : Command(dio, data) {}
    void execute() {
        this->data->hd.learnNormal(*this->data->tsTrain);
        this->data->ar = this->data->hd.detect(*this->data->tsTest);
        dio->write("anomaly detection complete.\n");
    }
};

class PrintAnomaly : public Command {
public:
    PrintAnomaly(DefaultIO *dio, Data *data) : Command(dio, data) {}
    void execute() {
        vector<AnomalyReport> vec = this->data->ar;
        int size = this->data->ar.size();
        string description;
        int timeStep = 0;
        for (int i = 0; i < size; i++) {
            description = vec.at(i).description;
            timeStep = vec.at(i).timeStep;
            dio->write(timeStep);
            dio->write("\t");
            dio->write(description + "\n");
        }
        dio->write("Done.\n");
    }
};

class Rate : public Command {
    vector<pair<int, int>> clientAnomalies;
    vector<pair<string, pair<int, int>>> groupedAnomalies;
    int n = 0; // total number of lines
    int p = 0; // number of total report lines
    float P = 0; // size of reports from client
    float N = 0; // N = n - p
    float TP = 0; // number of true positive alarms
    float FP = 0; // number of false positive alarms
public:
    Rate(DefaultIO *dio, Data *data) : Command(dio, data) {}
    void getAnomalies(string line) {
        // save each line
        vector<int> points;
        // save begin-end pair of anomalies
        pair<int, int> pairs;
        while( line != "done" )
        {
            points.clear();
            stringstream ss(line);
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                points.push_back(stoi(substr));
            }
            pairs.first = points.at(0);
            pairs.second = points.at(1);
            // calculate number of lines for each report
            this->p += pairs.second - pairs.first + 1;
            this->clientAnomalies.push_back(pairs);
            line = dio->read();
        }
        this->P = this->clientAnomalies.size();
    }
    void groupedAr() {
        vector<AnomalyReport> vec = this->data->ar;
        int size = vec.size();

        int start = 0;
        int end = 0;
        int tmp;
        string description;

        pair<string, pair<int, int>> anomaly;
        for (int i = 0; i < size; i++) {
            start = i;
            tmp = 0;
            if (i + 1 != size) {
                while (vec.at(start).description == vec.at(i + 1).description
                       && vec.at(i).timeStep + 1 == vec.at(i + 1).timeStep) {
                    i++;
                    tmp++;
                    if (i + 1 == size) {
                        break;
                    }
                }
            }
            end = start + tmp;
            anomaly.first = vec.at(start).description;
            anomaly.second.first = vec.at(start).timeStep;
            anomaly.second.second = vec.at(end).timeStep;
            this->groupedAnomalies.push_back(anomaly);
        }
    }
    void checkAlarms() {
        int clientSize = this->clientAnomalies.size();
        int detectSize = this->groupedAnomalies.size();
        int flag;
        for (int i = 0; i < detectSize; i++) {
            flag = 0;
            pair<int, int> detect = groupedAnomalies.at(i).second;
            for (int j = 0; j < clientSize; j++) {
                pair<int, int> client = clientAnomalies.at(j);
                if (client.first <= detect.second && client.second >= detect.first) {
                    flag = 1;
                    this->TP++;
                }
                else if (client.second >= detect.first && client.first <= detect.second) {
                    flag = 1;
                    this->TP++;
                }
                else if (client.first <= detect.first && client.second >= detect.second) {
                    flag = 1;
                    this->TP++;
                }
                else if (client.second <= detect.second && client.first >= detect.first) {
                    flag = 1;
                    this->TP++;
                }
            }
            if (flag != 1) {
                this->FP++;
            }
        }
    }
    void execute() {
        dio->write("Please upload your local anomalies file.\n");
        // initialize
        this->clientAnomalies.clear();
        this->groupedAnomalies.clear();
        this->n = this->data->tsTest->csvSize(); // total number of lines
        this->p = 0; // number of total report lines
        this->P = 0; // size of reports from client
        this->N = 0; // N = n - p
        this->TP = 0; // number of true positive alarms
        this->FP = 0; // number of false positive alarms
        // gets all anomalies from client and save them
        getAnomalies(dio->read());
        dio->write("Upload complete.\n");
        // group all anomalies from detector by time step and description
        groupedAr();
        checkAlarms();
        this->N = this->n - this->p;
        dio->write("True Positive Rate: ");
        dio->write(floor(1000 * (this->TP/this->P)) / 1000);
        dio->write("\n");
        dio->write("False Positive Rate: ");
        dio->write(floor(1000 * (this->FP/this->N)) / 1000);
        dio->write("\n");
    }
};

class End : public  Command {
public:
    End(DefaultIO* dio, Data* data) : Command(dio, data) {}
    void execute() {}
};


#endif /* COMMANDS_H_ */
