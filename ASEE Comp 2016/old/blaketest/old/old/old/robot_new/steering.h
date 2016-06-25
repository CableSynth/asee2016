#ifndef STEERING_H
#define STEERING_H
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

namespace steering {

	static int statesCounter = 0;
	static int lastStates[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	
	// description: steers the nose
	// lineSensor: line following sensor
	// motor:      steering servo object
	// speed:      max speed the robot should go
	void steer(LineSensor lineSensor, Servo motor);


	// description: drives the motors
	// speed: max speed of the motors
	// angle: angle of nose
	//	 0: straight
	//	>0: turning left
	//	<0: turning right
	void drive(int angle, int speed);


	// description: gets angle to turn based on line data
	// lineSensor: line sensor on nose
	// return: angle to turn nose
	int getAngle(LineSensor lineSensor);


	// description: gets the current state of the line
	// array: line sensor data
	// size:  elements in line sensor array
	// return: current state based on line
	int getCurrentState(LineSensor lineSensor);


	// description: returns angle based on state
	// state: current state of the line sensor
	// return: angle to turn based on state
	int angleFromState(int state);


	// description: moves the motor by delta degrees
	// delta: angles to move servo by
	// motor: servo motor object to move
	void moveServo (int delta, Servo motor);


	// description: converts distance along circumference to degrees to turn
	// distance: distance to move along the circumference
	// radius:   radius of the circle
	// return:   angle to turn in degrees
	int toDegrees (int distance, int radius);


	// description: returns the ratio between the speeds at which
	//		the two motors should be driven
	// angle: angle of nose
	//	 0: straight
	//	>0: turning left
	//	<0: turning right
	// return: ratio between two motor speeds (left/right)
	double ratio(int angle);


	// description: adds state to array of past states
	// state: added to front of lastStates array
	void addToStates(int state);


	// description: returns a state from array of past states
	// state: which of last states to return
	// return: lastState[state]
	int getLastState(int state = 0);


	// NOTE: most of the time, moveServo should be called instead 
	//
	// sets the servo to a certain angle in degrees
	//		limits range to UPPER and LOWER bounds
	void setServo (int angle, Servo motor);
}

#endif
