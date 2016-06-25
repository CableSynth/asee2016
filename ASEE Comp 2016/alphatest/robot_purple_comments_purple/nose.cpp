#include "constants.h"
#include "nose.h"
#include "wheels.h"
#include "rings.h"
#include <Arduino.h>
#include <Servo.h>

using namespace rings;
using namespace wheels;

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

extern bool* lineData; 

// wall sensors; the bigger the number, the closer the wall
extern int wall_L;
extern int wall_LS;
extern int wall_RS;
extern int wall_R;
extern int wall_Far;
extern int snorkle;

void nose::steer() {
    //_CHANGE unneeded variable
    setNose(getAngle());
}


int nose::getAngle() {
    static int lastAngle = 0;
    int angle = 0;      // value that will be returned
    
    int index = -1;     // first sensor from the left that sees the line
    int amountSeen = 0; // amount of sensors that see the line

    // loop through line sensors looking for line
    for (int i = 0; i < 8; ++i) {
        if (lineData[i]) {
            ++amountSeen;
            if (index == -1) {
                index = i;
            }
        }
    }
    
    /*** CONTROLS CURRENT STATE ***/
    switch (currentState) {

        // follow the right wall
        case WALL_FOLLOW_R:
            
            if (!isDropping) {
                driveSpeed = SPEED;
            }
            
            if (wall_LS > DIST_START_TURN) {
                // approaching box; start small turn
                currentState = LEFT_TURN1;
            
            //if you're at the end of the run near the parking zone
            } else if (pathCounter == 7 && wall_RS < 100 && wall_R < 100) {
              //STOPIT();
                currentState = EDGE_AREA;
            } else if (pathCounter == 8 && wall_R < 200 && !isDropping) {
                // we dropped second to last ring; find inner wall
                currentState = WALL_FOLLOW_L;
                ++pathCounter;
            }
            break;
            
        // follow the left wall
        case WALL_FOLLOW_L:
            
            if (!isDropping) {
                driveSpeed = SPEED;
            }//_CHANGE
            
            if (wall_RS > DIST_START_TURN) {// && pathCounter != 9) {
                // approaching box; start small turn
                currentState = RIGHT_TURN1;
                
            //end of the game by the parking zone
            } else if (pathCounter == 7 && wall_LS < 300 && wall_L < 100) {
                currentState = EDGE_AREA;
            } else if (pathCounter == 9){
                setNose(NOSE_CENTER -15);
                delay(750);
                currentState = LINE_FOLLOW;
            }
            
            /*else if (pathCounter == 3  && wall_L < 75) {
                // we lost the wall in the middle section; drive in reverse
                dropRing();
                
                // back up with slight right turn
                driveWheels(-100, -100);
                setNose(NOSE_CENTER - 10);
                
                // have a slight turn for a quarter second
                long t = millis();
                while(millis() - t < 250) { stopRing(); }
                
                // now back up straight until the far right sensor sees the line
                setNose(NOSE_CENTER);
                while(digitalRead(LINE_SENSOR_7) == 0) { stopRing(); }
                
                // follow the line once we see it
                currentState = LINE_FOLLOW;
                ++pathCounter;
                
            } else if (pathCounter == 9) {
                ringServo.write(150);
                if (wall_L > 300) {
                   ++pathCounter;
                }
            } else if (pathCounter == 10 && wall_L < 75) {
                dropRing();
                
                // back up with slight right turn
                driveWheels(-100, -100);
                setNose(NOSE_CENTER - 10);
                
                // have a slight turn for a quarter second
                long t = millis();
                while(millis() - t < 250) { stopRing(); }
                
                // now back up straight until the far right sensor sees the line
                setNose(NOSE_CENTER);
                while(isDropping) { stopRing(); }
                
                // drive right wheel backwards to turn sharper
                setNose(NOSE_RIGHT_MAX);
                ringServo.write(0);
                drive(steeringMotor.read() - NOSE_CENTER, driveSpeed);

                // turn until we see the line
                while(!digitalRead(LINE_SENSOR_0));
                delay(600);
                setNose(NOSE_CENTER);
                
                // turn less sharp so we find the line
                drive(steeringMotor.read() - NOSE_CENTER, driveSpeed);
                
                // drive into the finish
                setNose(NOSE_CENTER - 5);
                drive(steeringMotor.read() - NOSE_CENTER, driveSpeed);
                
                // drive a little longer once we see the back wall
                while(analogRead(WALL_SENSOR_LS) < 800);
                delay(400);
                STOPIT();
            }*/
            break;
        
        //Where we think the problem is    
        // find inner wall after delivering 3rd ring (part 1)
        case MIDDLE_AREA1:
            // move to next step once we find the line
            if (lineData[7]) {//_CHANGE used to be 0
                currentState = MIDDLE_AREA2;
            }
            break;
            
        // find inner wall after delivering 3rd ring (part 2)
        case MIDDLE_AREA2:
            // turn right once we find the inner wall
            if (amountSeen == 0) {
                currentState = LEFT_TURN2;
                
                ++pathCounter;
                //pathCounter = 4
            }
            break;
 
        // line following after reversing in middle section
        case LINE_FOLLOW:
            if (pathCounter == 5 && amountSeen > 2) {
                currentState = WALL_FOLLOW_L;
                
                setNose(NOSE_CENTER + 20);
                while(analogRead(WALL_SENSOR_L) < 400);
                setNose(NOSE_CENTER + 10);
                while(analogRead(WALL_SENSOR_L) < 600);
                
                ++pathCounter;
                //pathCounter = 6
            } else if(pathCounter == 9 && amountSeen == 0){
              //If line has been seen the line follow otherwise don't
              setNose(NOSE_CENTER - 8);
              //while(digitalRead(LINE_SENSOR_5) == 0) {  stopRing(); }
                //STOPIT();
            } else if (pathCounter == 9) {
                //last thing we run; stop in finish box
                digitalWrite(A8, HIGH);
                int SENSOR_ANGLE[15] = {-15, -15, -10, -10, -5, -3, 0, 0, 0, 3, 5, 10, 10, 15, 15};
                
                while (wall_LS < 300 && wall_RS < 300) {
                    updateSensors();
                    stopRing();
                    
                    amountSeen = 0;
                    index = -1;
                    for (int i = 0; i < 8; ++i) {
                        if (lineData[i]) {
                            ++amountSeen;
                            if (index == -1) {
                                index = i;
                            }
                        }
                    }
                    
                    if (index == -1) {
                        //we dont see the line
                        setNose(NOSE_CENTER - 20);
        
                    }else {
                        // we see the line
                        angle = index * 2;
                        if (amountSeen == 2) {
                            ++angle;
                        }
                        
                        // set angle based on array
                        angle = NOSE_CENTER - SENSOR_ANGLE[angle];
                        setNose(angle);
                        lastAngle = angle;
                    }
                }
                
                setNose(NOSE_LEFT_MAX);
                drive(steeringMotor.read() - NOSE_CENTER, driveSpeed);
                stopRing();
                
                delay(500);
                
                drive(steeringMotor.read() - NOSE_CENTER, driveSpeed);
                
                while(analogRead(WALL_SENSOR_LS) < 800);
                delay(400);
                
                
                ringServo.write(180);
                STOPIT();
                
                
            }
            break;
            
        // navigate past gap in wall after delivering 5th ring
        case EDGE_AREA:
            // turn slight left until we hit the line, then wall follow
            if (lineData[0]) {
                currentState = WALL_FOLLOW_L;
                delay(100);
                ++pathCounter;
                //pathcounter = 8
            }
            break;

        // initial small turn
        case LEFT_TURN1:
            // turn hard once we get close to the wall
            if (wall_LS > DIST_HARD_TURN) {
                currentState = LEFT_TURN2;
            }
            break;

        // hard turn
        case LEFT_TURN2:
            if (pathCounter == 4 && lineData[7]) {
                currentState = LINE_FOLLOW;
                ++pathCounter;
                //pathCounter = 5
            } 
            
//            else if (wall_R < DIST_END_TURN) {
//                // go back to wall follow after far enough away from wall
//
//                if (pathCounter == 2) {
//                    // find inner wall if just dropped 3rd ring
//                    currentState = MIDDLE_AREA1;
//
//                } 
                
//                else if (pathCounter == 5) {
//                    // navigate past gap in wall after 5th ring
//                    currentState = WALL_FOLLOW_R;
//                    ++pathCounter;
//                }
//                
//                else {
//                    // go back to following right wall
//                    currentState = WALL_FOLLOW_R;
//                    ++pathCounter;
//                }
//            }
            
            break;

        // initial small turn
        case RIGHT_TURN1:
            // turn hard once we get close to the wall
            if (wall_RS > DIST_HARD_TURN || wall_LS > 900) {
                currentState = RIGHT_TURN2;
            }
            break;

        // hard turn
        case RIGHT_TURN2:
            // only called after finding inner wall (i believe?)
            if (wall_L < 150 && wall_RS < DIST_HARD_TURN-100) {  //
              
                if (pathCounter == 2) {//about to deliver the third box
                    currentState = MIDDLE_AREA1;
                } else {
                    currentState = WALL_FOLLOW_L;
                    driveSpeed = SPEED;
                }
//                if (pathCounter == 0) {
//                    driveWheels(255, 255);
//                    while(!isDropping) { stopRing(); }
//                    
//                    // go fast for long straightaway
//                    setNose(NOSE_CENTER + 1);
//                    delay(2000);
//                }
                ++pathCounter;
            }
            break;
    }


    stopRing();


    /*** CONTROLS OUTPUT ***/
    switch (currentState) {

        // follow the righ wall
        case WALL_FOLLOW_R:
            angle = NOSE_CENTER - (WALL_DIST - wall_R)/40;
            if (pathCounter == 8 && wall_R < 100) {
                angle = NOSE_CENTER;
            }
            break;
            
        // follow the left wall
        case WALL_FOLLOW_L:
                angle = NOSE_CENTER + (WALL_DIST - wall_L)/30;

                // if we are looking for the inner wall to drop last ring
//                if (pathCounter == 9 && wall_L < 500) {
//                    // before finding wall
//                    angle = NOSE_CENTER + 45;
//                } else if(pathCounter == 9) {
//                    //once we find the wall; goes back to normal wall follow
//                    ++pathCounter;
//                }

            break;
            
        // transition to middle section after dropping 3rd ring
        // before seeing the line
        case MIDDLE_AREA1:
            angle = NOSE_CENTER - 40;
            break;
        //after seeing the line
        case MIDDLE_AREA2:
            angle = NOSE_CENTER;
            break;
        
        // line follow in the middle after reversing
        case LINE_FOLLOW:
            if (index == -1) {
                //we dont see the line
                angle = lastAngle;

            }else {
                // we see the line
                angle = index * 2;
                if (amountSeen == 2) {
                    ++angle;
                }
                
                // set angle based on array
                angle = NOSE_CENTER - SENSOR_ANGLES[angle];
                lastAngle = angle;
            }
            break;
        
        // initial small left turn
        case LEFT_TURN1:
            driveSpeed = TURN_SPEED;
            angle = NOSE_CENTER + 15;
            break;

        // hard left turn
        case LEFT_TURN2:
            angle = 180;
            break;
            
        // initial small right turn
        case RIGHT_TURN1:
            driveSpeed = TURN_SPEED;
            angle = NOSE_CENTER - 25;
            break;

        // hard right turn
        case RIGHT_TURN2:
            angle = 0;
            break;
        
        // turn left after dropping 5th ring to line follow
        case EDGE_AREA:
            angle = NOSE_CENTER - 15;
            break;    
    }

    stopRing();
    return angle;
}


// sets the nose to a vertain angle
// > 90 left turn
// < 90 righ turn
void nose::setNose (int angle) {
    // make sure angle is within valid range
    if (angle < NOSE_RIGHT_MAX) {
        angle = NOSE_RIGHT_MAX;
    } else if (angle > NOSE_LEFT_MAX) {
        angle = NOSE_LEFT_MAX;
    }   

    steeringMotor.write(angle);
    return;
}


// update line and wall sensor variables
void nose::updateSensors() {

    for (int i = 0; i < 8; ++i) {
        lineData[i] = digitalRead(LINE_SENSOR[i]) == 1;
    }


    wall_L   = analogRead(WALL_SENSOR_L);
    wall_LS  = analogRead(WALL_SENSOR_LS);
    wall_RS  = analogRead(WALL_SENSOR_RS);
    wall_R   = analogRead(WALL_SENSOR_R);
    wall_Far = analogRead(WALL_SENSOR_FAR);
    snorkle  = analogRead(GARAGE_SENSOR);

}
