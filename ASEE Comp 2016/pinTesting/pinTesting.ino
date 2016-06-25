#define prt Serial


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



static const int STEERING_PIN = STEERING_MIDDLE;




const int STEERING_LOWER_BOUND = 45;
const int STEERING_CENTER = 92;
const int STEERING_UPPER_BOUND = 140;

static const int NUMBER_OF_PINS = 8;
static const int LINE_SENSOR_PINS[NUMBER_OF_PINS] = {LINE_SENSOR_0, LINE_SENSOR_1,LINE_SENSOR_2,
	LINE_SENSOR_3, LINE_SENSOR_4, LINE_SENSOR_5, LINE_SENSOR_6, LINE_SENSOR_7};

const int PWMR = WHEEL_PWM_BR;
const int PWML = WHEEL_PWM_BL;

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

//wall distances
const int DIST_START_TURN = 480;
const int DIST_HARD_TURN = 840;
const int DIST_END_TURN = 200;
const int WALL_DIST = 600;

const int SPEED = 150;
const int TURN_SPEED = 100;

enum State { LINE_FOLLOW, LEFT_TURN1, LEFT_TURN2, RIGHT_TURN1, RIGHT_TURN2, IGNORE_TURN,LAND_PLANE, OFF_TRACK, ON_WALL, ON_TRACK, POST_DROP, WALL_FOLLOW_R, WALL_FOLLOW_L, MIDDLE_AREA1, MIDDLE_AREA2 };




#include <Servo.h>
#include "LineSensor.h"

//Serial:  USB
//Serial1: bluetooth
//#define DEBUG

//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor(LINE_SENSOR_PINS, NUMBER_OF_PINS );


Servo steeringMotor;  //servo controlling steering
Servo ringServo;      //servo moving ring arm
int input = 0;        //bluetooth input 0-9
int serial_temp;      //temp for input validation
long lastTime = 0;    //last time loop was called
int driveSpeed = SPEED;

void setup() {

    pinMode(LEDG, OUTPUT);
    pinMode(LEDR, OUTPUT);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDR, HIGH);
  
    //setup steering servo and point it straight
    steeringMotor.attach(STEERING_PIN);
    steeringMotor.write(STEERING_CENTER);

    //setup ring arm servo
    ringServo.attach(RING_DISPENSER_SERVO);
    ringServo.write(0);

    //start serial communication
    prt.begin(115200);


    //setup driving motor speed pins
    pinMode(PWMR, OUTPUT);
    pinMode(PWML, OUTPUT);
    analogWrite(PWMR, 0);
    analogWrite(PWML, 0);
    
    //tell back left motor to drive forward
    pinMode(WHEEL_DIR_BL_F, OUTPUT);
    pinMode(WHEEL_DIR_BL_B, OUTPUT);
    digitalWrite(WHEEL_DIR_BL_F, HIGH);
    digitalWrite(WHEEL_DIR_BL_B, LOW);
    
    //tell back right motor to drive forward
    pinMode(WHEEL_DIR_BR_F, OUTPUT);
    pinMode(WHEEL_DIR_BR_B, OUTPUT);
    digitalWrite(WHEEL_DIR_BR_F, HIGH);
    digitalWrite(WHEEL_DIR_BR_B, LOW);
    
    //enable driving motor controller
    pinMode(WHEEL_PWM_B_STBY, OUTPUT);
    digitalWrite(WHEEL_PWM_B_STBY, HIGH);


    //setup ring dispensing motor
    pinMode(WHEEL_PWM_FR, OUTPUT);
    analogWrite(WHEEL_PWM_FR, 0);
    pinMode(WHEEL_DIR_BR_F, OUTPUT);
    digitalWrite(WHEEL_DIR_FR_B, HIGH);
    digitalWrite(WHEEL_DIR_FR_F, LOW);
    
    //enable ring dispensing motor controller
    pinMode(WHEEL_PWM_R_STBY, OUTPUT);
    digitalWrite(WHEEL_PWM_R_STBY, HIGH);

    //misc line sensor pin that does not get init in contructor for some reason
    //pinMode(39, INPUT);
    pinMode(11, INPUT);
    pinMode(53, INPUT);
    
    //setup wall sensors
    pinMode(WALL_SENSOR_R, INPUT);
    pinMode(WALL_SENSOR_RS, INPUT);
    pinMode(WALL_SENSOR_L, INPUT);
    pinMode(WALL_SENSOR_LS, INPUT);
    pinMode(GARAGE_SENSOR, INPUT);
    pinMode(A8, INPUT);
    
    
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);

}



void loop() {
    digitalWrite(LEDG, LOW);
    while(digitalRead(BUTTON1)) {
        delay(500);
        prt.print(analogRead(WALL_SENSOR_L));
        prt.print(' ');
        prt.print(analogRead(WALL_SENSOR_LS));
        prt.print(' ');
        prt.print(analogRead(WALL_SENSOR_RS));
        prt.print(' ');
        prt.print(analogRead(WALL_SENSOR_R));
        prt.print(' ');
        prt.println(analogRead(WALL_SENSOR_FAR));
        prt.print(' ');
        prt.println(analogRead(A9));
    }
    int *t = new int[8];
    LineSensor lineSensor(LINE_SENSOR_PINS, NUMBER_OF_PINS );
    while(!digitalRead(BUTTON1));
    while(digitalRead(BUTTON1)) {
        delay(500);
        
        lineSensor.getCurrent(t);
        
        for (int i = 0; i < 8; ++i) {
            prt.print(t[i]);
        }
        prt.println(' ');
    }
    
    
    
    while(!digitalRead(BUTTON1));
    while(digitalRead(BUTTON1)) {
        steeringMotor.write(60);
        delay(1000);
        steeringMotor.write(90);
        delay(1000);
        steeringMotor.write(120);
        delay(1000);
    }

}
