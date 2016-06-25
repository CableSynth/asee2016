#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "pinouts.h"


static const int STEERING_PIN = STEERING_MIDDLE;

//*** line sensor mesurements ***//
const int SENSOR_ANGLES[15] = {-20, -15, -15, -15, -10, -10, -10, -5, -3, 0, 0, 0, 3, 5}; //non-symetric line following


//steering servo
const int NOSE_RIGHT_MAX = 55;
const int NOSE_CENTER = 100;
const int NOSE_LEFT_MAX = 145;

static const int NUMBER_OF_PINS = 8;
static const int LINE_SENSOR[NUMBER_OF_PINS] = {LINE_SENSOR_0, LINE_SENSOR_1,LINE_SENSOR_2,
	LINE_SENSOR_3, LINE_SENSOR_4, LINE_SENSOR_5, LINE_SENSOR_6, LINE_SENSOR_7};

const int PWMR = WHEEL_PWM_BR;
const int PWML = WHEEL_PWM_BL;


//wall distances
const int DIST_START_TURN = 380; //we expect for Tails this should be the RS
const int DIST_HARD_TURN = 500; 
const int DIST_END_TURN = 100;
const int WALL_DIST = 600; //R (not RS) 45 deg. out the side. Says how far away from wall to follow

const int SPEED = 200; //Between 0-255
//const int MAX_SPEED = 255;
const int TURN_SPEED = 100; 

enum State {LINE_FOLLOW, LEFT_TURN1, LEFT_TURN2, RIGHT_TURN1, RIGHT_TURN2, RIGHT_TURN3, OFF_WALL, ON_WALL, WALL_FOLLOW_R, WALL_FOLLOW_L, MIDDLE_AREA1, MIDDLE_AREA2, LINE_FOLLOW_UNTIL_XING, EDGE_AREA, FOLLOW_TILL_LOSE, FOLLOW_TIME, FOLLOW_TIME_SHORT, WALL_UNTIL_LOSE, GENTLE_RT, GENTLE_RT2, GENTLE_LT, GENTLE_LT_2, PRE_PARK, PARK, STOP, STRAIGHTtoWALL, LEFT_TURN_MAX  };

//_NEW
const int stateMap[24] = {WALL_FOLLOW_L, RIGHT_TURN1, RIGHT_TURN2, WALL_FOLLOW_L, RIGHT_TURN1, RIGHT_TURN2, WALL_FOLLOW_L, RIGHT_TURN1,
RIGHT_TURN3, STRAIGHTtoWALL, LEFT_TURN_MAX, GENTLE_LT_2, WALL_FOLLOW_L, RIGHT_TURN1, RIGHT_TURN2, LINE_FOLLOW_UNTIL_XING, 
FOLLOW_TIME_SHORT, WALL_FOLLOW_L, RIGHT_TURN1, RIGHT_TURN2, GENTLE_RT2, FOLLOW_TIME, PRE_PARK, PARK };

//const bool doWeDrop[15] = { true, false, true, false, true, false, true, false, true, false, true, false, false};


#endif
