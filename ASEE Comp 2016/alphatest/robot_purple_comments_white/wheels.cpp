#include "constants.h"
#include "nose.h"
#include "wheels.h"
#include <Arduino.h>
#include <Servo.h>

//Serial:  USB
//Serial1: bluetooth
#define prt Serial3
//#define DEBUG



// drives wheels with differential based on angle
void wheels::drive(int angle, int speed) {
    int left;
    int right;
    
    if (angle > 0) {
        right  = speed;
        left   = speed * ratio(angle);
    } else {
        left   = speed;
        right  = speed/ratio(angle);
    }

    driveWheels(left, right);

    return;
}


// drives wheels forwards and backwards; > 0 is forwards
void wheels::driveWheels(int left, int right) {

    if (left > 0) {
        // drive left motor forward
        digitalWrite(WHEEL_DIR_BL_F, HIGH);
        digitalWrite(WHEEL_DIR_BL_B, LOW);

    } else if (left < 0) {
        // drive left motor backwards
        digitalWrite(WHEEL_DIR_BL_F, LOW);
        digitalWrite(WHEEL_DIR_BL_B, HIGH);
        left = -left;

    } else {
        // stop left motor
        digitalWrite(WHEEL_DIR_BL_F, LOW);
        digitalWrite(WHEEL_DIR_BL_B, LOW);
    }


    if (right > 0) {
        // drive right motor forward
        digitalWrite(WHEEL_DIR_BR_F, HIGH);
        digitalWrite(WHEEL_DIR_BR_B, LOW);

    } else if (right < 0) {
        // drive right motor backwards
        digitalWrite(WHEEL_DIR_BR_F, LOW);
        digitalWrite(WHEEL_DIR_BR_B, HIGH);
        right = -right;

    } else {
        // stop right motor
        digitalWrite(WHEEL_DIR_BR_F, LOW);
        digitalWrite(WHEEL_DIR_BR_B, LOW);
    }

    // cap pwm at 255
    if (left > 255)  { left  = 255; }
    if (right > 255) { right = 255; }
    
    //send pwm to motors
    analogWrite(PWMR, right);
    analogWrite(PWML, left);
}

double wheels::ratio(int angle) {
    return angle / -60.0 + 1.0;
}

void wheels::STOPIT() {
    driveWheels(0, 0);
    while(true);
}
