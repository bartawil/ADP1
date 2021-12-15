cmake_minimum_required(VERSION 3.16)
project(ex4)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex4 anomaly_detection_util.h anomaly_detection_util.cpp AnomalyDetector.h MainTrain.cpp
        SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp timeseries.h
        minCircle.cpp minCircle.h HybridAnomalyDetector.h HybridAnomalyDetector.cpp)
