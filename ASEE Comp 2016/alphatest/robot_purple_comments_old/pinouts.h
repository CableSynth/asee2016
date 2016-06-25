#ifndef PINOUTS_H
#define PINOUTS_H


    
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



// Analog Pins
#define COLOR_SENSOR_R    A4
#define COLOR_SENSOR_L    A9
#define LINE_SENSOR_BR    A2
#define WALL_SENSOR_FAR   A10
//#define LINE_SENSOR_BL    A10 not recognized by compiler, using "64" since its the digital pin number
#define WALL_SENSOR_R     A7
#define WALL_SENSOR_RS    A6 
#define WALL_SENSOR_LS    A5 //A8 not recognized by compiler, using "62" since its the digital pin number
#define WALL_SENSOR_L     A4
#define GARAGE_SENSOR     A9

//Digital Pins 
#define LINE_SENSOR_0     41
#define LINE_SENSOR_1     43
#define LINE_SENSOR_2     45
#define LINE_SENSOR_3     47  
#define LINE_SENSOR_4     49
#define LINE_SENSOR_5     51
#define LINE_SENSOR_6     53
#define LINE_SENSOR_7     52

#define LEDR              38
#define LEDG              40

#define BUTTON1           30
#define BUTTON2           32

//PWM
#define RING_DISPENSER_R1 13
#define RING_DISPENSER_R2 12
#define RING_DISPENSER_L1 11
#define RING_DISPENSER_SERVO 10
#define RING_CHUTE_R      5
#define RING_CHUTE_L      4
#define STEERING_MIDDLE   9

//Motor Controllers
#define WHEEL_DIR_FR_B     34
#define WHEEL_DIR_FR_F     36    
#define WHEEL_DIR_FL_B     35
#define WHEEL_DIR_FL_F     37
#define WHEEL_DIR_BR_B     35 //purple: 31
#define WHEEL_DIR_BR_F     37 //purple: 33
#define WHEEL_DIR_BL_B     27 //purple: 23
#define WHEEL_DIR_BL_F     29 //purple: 25

#define WHEEL_PWM_FR      8
#define WHEEL_PWM_FL      7
#define WHEEL_PWM_BR      2
#define WHEEL_PWM_BL      3
#define WHEEL_PWM_B_STBY  31
#define WHEEL_PWM_R_STBY  33


//Special
#define BLUETOOTH_TX1     18    //Note: 3.3V MAX!!
#define BLUETOOTH_RX1     19    //    For any pin
#define SPEAKER_DAC0      DAC0
#define SPEAKER_DAC1      DAC1

#endif
