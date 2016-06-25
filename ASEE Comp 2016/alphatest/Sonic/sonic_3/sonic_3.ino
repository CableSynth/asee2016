#include <Servo.h>
#include "nose.h"
#include "wheels.h"
#include "rings.h"
#include "constants.h"
using namespace nose;
using namespace rings;
using namespace wheels;

//Serial:  USB
//Serial3: bluetooth
#define prt Serial3
//#define DEBUG

//*********************SONIC***************************

/*** OUTPUT ***/
// controls the nose
Servo steeringMotor;

// controls the ring dispensing arm
Servo ringServo;


/*** INPUT ***/
// line sensors; 1 = sees line; 0-7 ~ L-R
bool* lineData = new bool[8]; 

// wall sensors; the bigger the number, the closer the wall
int wall_L;
int wall_LS;
int wall_RS;
int wall_R;
int wall_Far;
int snorkle;


long lastTime = 0;
int driveSpeed = SPEED;
int pathCounter = 0;
int stateCounter = 0; //_NEW
int dropCounter = 0; //_NEW
int rt2Time = 0;
int rt3Time = 0;
int parkTime = 0;
bool isDropping = false;
State currentState = WALL_FOLLOW_L;

void loop() {

    #ifdef DEBUG
    delay(800);
    prt.print("TIME: " );
    prt.println(millis() - lastTime);
    lastTime = millis();
    #endif
   
    // stop if taller button is pressed
    if (!digitalRead(BUTTON2)) {
        driveWheels(0, 0);

        // resume once smaller button is pressed
        while(digitalRead(BUTTON1)) { stopRing(); }
        driveSpeed = SPEED;
    }



    updateSensors();
    stopRing();

    steer();
    stopRing();
    
    dropRings();
    stopRing();

        //This "angle" is the deviation from center | 0 for straight, 
    drive(steeringMotor.read() - NOSE_CENTER, driveSpeed);
    stopRing();

}



void setup() {

    // line sensor pins
    for (int i = 0; i < NUMBER_OF_PINS; ++i) {
        pinMode(LINE_SENSOR[i], INPUT);
    }

    //LEDs on shield
    pinMode(LEDG, OUTPUT);
    pinMode(LEDR, OUTPUT);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDR, HIGH);
  
    //setup steering servo and point it straight
    steeringMotor.attach(STEERING_PIN);
    steeringMotor.write(NOSE_CENTER);

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
    

    //can be used for version number to make sure new code is uploaded
    #ifdef DEBUG
    prt.println("1");
    #endif
    
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    while(digitalRead(BUTTON1));
    
    long t = millis();
    bool toggle = false;
    while(analogRead(A8) > 400) { //Wait for light to go out
        if(millis() - t > 100) {
            if(toggle) {
                digitalWrite(LEDG, HIGH);
            } else {
                digitalWrite(LEDG, LOW);
            }
            
            t = millis();
            toggle = !toggle;
        }
    }
    
    
    setNose(NOSE_CENTER + 30);//drop nose
    delay(200);
    for(int i = 0; i < 100; ++i) {
        ringServo.write(i);
        delay(5);
    }
    
    
    
    
    setNose(NOSE_CENTER - 10);
     delay(100);
    
    //Go forward for 2/10 of a second
    driveWheels(150, 150);
    delay(350);
    //lastangle = NOSE_CENTER + 3;
    //setNose(NOSE_CENTER-5);
    ringServo.write(0);
}
