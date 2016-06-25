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

//*********************TAILS***************************

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
    steeringMotor.write(NOSE_CENTER - 5);

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
    
    pinMode(A8, OUTPUT);
    digitalWrite(A8, HIGH);
    
    while(digitalRead(BUTTON1));//Appears to wait to start the whole thing - Launch
    
    digitalWrite(A8, LOW);
    setNose(NOSE_CENTER + 5); //Drop the nose by turning a little bit left
    delay(250); //wait for the nose to fall down
    for(int i = 0; i < 150; ++i) {
      if(i == 90) {
          driveWheels(255, 255); //Starts driving  
      }
      ringServo.write(i); //swings the ring arm
      delay(4); //don't swing the arm too fast
    }
    //********Is this necessary??
    delay(500); //go blindly straight for half second before starting to steer
}
