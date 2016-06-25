#ifndef STEERING_H
#define STEERING_H
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

namespace steering {

	static int statesCounter = 0;
	static int lastStates[5] = {0, 0, 0, 0, 0};


	int getAngle(int* array, int size);

	int getCurrentState(int* array, int size);

	void addToStates(int state);

	int getLastState(int state = 0);

	int angleFromState(int state);

  void drive(int angle, int speed);

  double ratio(int angle);

	
	/*
	int priorityEncoder(int* array, int size);
	int howManyOnes(int* array, int size);
	*/

	/**
	 * This function sets the servo to a certain angle in degrees.
	 * This function limits the input to [50, 110].
	 * 
	 * @author Blake Lasky
	 * @param angle the angle to set the servo to
	 * @param motor the servo the move
	 */
	 void setServo (int angle, Servo motor );


	/**
	 * This function changes the servos position by delta degrees.
	 * This function limits the input to [50, 110].
	 * 
	 * @author Blake Lasky
	 * @param angle the angle to change the current motor position by
	 */
	 void moveServo (int delta, Servo motor );


	//takes the array with numbers in it
	//adds the numbers together and steers with it
	 void steer(LineSensor lineSensor, int size, Servo motor, int speed);


	/**
	 * This function takes in a distance to move along the circumference
	 * and the radius of the circle.
	 * 
	 * @author Blake Lasky 
	 * @param angle the angle to set 
	 * @return degrees to turn to achieve desired distance
	 */
	 int toDegrees (int distance, int radius);

}

#endif
