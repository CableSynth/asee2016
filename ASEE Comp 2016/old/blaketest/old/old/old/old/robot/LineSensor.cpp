#include "LineSensor.h"
#include <Arduino.h>


LineSensor::LineSensor() {
	sensors = 0;
	current = lastSeen = pins = 0x0;
}

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


int* LineSensor::getCurrent () {
	int* temp = new int [sensors];

	for (int i = 0; i < sensors; ++i) {
		temp[i] = current[i];
	}

	return temp;
}

void LineSensor::getCurrent(int* arr) {
   for (int i = 0; i < sensors; ++i) {
    arr[i] = current[i];
  }
}


int* LineSensor::getLastSeen () {
	int* temp = new int [sensors];

	for (int i = 0; i < sensors; ++i) {
		temp[i] = lastSeen[i];
	}

	return temp;
}

void LineSensor::getLastSeen(int* arr) {
	
  for (int i = 0; i < sensors; ++i) {
    arr[i] = lastSeen[i];
  }
  
}


/**
 * This function updates the arrays current and lastSeen. 
 * lastSeen will only be overwritten if current has at least one true.
 * 
 * @author Blake Lasky
 * 
 * @param current current line data array
 * @param lastSeen reading data from last time we got at least one true reading
 * @param pinSpots pins corresponding to the previous two data arrays
 * @param arraySize size of the previous three arrays
 */
void LineSensor::update () {
    int* temp;

    temp = getSensorData();

    if ( hasOneTrue(current) ) {      
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


/**
 * This function reads pins from pinSpots into array lineData of size arraySize.
 * 
 * @author Blake Lasky
 * 
 * @param lineData is an array which will be overidden with new data
 * @param pinSpots stores the pin numbers to read data in to put in lineData
 * @param arraySize stores the size of the other arrays; defaults to 8
 */
int* LineSensor::getSensorData() {

	int* temp = new int [8];

	//get sensor data from all 8 pins
	for (int i = 0; i < sensors; ++i) {      
		temp[i] = digitalRead( pins[i] );             
	}
     
	return temp;
}


/**
 * This function takes an array and check to make sure it has at least one true value
 * 
 * @author Blake Lasky
 * 
 * @param array the array to iterate through and check for a true value
 * @param arraySize size of the array passed in
 * 
 * @return returns whether or not there was at least one true value
 */
bool LineSensor::hasOneTrue (const int* array) {

    for (int i = 0; i < sensors; ++i) {
        if (array[i]) {
            return true;
        }
    }

    return false;
}
