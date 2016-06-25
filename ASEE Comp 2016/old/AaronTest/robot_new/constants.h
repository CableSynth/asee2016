#ifndef CONSTANTS_H
#define CONSTANTS_H

const int test = 100;



//*** line sensor mesurements ***//
const int SENSOR_DISTANCES[8] = {-20, -15, -10, 0, 0, 10, 15, 20};
const int NOSE_LENGTH = 200;

const int STEERING_LOWER_BOUND = 40;
const int STEERING_UPPER_BOUND = 125;

const int NUMBER_OF_PINS = 8;
const int LINE_SENSOR_PINS[NUMBER_OF_PINS] = {12, 11, 10, 9, 8, 7, 4, 2};
const int LED_PIN = 13;

const int PWMR = 5;
const int PWML = 6;

static int TOP_SPEED = 40;

// 0 turn left
// 1 straight
// 2 turn right
const int PATH_LENGTH  = 10;
const int PATH_TURNS[PATH_LENGTH] = {0, 1, 0, 1, 1, 0, 1, 0, 1, 1};
const int PATH_ANGLE[3] = {-10, 0, 10};

#endif
