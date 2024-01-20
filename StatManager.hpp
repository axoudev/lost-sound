#ifndef STATMANAGER_HPP
#define STATMANAGER_HPP

class StatManager {
public:
  StatManager(int numPins);
  ~StatManager();

  void addValues(int* pinValues);
  float* getAverages();
  float* getMedians();
  float* getMinimums();
  float* getMaximums();
  float* getStandardDeviations();
  float* getVariances();

private:
  int numPins;
  int** values;
  int* counts;
};

#endif
