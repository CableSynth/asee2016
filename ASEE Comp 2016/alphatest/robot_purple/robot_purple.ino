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
    prt.println("1");
}

void loop() {

    /*
     *    Steering servo calibration code 
     */
    /*while(1) {
        if(Serial.available() > 2) {
            serial_temp = Serial.read()-'0';
            serial_temp = serial_temp * 10 + Serial.read()-'0';
            serial_temp = serial_temp * 10 + Serial.read()-'0';
            Serial.println(serial_temp);
            //if(serial_temp >= 0 && serial_temp <= 9){
//                steeringMotor.write(serial_temp);
                moveServo(serial_temp, steeringMotor);
            //}
        }
    }*/
    int dist;
   /*while(true) {
//        if(prt.available() > 0) {
//            serial_temp = prt.read()-'0';
//            if(serial_temp >= 0 && serial_temp <= 9){
//                input = (serial_temp) * 30;
//            }
//        }
//        dist = analogRead(WALL_SENSOR_R);
//        int err = (300 - dist);
//        int angle;
        delay(500);
        prt.println(analogRead(GARAGE_SENSOR));
//        prt.print('\t');
//        prt.print(err);
//        prt.print('\t');
//        if (dist > 305) {
//          angle = STEERING_CENTER - err/50;
//          //prt.println(angle);
//          //setServo(angle, steeringMotor);
//        } else if (dist < 295) {
//          angle = STEERING_CENTER - err/10;
//          //prt.println(angle);
//          //setServo(angle, steeringMotor);
//        }
//        
//        if (input != 0) {
//            drive(steeringMotor.read() - STEERING_CENTER, input);
//        } else {
//            drive(steeringMotor.read() - STEERING_CENTER, 0);
//        }
        
    }*/
    
    
    //delay(1000);
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
        #ifdef DEBUG
        delay(800);
        prt.print("TIME: " );
        prt.println(millis() - lastTime);
        #endif
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






