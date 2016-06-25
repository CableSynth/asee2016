#include "LineSensor.h"
#include <Arduino.h>

LineSensor::LineSensor(const int* pinNums, int numOfPins) {
	sensors = numOfPins;

	pins = new int [sensors];

	for (int i = 0; i < numOfPins; ++i) {
		pins[i] = pinNums[i];
		pinMode(pins[i], INPUT);
	}
}

void LineSensor::getCurrent(int* arr) {
	//get sensor data from all 8 pins
	for (int i = 0; i < sensors; ++i) {      
		arr[i] = digitalRead( pins[i] );             
	}
}