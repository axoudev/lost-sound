#ifndef STATMANAGER_HPP
#define STATMANAGER_HPP

class StatManager {
public:
  // Constructeur
  StatManager(int numPins);

  // Destructeur
  ~StatManager();

  // Ajoute les valeurs des broches analogiques
  void addValues(int* pinValues);

  // Calcule les moyennes des valeurs
  float* getAverages();

  // Calcule la médiane des valeurs
  float* getMedians();

  // Calcule les minimums des valeurs
  float* getMinimums();

  // Calcule les maximums des valeurs
  float* getMaximums();

  // Calcule les écarts types des valeurs
  float* getStandardDeviations();

  // Calcule les variances des valeurs
  float* getVariances();

private:
  int numPins;
  int** values;
  int* counts;

  // Calcule la médiane d'un tableau de valeurs
  float getMedians(int* values, int size);
};

#endif // STATMANAGER_HPP
