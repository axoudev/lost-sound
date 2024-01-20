#ifndef STATMANAGER_H
#define STATMANAGER_H

#include <Arduino.h>

class StatManager {
public:
    StatManager(int numPins);
    void addValues(int* pinValues);
    float* getAverages();

private:
    int* values;
    int* counts;
    int numPins;
};

#endif