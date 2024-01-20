#include "StatManager.hpp"

StatManager::StatManager(int numPins) {
    this->numPins = numPins;
    values = new int[numPins];
    counts = new int[numPins];

    // Initialize values and counts arrays
    for (int i = 0; i < numPins; ++i) {
        values[i] = 0;
        counts[i] = 0;
    }
}

void StatManager::addValues(int* pinValues) {
    // Add the new values to the existing values and update counts
    for (int i = 0; i < numPins; ++i) {
        values[i] += pinValues[i];
        counts[i]++;
    }
}

float* StatManager::getAverages() {
    // Calculate and return the averages for each pin
    float* averages = new float[numPins];

    for (int i = 0; i < numPins; ++i) {
        averages[i] = (counts[i] > 0) ? static_cast<float>(values[i]) / counts[i] : 0;
    }

    return averages;
}
