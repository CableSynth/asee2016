#ifndef PINOUTS_H
#define PINOUTS_H

// Analog Pins
#define COLOR_SENSOR_R    A4
#define COLOR_SENSOR_L    A9
#define LINE_SENSOR_BR    A2
#define LINE_SENSOR_BL   A10
//#define LINE_SENSOR_BL    A10 not recognized by compiler, using "64" since its the digital pin number
#define WALL_SENSOR_R     A3
#define WALL_SENSOR_L     A8 
#define WALL_SENSOR_L     62 //A8 not recognized by compiler, using "62" since its the digital pin number
#define GARAGE_SENSOR     A5

//Digital Pins 
#define LINE_SENSOR_0     39 //green: 39 //Pin 37 is said to be used for motor controllers
#define LINE_SENSOR_1     41 //green: 41
#define LINE_SENSOR_2     43 //green: 43
#define LINE_SENSOR_3     45 //green: 45  
#define LINE_SENSOR_4     47 //green: 47
#define LINE_SENSOR_5     49 //green: 49
#define LINE_SENSOR_6     51 //green: 51  
#define LINE_SENSOR_7     53 //green: 52  //53 appears to be driven high
#define LED1              38
#define LED2              40

#define BUTTON1           30
#define BUTTON2           32

//PWM
#define RING_DISPENSER_R1 13
#define RING_DISPENSER_R2 12
#define RING_DISPENSER_L1 11
#define RING_DISPENSER_L2 10
#define RING_CHUTE_R      5
#define RING_CHUTE_L      4
#define STEERING_MIDDLE   9

//Motor Controllers
#define WHEEL_DIR_FR_B     34
#define WHEEL_DIR_FR_F     36    
#define WHEEL_DIR_FL_B     35
#define WHEEL_DIR_FL_F     37
#define WHEEL_DIR_BR_B     35 //purple: 31 //green: 35  //who knows waht purpole is
#define WHEEL_DIR_BR_F     37 //purple: 33 //green: 37  // "watt" -michael
#define WHEEL_DIR_BL_B     27 //purple: 23 //green: 27
#define WHEEL_DIR_BL_F     29 //purple: 25 //green: 29

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
