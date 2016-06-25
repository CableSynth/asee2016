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

void LineSensor::getLastSeen(int* arr) {
	
  for (int i = 0; i < sensors; ++i) {
    arr[i] = lastSeen[i];
  }
  
}

void LineSensor::update () {
    int* temp;

    temp = getSensorData();

    if ( hasOneTrue() ) {      
        // shifts data from current to lastSeen and from temp to current
        for (int i = 0; i < sensors; ++i) {
            lastSeen[i] = current[i];
            current[i] = temp[i];
        }      
    } else {      
        //overwrites current with temp; does not affect lastSeen
        for (int i = 0; i < sensors; ++i) {
            current[i] = temp[i];
        }      
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

bool LineSensor::hasOneTrue () {

    for (int i = 0; i < sensors; ++i) {
        if (current[i]) {
            return true;
        }
    }

    return false;
}
