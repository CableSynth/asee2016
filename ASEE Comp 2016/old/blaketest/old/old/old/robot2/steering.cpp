#include "constants.h"
#include "steering.h"
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

void steering::steer(LineSensor lineSensor, int size, Servo motor, int speed) {

  
    int* data = new int [size];
    int priority;
    int angle;

    lineSensor.update();
    lineSensor.getCurrent(data);

    angle = getAngle(data, size);

    moveServo(angle, motor);

    angle = motor.read() - 90;

    drive(angle, speed);

    delete [] data;

    return;
}


int steering::getAngle(int*array, int size) {
    int state;

    state = getCurrentState(array, size);

    return angleFromState(state);
}


int steering::getCurrentState(int* array, int size) {

    int index;
    int leftMost;
    int amount = 0;
    int state;

    for (int i = 0; i < size; ++i) {
        if (array[i]) {
            if (amount == 0) {
              leftMost = i;
            }
            ++amount;
            index = i;
        } else if (amount) {
            break;
        }
    }

    switch(amount) {
        case 0:
            if (getLastState() > 0) {
                state = 8;
            } else {
                state = -8;
            }
            break;          
        case 1:
            state = index * 2 - 7;
            break;
        case 2:
            state = index * 2 - 8;
            break;
        default:
            if (3 - leftMost < index - 4) {
              state = 10; 
            } else {
              state = -10;
            }

            
    }
    addToStates(state);
    return state;
}


int steering::angleFromState(int state) {
    int angle;

    if (-8 < state && state < 8) {
        if (state < 0) {
            angle = -toDegrees(SENSOR_DISTANCES[-state], NOSE_LENGTH);
        } else {
            angle = toDegrees(SENSOR_DISTANCES[state], NOSE_LENGTH);
        }
    } else {
        return state * 2;      
    }    

    return angle;
}

int steering::getLastState(int n) {
    return lastStates[(statesCounter+9-n) % 5];
}


void steering::setServo (int angle, Servo motor ) {

// make sure angle is within valid range
    if (angle < STEERING_LOWER_BOUND) {
        angle = STEERING_LOWER_BOUND;
    } else if (angle > STEERING_UPPER_BOUND) {
        angle = STEERING_UPPER_BOUND;
    }   

    motor.write(angle);

    return;
}


void steering::moveServo (int delta, Servo motor ) {    

    setServo(delta + motor.read(), motor);

    return;
}


int steering::toDegrees (int distance, int radius) {

    return 360 * distance / (PI * 2 * radius);
}


void steering::addToStates(int state) {
    lastStates[statesCounter] = state;
    statesCounter = (statesCounter + 1) % 5;
}

void steering::drive(int angle, int speed) {
  int left;
  int right;
  if (angle > 0) {
    left  = speed;
    right = speed * ratio(angle);
  } else {
    right = speed;
    left  = speed/ratio(angle);
  }

  analogWrite(PWMR, right);
  analogWrite(PWML, left);

        if (millis()%1000 == 0) {
  Serial.println(right);
  Serial.println(left);
        }
}

double steering::ratio(int angle) {
  return angle / -75.0 + 1.0;
}

// ************ NO LONGER USED **************
/*
int steering::priorityEncoder(int* array, int size) {

    for (int i = 0; i <= (size - 3) / 2; ++i) {

        if (array[i]) {
            if (array[size - i - 1]) {
                continue;
            } else {
                return i;
            }
        } else if (array[size - i - 1]) {
            return size - i - 1;
        }
    }

    return 8;
}

int steering::howManyOnes(int* array, int size) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        count += array[i];
    }
    return count;
}*/
