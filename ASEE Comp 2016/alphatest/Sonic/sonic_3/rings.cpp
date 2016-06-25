#include "constants.h"
#include "nose.h"
#include "wheels.h"
#include "rings.h"
#include <Arduino.h>
#include <Servo.h>

//Serial:  USB
//Serial1: bluetooth
#define prt Serial3
//#define DEBUG

extern bool isDropping;
extern int stateCounter;
extern State currentState;
extern Servo ringServo;

extern int wall_L;
extern int wall_LS;
extern int wall_RS;
extern int wall_R;
extern int wall_Far;
extern int snorkle;
extern int dropCounter;
extern int stateCounter;

void rings::dropRings() {
    
    //The snorkle: floor is around 40 and board is around 185
    if(snorkle > 112 && !isDropping && 
    (stateCounter == 4 || stateCounter == 5 || stateCounter == 9 || stateCounter == 10 || stateCounter == 12 || stateCounter == 18 || stateCounter == 19
    || stateCounter == 22 || stateCounter == 23 || stateCounter == 25 || stateCounter == 26 || stateCounter == 30 || stateCounter == 31 )){
      dropCounter++;
      dropRing();
    }
 
  /*if(snorkle > 400 && !isDropping && stateCounter !=10) { //if on the wall and not doing a gentle LT
        
        //if we're supposed to drop, then drop
        if(doWeDrop[dropCounter] == true){
          dropRing();
        }
               
        dropCounter++;        
    } 
    
        stopRing();       
     

  //Blake's Old code
    //static int droppedState[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //static int hasDropped[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};    
    /*static State lastState = STRAIGHT_TIME;
    static State ringState = STRAIGHT_TIME;
    static int pathLatch = -1;
    static bool done012 = false;
    static bool seeWall = false;
    
    static bool isDropped = false;
    #ifdef DEBUG
    prt.print("RS: ");
    prt.print(ringSense);
    prt.print("  ");
    #endif
    
    if (pathLatch == -1 && wall_RS > DIST_START_TURN && !hasDropped[stateCounter]) {
        pathLatch = stateCounter ;
    } else if (pathLatch != -1 && hasDropped[pathLatch] && !isDropping) {
        pathLatch = -1;
    }
    
    if(snorkle < 400) {
        ringState = STRAIGHT_TIME;
    } else {
        ringState = ON_WALL;
    }
    
    if (currentState == MIDDLE_AREA2) {
        done012 = true;
    }
    
    switch(pathLatch) {
       
        case 2:
            if (!hasDropped[pathLatch] && ringState == ON_WALL && lastState == ON_WALL) {
                dropRing();
                hasDropped[pathLatch] = true;
            }
            break;
        case 5:
            if(!hasDropped[pathLatch] && ringState == ON_WALL && lastState == ON_WALL) {
                dropRing();
                hasDropped[pathLatch] = true;
            }
            break;
        case 8:
            if(!hasDropped[pathLatch] && ringState == ON_WALL && lastState == ON_WALL) {
                dropRing();
                hasDropped[pathLatch] = true;
            }
            break;
    }
    
    lastState = ringState;*/
  
}


void rings::dropRing() {
        analogWrite(WHEEL_PWM_FR,255);
        isDropping = true;
}

void rings::stopRing()  {
    static bool getInTheHole = false;
    if (digitalRead(RING_DISPENSER_R2) == 0 && !getInTheHole) {
        return;
    }
    
    if (digitalRead(RING_DISPENSER_R2) != 0 && !getInTheHole) {
        getInTheHole = true;
        return;
    } 
    
    if (digitalRead(RING_DISPENSER_R2) == 0 && getInTheHole) {
        getInTheHole = false;
        analogWrite(WHEEL_PWM_FR,0);
        isDropping = false;
        return;
    }
}
