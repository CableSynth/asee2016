#include "constants.h"
#include "steering.h"
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

void steering::steer(LineSensor lineSensor, Servo motor, int speed) {
    
    int angle = getAngle(lineSensor) / REDUCE;
    moveServo(angle, motor);
    return;
}


int steering::getAngle(LineSensor lineSensor) {

    static int pathCounter = 0;
    static int lastCase = 1;
    static int lastIndex = 1;
    static long lastTime = 0;
    static long lastLF = 0;
    static State currentState = LINE_FOLLOW;
    static State lastState = LINE_FOLLOW;
    static int lastAngle = 0;
    int size = lineSensor.howManyPins();
    
    int* data = new int [size];
    lineSensor.update();
    lineSensor.getCurrent(data);
    
    int index = -1;

    int amountSeen = 0;
    for (int i = 0; i < size; ++i) {
      Serial.print(data[i]);
        if (data[i]) {
            ++amountSeen;
            if (index == -1) {
                index = i;
            }
        }
    }
    Serial.println(' ');
    int angle;
    
    
    switch (currentState) {
        case LINE_FOLLOW:
            if (amountSeen > 2 && millis() - lastLF > 500) {
                switch (PATH_TURNS[pathCounter]) {
                    case 0:
                        lastState = currentState;
                        currentState = LEFT_TURN1;
                    break;
                    case 1:
                        lastState = currentState;
                        currentState = IGNORE_TURN;
                    break;
                    case 2:
                        lastState = currentState;
                        currentState = RIGHT_TURN1;
                    break;
                }                
                pathCounter =  (pathCounter + 1) % PATH_LENGTH;
            }
            break;

        case LEFT_TURN1:
            if (data[1] == 0) {
                lastState = currentState;
                currentState = LEFT_TURN2;
            }
            break;

        case LEFT_TURN2:
            if (data[1] == 1) {
                lastState = currentState;
                currentState = LINE_FOLLOW;
                lastLF = millis();
            }
            break;

        case RIGHT_TURN1:
            if (data[6] == 0) {
                lastState = currentState;
                currentState = RIGHT_TURN2;
            }
            break;

        case RIGHT_TURN2:
            if (data[6] == 1) {
                lastState = currentState;
                currentState = LINE_FOLLOW;
                lastLF = millis();
            }
            break;

        case IGNORE_TURN:
            if (amountSeen < 3) {
                lastState = currentState;
                currentState = LINE_FOLLOW;
                lastLF = millis();
            }
            break;
    }
    

    switch (currentState) {
        case LINE_FOLLOW:
            if (index == -1) {
                angle = lastAngle;
            }else if ( millis() - lastTime > 50) {
                angle = index * 2;
    
                if (amountSeen == 2) {
                    ++angle;
                } else if (amountSeen == 0) {
                    angle = lastAngle;
                }
                angle = SENSOR_ANGLES[angle];
                lastTime = millis();
                lastAngle = angle;
            }
            //digitalWrite(13, LOW);
            Serial.print("F    ");
            Serial.println(pathCounter);
            break;
        case LEFT_TURN1:
        case LEFT_TURN2:
            angle = -180 * REDUCE;
            //digitalWrite(13, HIGH);
            Serial.print("L    ");
            Serial.println(pathCounter);
            break;
        case RIGHT_TURN1:
        case RIGHT_TURN2:
            angle = 180 * REDUCE;
            Serial.print("R    ");
            Serial.println(pathCounter);
            break;
        case IGNORE_TURN:
            angle = 0;
            Serial.print("I    ");
            Serial.println(pathCounter);
            break;
    }


    delete [] data;
    data = NULL;
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

void steering::drive(int angle, int speed) {
    int left;
    int right;
    if (angle > 0) {
        right = speed / ratio(angle);
        left  = speed;
    } else {
        right = speed;
        left  = speed / ratio(-angle);
    }

    analogWrite(PWMR, right);
    analogWrite(PWML, left);

    return;
}

double steering::ratio(int angle) {
    return angle / 50.0 + 1.0;
}
