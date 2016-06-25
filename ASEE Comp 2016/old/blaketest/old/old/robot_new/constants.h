#ifndef CONSTANTS_H
#define CONSTANTS_H

const int test = 100;



//*** line sensor mesurements ***//

const int SENSOR_ANGLES[15] = {-50, -50, -40, -20, -10, -3.51, -1.72, 0, 1.72, 3.51, 10, 20, 40, 50, 50};
//const int SENSOR_ANGLES[15] = {-12.33, -10.65, -8.9, -7.11, -5.26, -3.51, -1.72, 0, 1.72, 3.51, 5.26, 7.11, 8.9, 10.65, 12.33};
//const int SENSOR_ANGLES[15] = {-6, -5, -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 4, 5, 6};
const int NOSE_LENGTH = 200;
const int REDUCE = 5;

const int STEERING_LOWER_BOUND = 30;
const int STEERING_CENTER = 82;
const int STEERING_UPPER_BOUND = 135;

const int NUMBER_OF_PINS = 8;
const int LINE_SENSOR_PINS[NUMBER_OF_PINS] = {12, 11, 10, 9, 8, 7, 4, 2};

const int PWMR = 5;
const int PWML = 6;

static int TOP_SPEED = 40;

// 0 turn left
// 1 straight
// 2 turn right
const int PATH_LENGTH  = 10;
const int PATH_TURNS[PATH_LENGTH] = {0, 1, 1, 0, 1, 0, 1, 1, 0, 1};
const int PATH_ANGLE[3] = {-30, 0, 30};

enum State { LINE_FOLLOW, LEFT_TURN1, LEFT_TURN2, RIGHT_TURN1, RIGHT_TURN2, IGNORE_TURN };

#endif
