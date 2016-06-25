#include "constants.h"
#include "steering.h"
#include "LineSensor.h"
#include <Arduino.h>
#include <Servo.h>

//Serial:  USB
//Serial1: bluetooth
#define prt Serial3
//#define DEBUG
extern Servo steeringMotor;
extern Servo ringServo;
extern int driveSpeed;
extern int pathCounter;
extern bool isDropping;
extern State currentState;

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
    
    return true;
}


int steering::getAngle(LineSensor lineSensor, int motorAngle, int speed) {
    static int lastCase = 1;
    static long lastTime = 0L;
    static int lastIndex = 7;
    //static State currentState = WALL_FOLLOW_R;//LINE_FOLLOW;//WALL_FOLLOW_R;
    static State lastState = LINE_FOLLOW;
   // static State lastRingState = NULL;    
    static int lastAngle = 0;
    int size = lineSensor.howManyPins();
    int* data = new int [size];
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
    
    /*switch(pathCounter%4) {
        case 0:
            digitalWrite(LEDR, LOW);
            digitalWrite(LEDG, LOW);
            break;
        case 1:
            digitalWrite(LEDR, HIGH);
            digitalWrite(LEDG, LOW);
            break;
        case 2:
            digitalWrite(LEDR, LOW);
            digitalWrite(LEDG, HIGH);
            break;
        case 3:
            digitalWrite(LEDR, HIGH);
            digitalWrite(LEDG, HIGH);
            break;
    }*/
    
    switch (currentState) {
        case WALL_FOLLOW_R:
            if(!isDropping) {
                driveSpeed = SPEED;
            }
            wallDist = analogRead(WALL_SENSOR_LS);
            if (wallDist > DIST_START_TURN) {
                currentState = LEFT_TURN1;
            } else if (pathCounter == 8 && analogRead(WALL_SENSOR_R) < 200) {
                currentState = WALL_FOLLOW_L;
                ++pathCounter;
            }/*else if (analogRead(WALL_SENSOR_R) < 75 && pathCounter == 5) {
                
               // drive(steeringMotor.read() - STEERING_CENTER, 0);
              
                currentState = EDGE_AREA;
                ++pathCounter;
            }*/
            break;
            
        case WALL_FOLLOW_L:
            wallDist = analogRead(WALL_SENSOR_RS);
            if (wallDist > DIST_START_TURN) {
                currentState = RIGHT_TURN1;
                //only got here is L was < 100
            } else if (pathCounter == 3 && analogRead(WALL_SENSOR_L) < 75) {
                
               // drive(steeringMotor.read() - STEERING_CENTER, 0);
                dropRing();
                //set motor direction to reverse
                digitalWrite(WHEEL_DIR_BL_F, LOW);
                digitalWrite(WHEEL_DIR_BL_B, HIGH);
                digitalWrite(WHEEL_DIR_BR_F, LOW);
                digitalWrite(WHEEL_DIR_BR_B, HIGH);
                stopRing();
                drive(0, 100);
                
                setServo(STEERING_CENTER - 10, steeringMotor);
                stopRing();
                long t = millis();
                while(millis() - t < 250) {
                    stopRing();
                }
                
                setServo(STEERING_CENTER, steeringMotor);
                
                while(data[7] == 0) {
                    stopRing();
                    lineSensor.getCurrent(data);
                }
                
                //set motor direction to forward
                digitalWrite(WHEEL_DIR_BL_F, HIGH);
                digitalWrite(WHEEL_DIR_BL_B, LOW);
                digitalWrite(WHEEL_DIR_BR_F, HIGH);
                digitalWrite(WHEEL_DIR_BR_B, LOW);
                currentState = LINE_FOLLOW;
                ++pathCounter;
                
            } if (pathCounter == 10 && analogRead(WALL_SENSOR_L) < 100) {
                setServo(0, steeringMotor);
                digitalWrite(WHEEL_DIR_BR_F, LOW);
                digitalWrite(WHEEL_DIR_BR_B, HIGH);
                drive(steeringMotor.read() - STEERING_CENTER, driveSpeed);
                while(analogRead(WALL_SENSOR_L) < 200);
                while(analogRead(WALL_SENSOR_L) > 210);
                digitalWrite(WHEEL_DIR_BR_F, HIGH);
                digitalWrite(WHEEL_DIR_BR_B, LOW);
                ringServo.write(0);
                
                while(data[0] == 0) {
                    lineSensor.getCurrent(data);
                }
                delay(150);
                digitalWrite(WHEEL_DIR_BR_F, HIGH);
                digitalWrite(WHEEL_DIR_BR_B, LOW);
                setServo(STEERING_CENTER - 5, steeringMotor);
                drive(steeringMotor.read() - STEERING_CENTER, driveSpeed);
                while(analogRead(WALL_SENSOR_LS) < 800);
                delay(400);
                STOPIT();
            }
            break;
            
        case MIDDLE_AREA1:
            if (data[7] == 1) {
                currentState = MIDDLE_AREA2;
            }
            break;
            
        case MIDDLE_AREA2:
            wallDist = analogRead(WALL_SENSOR_RS);
            if (wallDist > DIST_HARD_TURN) {
                currentState = RIGHT_TURN2;
            }
            break;
            
        case EDGE_AREA:
            //STOPIT();
            if (data[7] == 1) {
                currentState = WALL_FOLLOW_R;
                ++pathCounter;
            }
            break;
 
        
        case LINE_FOLLOW:
            if (pathCounter == 4 && amountSeen > 2) {
                currentState = WALL_FOLLOW_R;
                delay(250);
                ++pathCounter;
            }
            
            /*if (amountSeen > 2) {
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
            }*/
            break;

        case LEFT_TURN1:
            wallDist = analogRead(WALL_SENSOR_LS);
            if (wallDist > DIST_HARD_TURN) {
                currentState = LEFT_TURN2;
            }
            break;

        case LEFT_TURN2:
              wallDist = analogRead(WALL_SENSOR_R);
              if (wallDist < DIST_END_TURN) {
                  if (pathCounter == 2) {
                      currentState = MIDDLE_AREA1;
                  } else if (pathCounter == 5) {
                      currentState = EDGE_AREA;
                      ++pathCounter;
                      driveSpeed = SPEED;
                  } else {
                      currentState = WALL_FOLLOW_R; 
                      if (pathCounter == 4) {
                          currentState = LINE_FOLLOW;
                      }
                      ++pathCounter;
                      //driveSpeed = SPEED;
                  }
              }
            break;

        case RIGHT_TURN1:
            wallDist = analogRead(WALL_SENSOR_RS);
            if (wallDist > DIST_HARD_TURN) {
                currentState = RIGHT_TURN2;
            }
            break;

        case RIGHT_TURN2:
              wallDist = analogRead(WALL_SENSOR_L);
              //************************************************************** COMPLETELY SKIPPING STATE ************************
              if (wallDist < 150 && analogRead(WALL_SENSOR_RS) < DIST_HARD_TURN-100) {
              // drive(steeringMotor.read() - STEERING_CENTER, 0);
              //   while(true);
                  currentState = WALL_FOLLOW_L;
                  ++pathCounter;
                  if(pathCounter != 2) {
                      driveSpeed = SPEED;
                  }
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
        case WALL_FOLLOW_R:
            wallDist = analogRead(WALL_SENSOR_R);

//            if (wallDist > 900) {
//                angle = 135;
//            } else if (wallDist < 150) {
//                angle = 60;
//            } else {
                angle = STEERING_CENTER - (WALL_DIST - wallDist)/40;
            //}
            break;
            
        case WALL_FOLLOW_L:
            wallDist = analogRead(WALL_SENSOR_L);

//            if (wallDist > 900) {
//                angle = 45;
//            } else if (wallDist < 100) {
//                angle = 135;
//            } else {
                angle = STEERING_CENTER + (WALL_DIST - wallDist)/40;
                if (pathCounter == 9 && analogRead(WALL_SENSOR_L) < 500) {
                    angle = STEERING_CENTER + 45;
                } else if(pathCounter == 9) {
                    ++pathCounter;
                }
            //}
            break;
            
        case MIDDLE_AREA1:
            angle = 135;
            break;
            
        case MIDDLE_AREA2:
            angle = STEERING_CENTER;
            break;
        
        case LINE_FOLLOW:
            if (index == -1) {
                angle = lastAngle;
            }else {
                angle = index * 2;
    
                if (amountSeen == 2) {
                    ++angle;
                }
                
                angle = STEERING_CENTER - SENSOR_ANGLES[angle];
                lastAngle = angle;
            }
            #ifdef DEBUG
            prt.println('F');
            #endif
            break;
        
        case LEFT_TURN1:
            driveSpeed = TURN_SPEED;
            angle = STEERING_CENTER + 15;
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
            driveSpeed = TURN_SPEED;
            angle = STEERING_CENTER - 15;
            #ifdef DEBUG
            prt.println('R');
            #endif
            break;
        case RIGHT_TURN2:
            angle = -180;
            #ifdef DEBUG
            prt.println('R');
            #endif
            break;
        
        case EDGE_AREA:
            angle = STEERING_CENTER + 15;
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
    
    
    
    
    //    stopRing();

    
    
    
    
    
    
    

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

void steering::dropRings() {
    static bool hasDropped[] = {false, false, false, false, false, false, false, false, false, false, false};
    static State lastState = OFF_WALL;
    static State ringState = OFF_WALL;
    static int lastPath = 0;
    static int ringCounter = 0;
    static bool done012 = false;
    static bool seeWall = false;
    
    static bool isDropped = false;
    int ringSense = analogRead(GARAGE_SENSOR);
    #ifdef DEBUG
    prt.print("RS: ");
    prt.print(ringSense);
    prt.print("  ");
    #endif


//    if (ringSense < 20) {
//        ringState = OFF_TRACK;
//    } else if (ringSense < 50) {
//        ringState = ON_TRACK;
//    } else {
//        ringState = ON_WALL;
//    }
    
    
    
    if(ringSense < 75) {
        ringState = OFF_WALL;
    } else {
        ringState = ON_WALL;
    }
//    else{
//        switch(ringState){
//            case OFF_TRACK:
//                digitalWrite(LEDR, LOW);
//                digitalWrite(LEDG, LOW);
//                if( ringSense > 50) {
//                    ringState = ON_WALL;
//                }
//                break;
//            case ON_WALL:
//                digitalWrite(LEDR, LOW);
//                digitalWrite(LEDG, HIGH);
//                if (ringSense < 50) {
//                    ringState = ON_TRACK;
//                }
//                break;
//            case ON_TRACK:
//                digitalWrite(LEDR, HIGH);
//                digitalWrite(LEDG, LOW);
//                if (ringSense > 50) {
//                    ringState = ON_WALL;
//                } 
//                break;
//        }
//    }
    
    
    
    
    
    switch(pathCounter) {
        case 0:
        case 1:
        case 2:
            if (!hasDropped[pathCounter] && ringState == ON_WALL && lastState == ON_WALL && !isDropping) {
                dropRing();
                hasDropped[pathCounter] = true;
            }
            
            if(currentState == MIDDLE_AREA2) {
                done012 = true;
                ringServo.write(145); //prep to drop before reverse
            }
            break;
        case 3:
            break;
        case 4:
            ringServo.write(30);
            break;
        case 5:
            ringServo.write(0);
            if(!hasDropped[pathCounter] && ringState == ON_WALL && currentState != LINE_FOLLOW) {
                dropRing();
                hasDropped[pathCounter] = true;
            }
            break;
        case 6:
            break;
        case 7:
            if(!hasDropped[pathCounter] && ringState == ON_WALL && lastState == ON_WALL) {
                dropRing();
                hasDropped[pathCounter] = true;
            }
            break;
        case 8:
            break;
        case 9:
        case 10:
            if(!hasDropped[pathCounter] && ringState == ON_WALL && lastState == ON_WALL) {
                dropRing();
                hasDropped[pathCounter] = true;
            }
            ringServo.write(170);
            break;
      
      
    }
    
    lastState = ringState;
    lastPath = pathCounter;
  
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

void steering::STOPIT() {
  drive(steeringMotor.read() - STEERING_CENTER, 0);
  while(true);
}

double steering::ratio(int angle) {
    return angle / -60.0 + 1.0;
}

void steering::dropRing() {
        analogWrite(WHEEL_PWM_FR,255);
        isDropping = true;
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
        isDropping = false;
        return;
    }
}
