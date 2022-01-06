cmake_minimum_required(VERSION 3.16)
project(ex6)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread -std=c++11")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(CMAKE_CXX_STANDARD 11)

add_executable(ex6 anomaly_detection_util.h anomaly_detection_util.cpp AnomalyDetector.h MainTrain.cpp
        SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp timeseries.h
        minCircle.cpp minCircle.h HybridAnomalyDetector.h HybridAnomalyDetector.cpp
        CLI.cpp CLI.h commands.h Server.cpp Server.h)
