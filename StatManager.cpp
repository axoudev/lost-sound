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

float StatManager::getMedians(int* sortedValues, int size) {
  int middle = size / 2;
  if (size % 2 == 0) {
    int middleMinusOne = middle - 1;
    return (sortedValues[middleMinusOne] + sortedValues[middle]) / 2.0f;
  } else {
    return sortedValues[middle];
  }
}

float* StatManager::getMedians() {
  float* medians = new float[numPins];

  for (int i = 0; i < numPins; ++i) {
    int* sortedValues = new int[counts[i]];
    for (int j = 0; j < counts[i]; ++j) {
      sortedValues[j] = values[i][j];
    }

    // Tri manuel
    for (int j = 0; j < counts[i] - 1; ++j) {
      for (int k = 0; k < counts[i] - j - 1; ++k) {
        if (sortedValues[k] > sortedValues[k + 1]) {
          int temp = sortedValues[k];
          sortedValues[k] = sortedValues[k + 1];
          sortedValues[k + 1] = temp;
        }
      }
    }

    medians[i] = getMedians(sortedValues, counts[i]);

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

  float* averages = getAverages();

  for (int i = 0; i < numPins; ++i) {
    deviations[i] = 0;
    if (counts[i] > 1) {
      float mean = averages[i];
      float squaredDiffSum = 0;
      for (int j = 0; j < counts[i]; ++j) {
        float diff = values[i][j] - mean;
        squaredDiffSum += diff * diff;
      }
      deviations[i] = sqrt(squaredDiffSum / (counts[i] - 1));
    }
  }

  delete[] averages;

  return deviations;
}

float* StatManager::getVariances() {
  float* variances = new float[numPins];

  // Stockez les moyennes dans une variable locale
  float* averages = getAverages();

  for (int i = 0; i < numPins; ++i) {
    variances[i] = 0;
    if (counts[i] > 1) {
      float squaredDiffSum = 0;
      for (int j = 0; j < counts[i]; ++j) {
        float diff = values[i][j] - averages[i];
        squaredDiffSum += diff * diff;
      }
      variances[i] = squaredDiffSum / (counts[i] - 1);
    }
  }

  // Libérez la mémoire allouée pour les moyennes
  delete[] averages;

  return variances;
}
