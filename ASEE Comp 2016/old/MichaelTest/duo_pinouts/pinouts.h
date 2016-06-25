#ifndef PINOUTS_H
#define PINOUTS_H

// Analog Pins
#define COLOR_SENSOR_R  	A4
#define COLOR_SENSOR_L  	A9
#define LINE_SENSOR_BR  	A2
#define LINE_SENSOR_BL   A10
//#define LINE_SENSOR_BL    A10 not recognized by compiler, using "64" since its the digital pin number
#define WALL_SENSOR_R   	A3
#define WALL_SENSOR_L    A8 
#define WALL_SENSOR_L     62 //A8 not recognized by compiler, using "62" since its the digital pin number
#define GARAGE_SENSOR		  A5

//Digital Pins 
#define LINE_SENSOR_1	  	39
#define LINE_SENSOR_2	  	41
#define LINE_SENSOR_3		  43
#define LINE_SENSOR_4    	45  
#define LINE_SENSOR_5	  	47
#define LINE_SENSOR_6		  49
#define LINE_SENSOR_7		  51
#define LINE_SENSOR_8		  53

#define LED1				      38
#define LED2				      40

#define WHEEL_DIR_FR1		  34
#define WHEEL_DIR_FR2		  36		
#define WHEEL_DIR_FL1		  35
#define WHEEL_DIR_FL2		  37
#define WHEEL_DIR_BR1		  26
#define WHEEL_DIR_BR2		  28     
#define WHEEL_DIR_BL1		  27
#define WHEEL_DIR_BL2		  29

#define BUTTON1				    30
#define BUTTON2				    32

//PWM
#define RING_DISPENSER_R1	13
#define RING_DISPENSER_R2	12
#define RING_DISPENSER_L1	11
#define RING_DISPENSER_L2	10
#define RING_CHUTE_R		  5
#define RING_CHUTE_L		  4
#define STEERING_MIDDLE		9

//Motor Controllers
#define WHEEL_PWM_FR		  8
#define WHEEL_PWM_FL		  2
#define WHEEL_PWM_BR		  7
#define WHEEL_PWM_BL		  3

//Special
#define BLUETOOTH_TX1		  18	  //Note: 3.3V MAX!!
#define BLUETOOTH_RX1		  19	  //		For any pin
#define SPEAKER_DAC0		  DAC0
//#define SPEAKER_DAC0      66 //DAC0 not recognized by compiler, using "66" since its the digital pin number
#define SPEAKER_DAC1		  DAC1
//#define SPEAKER_DAC1      67 //DAC1 not recognized by compiler, using "67" since its the digital pin number

#endif
