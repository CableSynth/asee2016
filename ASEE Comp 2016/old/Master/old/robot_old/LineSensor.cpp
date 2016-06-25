#include "LineSensor.h"
#include <Arduino.h>

LineSensor::LineSensor(const int* pinNums, int numOfPins) {
	sensors = numOfPins;

	current = new int [sensors];
	lastSeen = new int [sensors];

	for (int i = 0; i < numOfPins; ++i) {
		current[i] = lastSeen[i] = 0;
	}

	pins = new int [sensors];

	for (int i = 0; i < numOfPins; ++i) {
		pins[i] = pinNums[i];
		pinMode(pins[i], INPUT);
	}
}

void LineSensor::getCurrent(int* arr) {
   for (int i = 0; i < sensors; ++i) {
    arr[i] = current[i];
  }
}

void LineSensor::update () {
    int* temp;

    temp = getSensorData();
    for (int i = 0; i < sensors; ++i) {
        current[i] = temp[i];
    }  

    delete[] temp;
    
}

int LineSensor::getNumSeen() {
    int counter = 0;

    for (int i = 0; i < sensors; ++i) {
        if (current[i]) {
            ++counter;
        }
    }

    return counter;
}


int* LineSensor::getSensorData() {

	int* temp = new int [8];

	//get sensor data from all 8 pins
	for (int i = 0; i < sensors; ++i) {      
		temp[i] = digitalRead( pins[i] );             
	}
     
	return temp;
}
