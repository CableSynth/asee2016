#include "constants.h"
#include "steering.h"
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

//Serial:  USB
//Serial1: bluetooth
#define prt Serial3
//#define DEBUG
extern Servo ringServo;
bool steering::steer(LineSensor lineSensor, Servo motor, int speed) {
    int treebeard = getAngle(lineSensor, motor.read(), speed);
    if (treebeard == 314) {
        return false;
    } else if(treebeard == -314) {  
        setServo(STEERING_CENTER, motor);
        return true;
    }
    //prt.println(treebeard);
    setServo(treebeard, motor);
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
    
    return true;
}


int steering::getAngle(LineSensor lineSensor, int motorAngle, int speed) {
    static int pathCounter = 0;
    static int lastCase = 1;
    static long lastTime = 0L;
    static int lastIndex = 7;
    static State currentState = WALL_FOLLOW;
    static State lastState = LINE_FOLLOW;
    static State ringState = OFF_TRACK;
   // static State lastRingState = NULL;    
    static int lastAngle = 0;
    int size = lineSensor.howManyPins();
    int* data = new int [size];
    lineSensor.update();
    lineSensor.getCurrent(data);
    int index = -1;
    int offCenter;
    static long timer;
    static int dist = 0;
    static long lastTimer;
    static int wallDist;

    int amountSeen = 0;
    for (int i = 0; i < size; ++i) {
        #ifdef DEBUG
        prt.print(data[i]);
        #endif
        if (data[i] == 1) {
            ++amountSeen;
            if (index == -1) {
                index = i;
            }
        }
    }
    #ifdef DEBUG
    prt.print("  ");
    prt.print(pathCounter);
    prt.print("  ");
    #endif
    int angle = 0;
    
    
    switch (currentState) {
        case WALL_FOLLOW:
            wallDist = analogRead(WALL_SENSOR_LS);
            if (wallDist > DIST_START_TURN) {
                currentState = LEFT_TURN1;
            }
            break;
            
        case LINE_FOLLOW:
            if (amountSeen > 2) {
                if(RING_DROPS[pathCounter]){
                  dropRing();
                }
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
            else if(PATH_LENGTH-1 == pathCounter){
                lastState = currentState;
                currentState = LAND_PLANE;
                ++pathCounter;
                timer = millis();
            }
            break;

        case LEFT_TURN1:
            wallDist = analogRead(WALL_SENSOR_LS);
            if (wallDist > DIST_HARD_TURN) {
                currentState = LEFT_TURN2;
            }
//            if (data[1] == 0) {
//                lastState = currentState;
//                currentState = LEFT_TURN2;
//            }
            break;

        case LEFT_TURN2:
              wallDist = analogRead(WALL_SENSOR_R);
              if (wallDist < DIST_END_TURN) {
                  currentState = WALL_FOLLOW;
              }
        
//            if (data[1] == 1) {
//                lastState = currentState;
//                currentState = LINE_FOLLOW;
//            }
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
    stopRing();
    int ringSense = analogRead(GARAGE_SENSOR);
    #ifdef DEBUG
    prt.print("RS: ");
    prt.print(ringSense);
    prt.print("  ");
    #endif
    if(ringSense < 10){
        ringState = OFF_TRACK;
    }
    else{
        switch(ringState){
            case OFF_TRACK:
                ringServo.write(0);
                if( ringSense > 100) {
                    ringState = ON_WALL;
                }
                break;
            case ON_WALL:
                ringState = ON_TRACK;
                dropRing();
                break;
            case ON_TRACK:
                if (ringSense > 100) {
                    ringServo.write(0);
                }   
                if(ringSense > 10 && ringSense < 90) {
                    ringServo.write(30);
                } else
                break;
        }
    }
    switch (currentState) {
        case WALL_FOLLOW:
            wallDist = analogRead(WALL_SENSOR_R);
//            prt.print(wallDist);
//            prt.print(' ');
//            prt.print(WALL_DIST - wallDist);
            angle = STEERING_CENTER - (WALL_DIST - wallDist)/40;
            break;
            
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
            #ifdef DEBUG
            prt.println('F');
            #endif
            break;
        
        case LEFT_TURN1:
            angle = STEERING_CENTER + 10;
            #ifdef DEBUG
            prt.println("L1");
            #endif
            break;
        case LEFT_TURN2:
            angle = 180;
            #ifdef DEBUG
            prt.println("L2");
            #endif
            break;
            
        case RIGHT_TURN1:
            angle = 0;
            #ifdef DEBUG
            prt.println('R');
            #endif
            break;
        case RIGHT_TURN2:
            angle = 180;
            #ifdef DEBUG
            prt.println('R');
            #endif
            break;
        
        case IGNORE_TURN:
            angle = 0;
            #ifdef DEBUG
            prt.println('I');
            #endif
            break;
        case LAND_PLANE:
            #ifdef DEBUG
            prt.println('P');
            #endif
            
            dist = speed * (millis()-timer);
            if (dist < TILL_TURN) {
                #ifdef DEBUG
                prt.println("it");
                #endif
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
            } else if(dist < TILL_TURN + TURN) {
                #ifdef DEBUG
                prt.println('t');
                #endif
                angle = 180;
            } else if (dist < TILL_TURN + TURN + AFTER_TURN) {
                #ifdef DEBUG
                prt.println("at");
                #endif
                angle = -314;
            } else {
                #ifdef DEBUG
                prt.println("done");
                #endif
                angle = 314;
            }
            break;        
    }

    delete [] data;
    data = NULL;
    #ifdef DEBUG
    prt.println(angle);
    #endif
    //Serial.println(angle);
    //Serial1.println(angle);
    stopRing();
    return angle;
}


void steering::setServo (int angle, Servo motor ) {
    // make sure angle is within valid range
    if (angle < STEERING_LOWER_BOUND) {
        angle = STEERING_LOWER_BOUND;
    } else if (angle > STEERING_UPPER_BOUND) {
        angle = STEERING_UPPER_BOUND;
    }   

//    prt.print(' ');
//    prt.println(angle);
    motor.write(angle);
    return;
}


void steering::moveServo (int delta, Servo motor ) {
    int rd = motor.read();
    
    #ifdef DEBUG
    prt.println(rd);
    #endif
    
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

void steering::dropRing() {
        analogWrite(WHEEL_PWM_FR,255);
}

void steering::stopRing()  {
    static bool getInTheHole = false;
    if (digitalRead(RING_DISPENSER_R2) == 0 && !getInTheHole) {
    //    Serial.println("hey1");
        return;
    }
    
    if (digitalRead(RING_DISPENSER_R2) != 0 && !getInTheHole) {
    //    Serial.println("hey2");
        getInTheHole = true;
        return;
    } 
    
    if (digitalRead(RING_DISPENSER_R2) == 0 && getInTheHole) {
    //    Serial.println("hey3");
        getInTheHole = false;
        analogWrite(WHEEL_PWM_FR,0);
        return;
    }
}
