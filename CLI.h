/*
 * CLI.h
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    Data* data;
    // you can add data members
    UploadFiles* uploadFiles;
    Correlation* correlation;
    AnomalyCheck* anomalyCheck;
    PrintAnomaly* printAnomaly;
    Rate* rate;
    End* end;

    vector<Command*> commands;
public:
	CLI(DefaultIO* dio);
	void start();
	virtual ~CLI();
};

#endif /* CLI_H_ */
