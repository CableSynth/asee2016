#include <Servo.h>
#include "LineSensor.h"
#include "steering.h"
#include "constants.h"
using namespace steering;


int const steeringPin = 3;

//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor( LINE_SENSOR_PINS, NUMBER_OF_PINS );

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

    delay(50);
    if(Serial.available() > 0) {
        serial_temp = Serial.read()-'0';
        if(serial_temp >= 0 && serial_temp <= 9){
            input = (serial_temp) * 20;
        }
    }
    
    steer(lineSensor, steeringMotor);

    drive(steeringMotor.read() - 90, input);
}
