#include "constants.h"
#include "steering.h"
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

#define prt Serial1

void steering::steer(LineSensor lineSensor, Servo motor, int speed) {
    int treebeard = getAngle(lineSensor, motor.read(), speed);
    moveServo(treebeard, motor);
    //setServo(STEERING_CENTER - treebeard, motor);
    
    /*string cheese
    double dutch
    char lizard
    float rootbeer
    long way_to_go
    byte me!
    short people
    name cecil
    enter the void

    ;oscapy*/
    
    return;
}


int steering::getAngle(LineSensor lineSensor, int motorAngle, int speed) {
    static int pathCounter = 0;
    static int lastCase = 1;
    static long lastTime = 0L;
    static int lastIndex = 7;
    static State currentState = LINE_FOLLOW;
    static State lastState = LINE_FOLLOW;
    static int lastAngle = 0;
    int size = lineSensor.howManyPins();
    int* data = new int [size];
    lineSensor.update();
    lineSensor.getCurrent(data);
    int index = -1;
    int offCenter;
    static long timer;
    static int dist = 0;

    int amountSeen = 0;
    for (int i = 0; i < size; ++i) {
        prt.print(data[i]);
        if (data[i] == 1) {
            ++amountSeen;
            if (index == -1) {
                index = i;
            }
        }
    }
    prt.print('\n');
    int angle = 0;
    
    
    switch (currentState) {
        case LINE_FOLLOW:
            if (amountSeen > 2) {
                switch (PATH_TURNS[pathCounter]) {
                    case 0:
                        lastState = currentState;
                        currentState = LEFT_TURN1;
                        ++pathCounter;
                    break;
                    case 1:
                        offCenter = motorAngle - STEERING_CENTER;
                        if ( offCenter < 20 && offCenter > -20) {
                            lastState = currentState;
                            currentState = IGNORE_TURN;
                            ++pathCounter;
                        }
                    break;
                    case 2:
                        lastState = currentState;
                        currentState = RIGHT_TURN1;
                        ++pathCounter;
                    break;
                    case -1:
                        lastState = currentState;
                        currentState = LAND_PLANE;
                        ++pathCounter;
                    break;
                }
            }
            else if(PATH_LENGTH == pathCounter){
                lastState = currentState;
                currentState = LAND_PLANE;
                ++pathCounter;
                timer = millis();
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
            }
            break;

        case IGNORE_TURN:
            if (amountSeen < 3) {
                lastState = currentState;
                currentState = LINE_FOLLOW;
            }
            break;  
    }
    
    
    switch (currentState) {
        case LINE_FOLLOW:
            if (index == -1) {
                angle = lastAngle;
            }else if ( millis() - lastTime > 5) {
                /*for (int i = 0; i < size; ++i) {
                  Serial.print(data[i]);
                  Serial1.print(data[i]);
                }
                Serial.print('\n');
                Serial1.print('\n');*/
                angle = index * 2;
    
                if (amountSeen == 2) {
                    ++angle;
                }
                
                lastTime = millis();
                angle = SENSOR_ANGLES[angle];
                lastAngle = angle;
            }
            prt.println('F');
            break;
        
        case LEFT_TURN1:
            angle = 0;
            prt.println("L1");
            break;
        case LEFT_TURN2:
            angle = -180;
            prt.println("L2");
            break;
            
        case RIGHT_TURN1:
            angle = 0;
            prt.println('R');
            break;
        case RIGHT_TURN2:
            angle = 180;
            prt.println('R');
            break;
        
        case IGNORE_TURN:
            angle = 0;
            prt.println('I');
            break;
        case LAND_PLANE:
            if (timer 
            if (index == -1) {
                angle = lastAngle;
            }else if ( millis() - lastTime > 5) {
                /*for (int i = 0; i < size; ++i) {
                  Serial.print(data[i]);
                  Serial1.print(data[i]);
                }
                Serial.print('\n');
                Serial1.print('\n');*/
                angle = index * 2;
    
                if (amountSeen == 2) {
                    ++angle;
                }
                
                lastTime = millis();
                angle = SENSOR_ANGLES[angle];
                lastAngle = angle;
            }
            prt.println('F');
            break;        
    }


    delete [] data;
    data = NULL;
    //Serial.println(angle);
    //Serial1.println(angle);
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
    int rd = motor.read();
    prt.println(rd);
    
    setServo(delta + rd, motor);

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

    analogWrite(PWMR, left);
    analogWrite(PWML, right);
    //analogWrite(PWMR, right);
    //analogWrite(PWML, left);

    return;
}

double steering::ratio(int angle) {
    return angle / -60.0 + 1.0;
}
