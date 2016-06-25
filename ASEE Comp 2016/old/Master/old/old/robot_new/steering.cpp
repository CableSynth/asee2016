#include "constants.h"
#include "steering.h"
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

void steering::steer(LineSensor lineSensor, Servo motor) {
    
    int angle = getAngle(lineSensor);

    moveServo(angle, motor);

    return;
}


int steering::getAngle(LineSensor lineSensor) {

    //get line sensor data
    static int pathCounter = 0;
    static int lastCase = 1;
    int size = lineSensor.howManyPins();
    int* data = new int [size];
    lineSensor.getCurrent(data);
    int state = -1;

    int amountSeen = 0;
    for (int i = 0; i < size; ++i) {
        if (data[i]) {
            ++amountSeen;
            if (state == -1) {
                state = i;
            }
        }
    }

    int angle;

    switch (amountSeen) {
        case 0:
            lastCase = 0;
            break;
        case 1:
        case 2:
            angle = toDegrees(SENSOR_DISTANCES[state], NOSE_LENGTH);
            lastCase = 1;
            break;
        default:
            if (lastCase == 3) {
                angle = PATH_ANGLE[PATH_TURNS[pathCounter]];
            } else {
                angle = PATH_ANGLE[PATH_TURNS[pathCounter = (pathCounter+1)%PATH_LENGTH]];
            }
            break;
    }



    return angle;
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
