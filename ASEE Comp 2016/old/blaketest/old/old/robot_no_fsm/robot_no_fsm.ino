#include <Servo.h>
#include "LineSensor.h"
#include "steering.h"
#include "constants.h"
using namespace steering;


int const steeringPin = 3;

//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor( new int [8] {12, 11, 10, 9, 8, 7, 4, 2}, NUMBER_OF_PINS );

Servo steeringMotor;
int input = 0;
int serial_temp;
int angle = 90;

void setup() {

    steeringMotor.attach(steeringPin);

    Serial.begin(9600);

    pinMode(PWMR, OUTPUT);
    pinMode(PWML, OUTPUT);
    delay(1000);

}

void loop() {

    if(Serial.available() > 0) {
        serial_temp = Serial.read()-'0';
        if(serial_temp >= 0 && serial_temp <= 9){
            input = (serial_temp) * 28;
        }
    }
    if (input != 0) {
        steer(lineSensor, steeringMotor, input);
    
        drive(steeringMotor.read() - 90, input);
        Serial.println(steeringMotor.read());
    } else {
        
        drive(steeringMotor.read()- 90, 0);
    }
}
