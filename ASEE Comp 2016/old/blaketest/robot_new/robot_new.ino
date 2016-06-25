#include <Servo.h>
//#include <Scheduler.h>
#include "LineSensor.h"
#include "steering.h"
#include "constants.h"
using namespace steering;

#define prt Serial1

//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor(LINE_SENSOR_PINS, NUMBER_OF_PINS );

Servo steeringMotor;
Servo ringServo;
int input = 0;
int serial_temp;
int angle = 90;
long t = 0;

void setup() {

    steeringMotor.attach(STEERING_PIN);
    steeringMotor.write(STEERING_CENTER);

    ringServo.attach(RING_DISPENSER_SERVO);
    ringServo.write(90);

    prt.begin(9600);
    //Serial1.begin(9600);

    //set
    pinMode(PWMR, OUTPUT);
    pinMode(PWML, OUTPUT);
    analogWrite(PWMR, 0);
    analogWrite(PWML, 0);
    
    pinMode(WHEEL_DIR_BL_F, OUTPUT);
    pinMode(WHEEL_DIR_BL_B, OUTPUT);
    digitalWrite(WHEEL_DIR_BL_F, HIGH);
    digitalWrite(WHEEL_DIR_BL_B, LOW);
    
    pinMode(WHEEL_DIR_BR_F, OUTPUT);
    pinMode(WHEEL_DIR_BR_B, OUTPUT);
    digitalWrite(WHEEL_DIR_BR_F, HIGH);
    digitalWrite(WHEEL_DIR_BR_B, LOW);
    
    pinMode(WHEEL_PWM_B_STBY, OUTPUT);
    digitalWrite(WHEEL_PWM_B_STBY, HIGH);


    
    pinMode(WHEEL_DIR_BR_F, OUTPUT);
    digitalWrite(WHEEL_DIR_FR_B, HIGH);
    digitalWrite(WHEEL_DIR_FR_F, LOW);
    
    pinMode(WHEEL_PWM_R_STBY, OUTPUT);
    digitalWrite(WHEEL_PWM_R_STBY, HIGH);

    pinMode(11, INPUT);
    pinMode(LINE_SENSOR_PINS[7], INPUT);
    
    for (int i = 0; i < -1; i = (i +1)/(100/100));
    prt.println("1");
    //Serial1.println("1");
}

void loop() {

    /*    Steering servo calibration code 
     * 
     while(1) {
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

   stopRing();
    
    if (input != 0) {
        prt.println(millis() - t);
        t = millis();
        
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








