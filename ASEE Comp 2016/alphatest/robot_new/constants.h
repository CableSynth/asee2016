#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "pinouts.h"


const int TILL_TURN = 260000;
const int TURN = 185000;
const int AFTER_TURN = 120000;

const bool IS_BT = true;

const int test = 100;

static const int STEERING_PIN = STEERING_MIDDLE;

//*** line sensor mesurements ***//
const int SENSOR_ANGLES[15] = {-5, -4, -3, -2, -2, -1, 0, 0, 0, 1, 2, 2, 3, 4, 5};
//const int SENSOR_ANGLES[15] = {-40, -20, -15, -10, -7, -5, -3, 0, 3, 5, 7, 10, 15, 20, 40};

//const int SENSOR_ANGLES[15] = {-12.33, -10.65, -8.9, -7.11, -5.26, -3.51, -1.72, 0, 1.72, 3.51, 5.26, 7.11, 8.9, 10.65, 12.33};
//const int SENSOR_ANGLES[15] = {-6, -5, -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 4, 5, 6};

const int NOSE_LENGTH = 200;
const int REDUCE = 1;

/*
 * OLD
 * const int STEERING_LOWER_BOUND = 30;
 * const int STEERING_CENTER = 82;
 * const int STEERING_UPPER_BOUND = 135;*/

const int STEERING_LOWER_BOUND = 50;
const int STEERING_CENTER = 95;
const int STEERING_UPPER_BOUND = 140;


//const int STEERING_LOWER_BOUND = 65;
//const int STEERING_CENTER = 105;
//const int STEERING_UPPER_BOUND = 145;

static const int NUMBER_OF_PINS = 8;
static const int LINE_SENSOR_PINS[NUMBER_OF_PINS] = {LINE_SENSOR_0, LINE_SENSOR_1,LINE_SENSOR_2,
	LINE_SENSOR_3, LINE_SENSOR_4, LINE_SENSOR_5, LINE_SENSOR_6, LINE_SENSOR_7};

const int PWMR = WHEEL_PWM_BR;
const int PWML = WHEEL_PWM_BL;

static int TOP_SPEED = 40;

// 0 turn left
// 1 straight
// 2 turn right

const int LT = 0;
const int ST = 1;
const int RT = 2;
const int END = -1;
const int PATH_LENGTH  = 11;
const int PATH_TURNS[PATH_LENGTH] = {ST, LT, ST, LT, LT, RT, ST, LT, ST, LT,END};
const bool RING_DROPS[PATH_LENGTH] = {false, true, false, true, true, false, false, true, false, true, false};
const int PATH_ANGLE[3] = {-30, 0, 30};

enum State { LINE_FOLLOW, LEFT_TURN1, LEFT_TURN2, RIGHT_TURN1, RIGHT_TURN2, IGNORE_TURN,LAND_PLANE };

#endif
