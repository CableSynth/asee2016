#include "constants.h"
#include "steering.h"
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

void steering::steer(LineSensor lineSensor, Servo motor) {

    int priority;
    int angle;
    int size = lineSensor.howManyPins();
    int* data = new int [size];

    lineSensor.update();
    lineSensor.getCurrent(data);

    angle = getAngle(lineSensor);

    moveServo(angle, motor);

    delete [] data;

    return;
}


int steering::getAngle(LineSensor lineSensor) {

    int state;

    state = getCurrentState(lineSensor);

    return angleFromState(state);
}


int steering::getCurrentState(LineSensor lineSensor) {

    int index;
    int leftMost;
    int amount = 0;
    int state;
    int size = lineSensor.howManyPins();
    int* array = new int[size];
    lineSensor.getCurrent(array);

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
    }amount = 0;

    for (int i = 0; i < size; ++i) {
        if (array[i]) {
          ++amount;
        }
      }
    delete [] array;

    switch(amount) {
        case 0:
            if (getLastState() > 0) {
                state = 10;
            } else {
                state = -10;
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
    static int pathCounter = -1;

    if (-8 < state && state < 8) {
        if (state < 0) {
            angle = -toDegrees(SENSOR_DISTANCES[-state], NOSE_LENGTH);
        } else {
            angle = toDegrees(SENSOR_DISTANCES[state], NOSE_LENGTH);
        }

    } else if (state == -10 || state == 10) {
        for (int i = 1; i < 5; ++i) {
            if (getLastState(i) == 10 || getLastState(i) == -10) {
              Serial.println(pathCounter);
                return PATH_ANGLE[PATH_TURNS[pathCounter % PATH_LENGTH]];
            }          
        }
        return PATH_ANGLE[PATH_TURNS[++pathCounter % PATH_LENGTH]];
    } else {
        return state * 2;      
    }    

    return angle;
}

int steering::getLastState(int n) {
    return lastStates[(statesCounter+9-n) % 10];
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
    statesCounter = (statesCounter + 1) % 10;

    return;
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

    return;
}

double steering::ratio(int angle) {
    return angle / -75.0 + 1.0;
}
