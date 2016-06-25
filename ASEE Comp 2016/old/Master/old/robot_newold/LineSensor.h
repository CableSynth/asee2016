#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {

    private:

    	//how many sensors are on the line sensor board
    	int sensors;

    	//current data from line sensor
        int* current;

        //sdata from when line was last seen
        int* lastSeen;

        //list of the pins where the sensor is; [0] is L3 and [7] is R3
    	int* pins;
    	

    	//helper function return raw sensor data
    	int* getSensorData();
     
        //default constructor 
        //DO NOT USE
     	LineSensor();
    	
    public:
     	bool hasOneTrue();

    	//constructors
    	//NOTE: make sure you pass in an array of pin numbers!
    	//			this will not work properly otherwise.
    	LineSensor(const int* pinNums, int numOfPins = 8);


    	//will overwrite array with current line data
    	void getCurrent(int* array);


        //returns how many sensors see the line
        int getNumSeen();

    	//updates current and lastSeen
    	void update();

        //returns number of pins
        int howManyPins() {return sensors;}
};

#endif
