#include "constants.h"
#include "steering.h"
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

void steering::steer(LineSensor lineSensor, Servo motor, int speed) {
    
    int angle = getAngle(lineSensor);

    moveServo(angle*sqrt(speed/20.0), motor);

    return;
}


int steering::getAngle(LineSensor lineSensor) {

    static int pathCounter = 0;
    static int lastCase = 1;
    static int lastState = 1;
    static long lastTime = 0;
    int size = lineSensor.howManyPins();
    int* data = new int [size];
    lineSensor.update();
    lineSensor.getCurrent(data);
    int state = -1;

    int amountSeen = 0;
    for (int i = 0; i < size; ++i) {
        Serial.print(data[i]);
        if (data[i]) {
            ++amountSeen;
            if (state == -1) {
                state = i;
            }
        }
    }
    Serial.println('.');
    Serial.println(amountSeen);
    delete [] data;
    data = NULL;
    
    int angle;

    switch (amountSeen) {
        case 0:
            if (lastState + (amountSeen/2) < 5) {
                angle = PATH_ANGLE[0];
            } else {
                angle = PATH_ANGLE[2];
            }
            lastCase = 0;
            break;
        case 1:
        case 2:
            if (millis() - lastTime > 50 ) {
                if (lastCase == 3 || lastCase == 0) {
                    ++pathCounter;
                    pathCounter %= PATH_LENGTH;
                }
                angle = toDegrees(SENSOR_DISTANCES[state], NOSE_LENGTH);
                lastCase = 1;
                lastState = state;
                lastTime = millis();
            }
            break;
        default:
            int turn = PATH_TURNS[pathCounter];

            switch (turn){
                case 0:
                    if (state == 0) {
                        angle = PATH_ANGLE[turn];
                    } else {
                        angle = PATH_ANGLE[1];
                    }
                    break;
                case 1:
                    angle = PATH_ANGLE[turn];
                    break;
                case 2:
                    if (state + amountSeen == 8) {
                          angle = PATH_ANGLE[turn];
                    } else {
                          angle = PATH_ANGLE[1];
                    }
                    break;
            }
            lastCase = 3;
            lastState = state;
            break;
    }

    Serial.println(angle);

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
