#include <Servo.h>
#include "LineSensor.h"
#include "steering.h"
#include "constants.h"
using namespace steering;


int const steeringPin = 3;
int timer1_counter;
const int clock_speed = 16000000;
const int sampling_frequency = 2;
const int prescalar = 256;

//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor( new int [8] {12, 11, 10, 9, 8, 7, 4, 2}, NUMBER_OF_PINS );

Servo steeringMotor;
int input = 0;
int serial_temp;
int angle = 90;

void setup() {

    noInterrupts();
    TCCR1A = 0;
    TCCR1B = 0;

    timer1_counter = 65536 - clock_speed / (prescalar * sampling_frequency);
    
    TCNT1 = timer1_counter;
    TCCR1B |= (1 << CS12);
    TIMSK1 |= (1 << TOIE1);

    pinMode(LED_PIN, OUTPUT);

    steeringMotor.attach(steeringPin);

    Serial.begin(9600);

    pinMode(PWMR, OUTPUT);
    pinMode(PWML, OUTPUT);
    delay(1000);
    
    interrupts();
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timer1_counter;   // preload timer
  digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}

void loop() {

    delay(50);
    if(Serial.available() > 0) {
        serial_temp = Serial.read()-'0';
        if(serial_temp >= 0 && serial_temp <= 9){
            input = (serial_temp) * 20;
        }
    }
    
    steer(lineSensor, steeringMotor, input);

    drive(steeringMotor.read() - 90, input);
}
