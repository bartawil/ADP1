/*
 * CLI.cpp
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->data = new Data();
    // creat objects from each command class
    this->uploadFiles = new UploadFiles(dio, data);
    this->correlation = new Correlation(dio, data);
    this->anomalyCheck = new AnomalyCheck(dio, data);
    this->printAnomaly = new PrintAnomaly(dio, data);
    this->rate = new Rate(dio, data);
    this->end = new End(dio, data);
    // push all commands to vector
    commands.push_back(this->uploadFiles);
    commands.push_back(this->correlation);
    commands.push_back(this->anomalyCheck);
    commands.push_back(this->printAnomaly);
    commands.push_back(this->rate);
    commands.push_back(this->end);
}

void CLI::start() {
    int option = 0;
    // if option is 6 we will exit and end the program
    while (option != 6) {
        dio->write("Welcome to the Anomaly Detection Server.\n"
                   "Please choose an option:\n"
                   "1.upload a time series csv file\n"
                   "2.algorithm settings\n"
                   "3.detect anomalies\n"
                   "4.display results\n"
                   "5.upload anomalies and analyze results\n"
                   "6.exit\n");
        option = stoi(this->dio->read());
        commands.at(option - 1)->execute();
    }
    commands.at(option - 1)->execute();
}


CLI::~CLI() {
    delete data->tsTest;
    delete data->tsTrain;
    delete data;
    delete uploadFiles;
    delete correlation;
    delete anomalyCheck;
    delete printAnomaly;
    delete rate;
    delete end;
}

