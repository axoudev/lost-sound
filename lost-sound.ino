// Hannah Flammang, 22.12.2023 
#include "StatManager.hpp" 

//CONST VALUES 
const int MAX_TENSION = 5; // 5.0 V from Arduino, 
const int RESOLUTION = 1023; //10 bit resolution = 1024 steps 
const int TRANSMISSION_SPEED = 9600; // 9600 bits per second 
const int LOOP_DELAY = 200; //milliseconds 
const int NB_ANALOG_PINS = 3; 
 
const int analogPins[] = {A0, A1, A2}; 
 /
StatManager statManager(NB_ANALOG_PINS); 
 
//VARIABLES 
int analogValues[NB_ANALOG_PINS]; 
 
void setup() { 
  // Initialize Serial communication 
  Serial.begin(TRANSMISSION_SPEED); 
} 
 
void loop() { 
  printAnalogValues(); 
 
  delay(LOOP_DELAY); 
} 
 
//FUNCTIONS 
 
/** 
* Convert analogValue to voltage value 
* 
* @param analogValue integer representing the analog value 
* @return float number representing voltage value 
*/ 
float analogToVolt(int analogValue) { 
  return (float) analogValue * MAX_TENSION / RESOLUTION;
} 
 
/** 
  * Prints analog value in serial monitor 
*/ 
void printAnalogValues() { 

  int pinValues[NB_ANALOG_PINS]; 
  
  for (int i = 0; i < NB_ANALOG_PINS; i++) {
    pinValues[i] = analogRead(analogPins[i]);
  }

  statManager.addValues(pinValues); 

  float* averages = statManager.getAverages(); 
  float* medians = statManager.getMedians();
  float* deviations = statManager.getStandardDeviations();
  float* variances = statManager.getVariances();

  for (int i = 0; i < NB_ANALOG_PINS; i++) {
    Serial.print(averages[i]);
    Serial.print(" "); 
    Serial.print(medians[i]);
    Serial.print(" "); 
    Serial.print(deviations[i]);
    Serial.print(" "); 
    Serial.print(variances[i]);
    Serial.print(" "); 
  }

  Serial.println(); 

  delete[] averages;
  delete[] medians;
  delete[] deviations;
  delete[] variances;
  delete[] pinValues;
} 