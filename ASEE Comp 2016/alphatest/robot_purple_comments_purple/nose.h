#ifndef NOSE_H
#define NOSE_H
#include <Arduino.h>
#include <Servo.h>

namespace nose {

    // update line and wall sensor variables
    void updateSensors();

    // steers the nose
    void steer();


    // return: angle to set nose
    int getAngle();


    // sets the servo to a certain angle in degrees
    //		limits range to UPPER and LOWER bounds
    void setNose(int angle);

}

#endif
