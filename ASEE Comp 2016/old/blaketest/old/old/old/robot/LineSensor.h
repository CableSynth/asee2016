#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {

private:

	//how mant sensors are on the line sensor board
	int sensors;

	//stores current data from line sensor
    int* current;

    //stores data from when line was last seen
    int* lastSeen;

    //list of the pins where the sensor is where [0] is L3 and [7] is R3
	int* pins;
	

	// Various helper member functions.
	int* getSensorData();
 
 	LineSensor();
	
public:
 bool hasOneTrue();

	//constructors
	//NOTE: make sure you pass in an array of pin numbers!
	//			this will not work properly otherwise.
	LineSensor(const int* pinNums, int numOfPins = 8);


	//will overwrite array with current line data
	void getCurrent(int* array);

	//will overwrite array with last seen line data
	void getLastSeen(int* array);


	//updates current and lastSeen
	void update();

};

#endif
