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
extern int stateCounter; //_NEW*/
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

extern int rt2Time;
extern int rt3Time;
extern int parkTime;



void nose::steer() {
    //_CHANGE unneeded variable
    setNose(getAngleTails());//_NEW
}

int nose::getAngleTails() {
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
    switch (stateMap[stateCounter]) {

        // follow the right wall
        /*case WALL_FOLLOW_R:
            
            if (!isDropping) {
                driveSpeed = SPEED;
            }
            
            if (wall_LS > DIST_START_TURN) {
                // approaching box; start small turn
                stateCounter++;
            
            //if you're at the end of the run near the parking zone
            } else if (pathCounter == 7 && wall_RS < 100 && wall_R < 100) {
              //STOPIT();
                stateCounter++
            } else if (pathCounter == 8 && wall_R < 200 && !isDropping) {
                // we dropped second to last ring; find inner wall
                stateCounter++;
            }
            break;*/
            
        // follow the left wall
        case WALL_FOLLOW_L: {
          digitalWrite(LEDG, HIGH);
           digitalWrite(A8, LOW); 
            if((millis() - rt2Time) > 325){
              driveSpeed = SPEED;
            }
            if(stateCounter == 6 && !isDropping){
               ringServo.write(150); //move arm forward for second box
            }
                        
            if (wall_RS > DIST_START_TURN) {
                // approaching box; start small turn
                stateCounter++;
                }
            
            break; }
        
        ///Where we think the problem is    
        // find inner wall after delivering 3rd ring (part 1)
        /*case MIDDLE_AREA1:
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
            break;*/
 
        // line following after reversing in middle section
        case LINE_FOLLOW:
        
            /*if (pathCounter == 5 && amountSeen > 2) {
                //currentState = WALL_FOLLOW_L;
                
                setNose(NOSE_CENTER + 20);
                while(analogRead(WALL_SENSOR_L) < 400);
                setNose(NOSE_CENTER + 10);
                while(analogRead(WALL_SENSOR_L) < 600);
                
                //++pathCounter;
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
                if (wall_RS > DIST_START_TURN) {
                // approaching box; start small turn
                stateCounter++;
                }
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
            break;*/

        // initial small turn
        case LEFT_TURN1:
            
            
            // turn hard once we get close to the wall
            if (wall_LS > DIST_HARD_TURN) {
                stateCounter++;
            }
            break;

        // hard turn
        case LEFT_TURN2:
            
            digitalWrite(LEDR, LOW);
            if (lineData[7]) {
                stateCounter++;
            } 
            
            break;

        // initial small turn
        case RIGHT_TURN1:
        digitalWrite(LEDG, LOW);
            // turn hard once we get close to the wall
            if (/*wall_RS > DIST_HARD_TURN ||*/ wall_LS > 900) {
                stateCounter++;
            }
            break;

        // hard turn
        case RIGHT_TURN2:
            digitalWrite(A8, HIGH);
            rt2Time = millis();
            if (lineData[0]) { 
                stateCounter++;
            }
            //lastAngle = angle;
            break;
            
        case RIGHT_TURN3:
            rt3Time = millis();
            
            if(lineData[0]){
                stateCounter++;
            }
            break;
            
        case STOP:
            
            STOPIT();
            
            break;

        case FOLLOW_TILL_LOSE:

           if(amountSeen == 0){
              stateCounter++;
           }
           break;

       case LINE_FOLLOW_UNTIL_XING:
            //rt2Time = millis();
            
           if (wall_RS > DIST_START_TURN) {
                // approaching box; start small turn
                stateCounter++;
                }
           break;

        case FOLLOW_TIME:
          parkTime = millis();
          if((millis() - rt2Time) > 650){
              stateCounter++;
          }
          break;
          
       case FOLLOW_TIME_SHORT:

          if((millis() - rt2Time) > 300){
              stateCounter++;
          }
          break;

        case WALL_UNTIL_LOSE:

          if(wall_LS < 300 && wall_L < 100){
              stateCounter++;
          }
          break;
      
      case STRAIGHTtoWALL: 

          if((millis() - rt2Time) > 200){
              stateCounter++;
          }
          break;
          
      case LEFT_TURN_MAX: 

          if((millis() - rt2Time) > 1000){
              stateCounter++;
          }
          //lastAngle = angle;
          break;
          
        case GENTLE_RT: 

          if(amountSeen >= 3){
            stateCounter++;
          }
          break;
          
          case GENTLE_RT2:
          rt2Time = millis();
          if(amountSeen >= 2){
            stateCounter++;
          }
          break;

        case GENTLE_LT:
          //This 300 may need changed
          
          if(lineData[4]){
            stateCounter++;
          }
          break;
          
       case GENTLE_LT_2:
            digitalWrite(A8, HIGH);//white led
            
          if(wall_L > 600){
            stateCounter++;
          }
          break;

      case PRE_PARK:
          rt2Time = millis();
          if((millis() - parkTime) > 800){
            stateCounter++;
          }
          break;

      case PARK:

          if((millis() - rt2Time) > 500){
              stateCounter++;
          }
          break;
          
     case BACK_UP:

          if(lineData[4]){
            
            STOPIT();
          }
          break;
          
         default:
           digitalWrite(LEDG, HIGH);
            digitalWrite(LEDR, HIGH);
            digitalWrite(A8, HIGH);
            break;
    }
    stopRing();

    /*** CONTROLS OUTPUT ***/
    switch (stateMap[stateCounter]) {

        // follow the righ wall
        /*case WALL_FOLLOW_R:
            angle = NOSE_CENTER - (WALL_DIST - wall_R)/40;
            if (pathCounter == 8 && wall_R < 100) {
                angle = NOSE_CENTER;
            }
            break;*/
            
        // follow the left wall
        case WALL_FOLLOW_L:
                angle = NOSE_CENTER + (WALL_DIST - wall_L)/35; //THURSDAY

            break;

        case WALL_UNTIL_LOSE:
                angle = NOSE_CENTER + (WALL_DIST - wall_L)/35;

            break;
            
        // transition to middle section after dropping 3rd ring
        // before seeing the line
        
        // line follow in the middle after reversing
        case FOLLOW_TILL_LOSE:
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

        case FOLLOW_TIME:
        driveSpeed = SPEED;
            if (index == -1) {
                //we dont see the line
                angle = NOSE_CENTER - 30;

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
            
            case FOLLOW_TIME_SHORT:
            
            if (index == -1) {
                //we dont see the line
                angle = NOSE_CENTER - 20;

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

            case LINE_FOLLOW_UNTIL_XING:
            if((millis() - rt2Time) > 325){
              driveSpeed = SPEED;
            }
            if (index == -1) {
               
                angle = lastAngle;
              
            }else {
                // we see the line
                angle = index * 2;
                if (amountSeen == 2) {
                    ++angle;
                }
                if(amountSeen == -1){
                 digitalWrite(LEDR, HIGH);   
                }
                else{
                  digitalWrite(LEDR, LOW);
                }
                if(amountSeen == 1){
                 digitalWrite(LEDG, HIGH);   
                }
                else{
                 digitalWrite(LEDG, LOW); 
                }
                
                // set angle based on array
                angle = NOSE_CENTER - SENSOR_ANGLES[angle];
                lastAngle = angle;
            }
            break;
        
        // initial small left turn
        case LEFT_TURN1:
            
            angle = NOSE_CENTER + 15;
            break;

        // hard left turn
        case LEFT_TURN2:
            driveSpeed = TURN_SPEED;
            angle = 180;
            break;
         
         case STRAIGHTtoWALL:
            angle = NOSE_CENTER - 30;
            
            break;
            
         case LEFT_TURN_MAX:
            
            angle = NOSE_CENTER + 45;
            //lastAngle = angle;
            break;
            
        // initial small right turn
        case RIGHT_TURN1:
            //driveSpeed = SPEED;
            angle = NOSE_CENTER - 25;
            break;

        // hard right turn
        case RIGHT_TURN2:
        driveSpeed = TURN_SPEED;
            angle = 0;
            break;
        
        case RIGHT_TURN3:
        driveSpeed = TURN_SPEED;
            angle = 0;
            break;
            
         case STOP:
            angle = NOSE_CENTER;
            break;

        case GENTLE_RT:
            angle = NOSE_CENTER - 20;
            break;
            
        case GENTLE_RT2 :
            angle = NOSE_CENTER - 30;
            break;

        case GENTLE_LT:
        driveSpeed = TURN_SPEED;
            angle = NOSE_CENTER + 45;
            break;
            
        case GENTLE_LT_2:
        
            angle = NOSE_CENTER + 15;
            break;
            
        case PRE_PARK:
            angle = NOSE_CENTER + 35;
            break;
            
        case PARK:
            angle = NOSE_CENTER;
            break; 
       
       case BACK_UP:
            angle = NOSE_CENTER;
            driveSpeed = -90;
            ringServo.write(0);
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

