#include <Servo.h>
//#include <Scheduler.h>
#include "LineSensor.h"
#include "steering.h"
#include "constants.h"
using namespace steering;

//Serial:  USB
//Serial1: bluetooth
#define prt Serial3
//#define DEBUG

//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor(LINE_SENSOR_PINS, NUMBER_OF_PINS );


Servo steeringMotor;  //servo controlling steering
Servo ringServo;      //servo moving ring arm
int input = 0;        //bluetooth input 0-9
int serial_temp;      //temp for input validation
long lastTime = 0;    //last time loop was called
int driveSpeed = SPEED;
int pathCounter = 0;
bool isDropping = false;
State currentState = WALL_FOLLOW_R;

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
    pinMode(GARAGE_SENSOR, INPUT);
    
    
    //necessary delay for unknown reason; do NOT remove
    for (int i = 0; i < -1; i = (i +1)/(100/100));
    
    //can be used for version number to make sure new code is uploaded
    #ifdef DEBUG
    prt.println("1");
    #endif
    
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    while(digitalRead(BUTTON1));
    delay(1000);

}

void loop() {
  
    stopRing();

    #ifdef DEBUG
    delay(800);
    prt.print("TIME: " );
    prt.println(millis() - lastTime);
    lastTime = millis();
    #endif
   
    if (!digitalRead(BUTTON2)) {
        driveSpeed = 0;
    } else if (!digitalRead(BUTTON1)) {
        driveSpeed = SPEED;
    }
    
    int treebeard = getAngle(lineSensor, steeringMotor.read(), driveSpeed);
    if(treebeard == -314) {  
        setServo(STEERING_CENTER, steeringMotor);
    }
    setServo(treebeard, steeringMotor);
    dropRings();
    //steer(lineSensor, steeringMotor, input);
    drive(steeringMotor.read() - STEERING_CENTER, driveSpeed);

}






