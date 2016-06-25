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
	bool hasOneTrue(const int* arr);
	int* getSensorData();
 
 LineSensor();
	
public:

	//constructors
	//NOTE: make sure you pass in an array of pin numbers!
	//			this will not work properly otherwise.
	LineSensor(const int* pinNums, int numOfPins = 8);


	//returns a copy of the current data
	int* getCurrent();
	//will make sure to deallocate the memory
	void getCurrent(int*);

	//returns copy of the data from when the line was last seen
	int* getLastSeen();
	//will make sure to deallocate the memory
	void getLastSeen(int*);


	//updates current and lastSeen
	void update();

};

#endif
