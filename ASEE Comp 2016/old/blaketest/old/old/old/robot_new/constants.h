#ifndef CONSTANTS_H
#define CONSTANTS_H

const int test = 100;



//*** line sensor mesurements ***//
const int SENSOR_DISTANCES[8] = {0, 5, 10, 15, 20, 25, 30, 35};
const int NOSE_LENGTH = 200;

const int STEERING_LOWER_BOUND = 40;
const int STEERING_UPPER_BOUND = 125;

const int NUMBER_OF_PINS = 8;

const int PWMR = 5;
const int PWML = 6;

static int TOP_SPEED = 40;

// 0 turn left
// 1 straight
// 2 turn right
const int PATH_LENGTH  = 18;
const int PATH_TURNS[PATH_LENGTH] = {0, 0, 2, 2, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 2, 0};
const int PATH_ANGLE[3] = {-30, 0, 30};

#endif
