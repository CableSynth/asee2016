#include <Servo.h>
//#include <Scheduler.h>
#include "LineSensor.h"
#include "steering.h"
#include "constants.h"
using namespace steering;

//Serial:  USB
//Serial1: bluetooth
#define prt Serial1

//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor(LINE_SENSOR_PINS, NUMBER_OF_PINS );


Servo steeringMotor;  //servo controlling steering
Servo ringServo;      //servo moving ring arm
int input = 0;        //bluetooth input 0-9
int serial_temp;      //temp for input validation
long lastTime = 0;    //last time loop was called

void setup() {

    //setup steering servo and point it straight
    steeringMotor.attach(STEERING_PIN);
    steeringMotor.write(STEERING_CENTER);

    //setup ring arm servo
    ringServo.attach(RING_DISPENSER_SERVO);
    ringServo.write(90);

    //start serial communication
    prt.begin(9600);


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
    pinMode(WHEEL_DIR_BR_F, OUTPUT);
    digitalWrite(WHEEL_DIR_FR_B, HIGH);
    digitalWrite(WHEEL_DIR_FR_F, LOW);
    
    //enable ring dispensing motor controller
    pinMode(WHEEL_PWM_R_STBY, OUTPUT);
    digitalWrite(WHEEL_PWM_R_STBY, HIGH);

    //misc line sensor pin that does not get init in contructor for some reason
    pinMode(11, INPUT);
    pinMode(80, INPUT); //IR wall sensor
    
    //necessary delay for unknown reason; do NOT remove
    for (int i = 0; i < -1; i = (i +1)/(100/100));
    
    //can be used for version number to make sure new code is uploaded
    prt.println("1");
}

void loop() {

    /*
     *    Steering servo calibration code 
     */
    /*while(            1) {
        if(Serial.available() > 2) {
            serial_temp = Serial.read()-'0';
            serial_temp = serial_temp * 10 + Serial.read()-'0';
            serial_temp = serial_temp * 10 + Serial.read()-'0';
            Serial.println(serial_temp);
            //if(serial_temp >= 0 && serial_temp <= 9){
                steeringMotor.write(serial_temp);
            //}
        }
    }*/
    
    // get input from bluetooth
    // 0-9: speeds
    if(prt.available() > 0) {
        serial_temp = prt.read()-'0';
        if(serial_temp >= 0 && serial_temp <= 9){
            input = (serial_temp) * 30;
        }
    }
  
  int distanceToWall = AnalogRead(80);
  
   stopRing();
    
    if (input != 0) {
        prt.println(millis() - lastTime);//print to bluetooth
        lastTime = millis();
        
        if (steer(lineSensor, steeringMotor, input)) {
            drive(steeringMotor.read() - STEERING_CENTER, input);
        } else {
            drive(steeringMotor.read() - STEERING_CENTER, 0);
        }
    } else {
        drive(steeringMotor.read() - STEERING_CENTER, 0);
    }
    
}

void driveThing() {
    while(true){
    
}
  
}







void dispenseRing() {
    analogWrite(WHEEL_PWM_FL,150);
    while(true);
}








