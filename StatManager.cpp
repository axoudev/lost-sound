#include "StatManager.hpp"
#include <cmath>

StatManager::StatManager(int numPins) {
  this->numPins = numPins;
  values = new int*[numPins];
  counts = new int[numPins];

  for (int i = 0; i < numPins; ++i) {
    values[i] = nullptr;
    counts[i] = 0;
  }
}

StatManager::~StatManager() {
  for (int i = 0; i < numPins; ++i) {
    delete[] values[i];
  }
  delete[] values;
  delete[] counts;
}

void StatManager::addValues(int* pinValues) {
  for (int i = 0; i < numPins; ++i) {
    int* newValues = new int[counts[i] + 1];

    for (int j = 0; j < counts[i]; ++j) {
      newValues[j] = values[i][j];
    }

    newValues[counts[i]] = pinValues[i];

    delete[] values[i];

    values[i] = newValues;
    counts[i]++;
  }
}

float* StatManager::getAverages() {
  float* averages = new float[numPins];

  for (int i = 0; i < numPins; ++i) {
    float sum = 0;
    for (int j = 0; j < counts[i]; ++j) {
      sum += values[i][j];
    }
    averages[i] = (counts[i] > 0) ? sum / counts[i] : 0;
  }

  return averages;
}

float* getMedians();

float* StatManager::getMedians() {
  float* medians = new float[numPins];

  for (int i = 0; i < numPins; ++i) {
    int* sortedValues = new int[counts[i]];
    for (int j = 0; j < counts[i]; ++j) {
      sortedValues[j] = values[i][j];
    }

    for (int j = 0; j < counts[i] - 1; ++j) {
      for (int k = 0; k < counts[i] - j - 1; ++k) {
        if (sortedValues[k] > sortedValues[k + 1]) {
          int temp = sortedValues[k];
          sortedValues[k] = sortedValues[k + 1];
          sortedValues[k + 1] = temp;
        }
      }
    }

    if (counts[i] % 2 == 0) {
      medians[i] = (sortedValues[counts[i] / 2 - 1] + sortedValues[counts[i] / 2]) / 2.0f;
    } else {
      medians[i] = sortedValues[counts[i] / 2];
    }

    delete[] sortedValues;
  }

  return medians;
}

float* StatManager::getMinimums() {
  float* minimums = new float[numPins];

  for (int i = 0; i < numPins; ++i) {
    int minVal = (counts[i] > 0) ? values[i][0] : 0;
    for (int j = 1; j < counts[i]; ++j) {
      if (values[i][j] < minVal) {
        minVal = values[i][j];
      }
    }
    minimums[i] = minVal;
  }

  return minimums;
}

float* StatManager::getMaximums() {
  float* maximums = new float[numPins];

  for (int i = 0; i < numPins; ++i) {
    int maxVal = (counts[i] > 0) ? values[i][0] : 0;
    for (int j = 1; j < counts[i]; ++j) {
      if (values[i][j] > maxVal) {
        maxVal = values[i][j];
      }
    }
    maximums[i] = maxVal;
  }

  return maximums;
}

float* StatManager::getStandardDeviations() {
  float* deviations = new float[numPins];

  for (int i = 0; i < numPins; ++i) {
    deviations[i] = 0;
    if (counts[i] > 1) {
      float mean = getAverages()[i];
      float squaredDiffSum = 0;
      for (int j = 0; j < counts[i]; ++j) {
        float diff = values[i][j] - mean;
        squaredDiffSum += diff * diff;
      }
      deviations[i] = sqrt(squaredDiffSum / (counts[i] - 1));
    }
  }

  return deviations;
}

float* StatManager::getVariances() {
  float* variances = new float[numPins];

  for (int i = 0; i < numPins; ++i) {
    variances[i] = 0;
    if (counts[i] > 1) {
      float squaredDiffSum = 0;
      for (int j = 0; j < counts[i]; ++j) {
        float diff = values[i][j] - getAverages()[i];
        squaredDiffSum += diff * diff;
      }
      variances[i] = squaredDiffSum / (counts[i] - 1);
    }
  }

  return variances;
}
