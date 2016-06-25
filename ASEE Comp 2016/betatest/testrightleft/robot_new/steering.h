#ifndef STEERING_H
#define STEERING_H
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

namespace steering {

	static int statesCounter = 0;
	static int lastStates[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  void stopRing();
  void dropRing();
  
	
	// description: steers the nose
	// lineSensor: line following sensor
	// motor:      steering servo object
	// speed:      max speed the robot should go
	bool steer(LineSensor lineSensor, Servo motor, int speed);


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
	int getAngle(LineSensor lineSensor, int motorAngle, int speed);


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


	// NOTE: most of the time, moveServo should be called instead 
	//
	// sets the servo to a certain angle in degrees
	//		limits range to UPPER and LOWER bounds
	void setServo (int angle, Servo motor);

}

#endif
