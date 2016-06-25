#include <Servo.h>
#include "LineSensor.h"


//servo pins
int const steering = 3;
Servo steeringMotor;

const int noseLength = 120;

//had problems with pin 10 on practice arduino
//left motors A
//right motors B
//
int const backLeftPWM = 11; //A PWM
int const backLeftIn1 = 14; //A In1
int const backLeftIn2 = 15; //A In2

int const backRightPWM = 3; //B PWM
int const backRightIn1 = 17; //B In1
int const backRightIn2 = 18; //B In2

int const boardLED = 13; 
int const STBY = 16;  // 

//line sensor
//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor( new int [8] {2, 4, 19, 6, 7, 8, 9, 12} );
int* lineData = new int [8];


void setup() {
    // put your setup code here, to run once:

    steeringMotor.attach(5); //attach servo to pin 19
    
    //Left Motor
    pinMode(backLeftIn1, OUTPUT);
    pinMode(backLeftIn2, OUTPUT);
    pinMode(STBY, OUTPUT);

    //Right Motor
    pinMode(backRightIn1, OUTPUT);
    pinMode(backRightIn2, OUTPUT);
  
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    lineSensor.update();

    //getSensorData(lineData, lineSensorPins, 8);
    
    if(lineSensor.hasOneTrue()) {
      lineSensor.getCurrent(lineData);
    } else {
      lineSensor.getLastSeen(lineData);
    }

    steer(lineData, steeringMotor);
    digitalWrite(backLeftIn1, 0);
    digitalWrite(backLeftIn2, 1);
    digitalWrite(STBY,1);

    digitalWrite(backRightIn1, 1);
    digitalWrite(backRightIn2, 0);

    for (int i = 0; i < 8; ++i) {
      Serial.print(lineData[i]);
    }

    Serial.println(' ');

}

//takes the array with numbers in it
//adds the numbers together and steers with it
void steer(int data[8], Servo motor){

 convertArrayToNumbers(data);
  int sum = sumArray(data);

  sum = toDegrees(sum, noseLength)/8;
  
  moveServo(sum, motor);
  
  return;
}

void moveServo (int delta, Servo motor ) {    

    Serial.println(delta);
    int angle = delta + motor.read();
    if (angle < 50) {
        angle = 50;
    } else if (angle > 120) {
        angle = 120;
    }   

    double rads = angle * 0.0174533;
    int leftSpeed = 130, rightSpeed = 130;

    leftSpeed *= .3 + ((double)(angle-50)/100);

    rightSpeed *= .3 + ((double)(120-angle)/100);
    
    analogWrite(backLeftPWM, leftSpeed);

    analogWrite(backRightPWM, rightSpeed);

    motor.write(angle);

    Serial.println(angle);
    
    return;
}



//function that takes the array of 1 or 0 values from the line 
//sensor and converts them into an array of values  
void convertArrayToNumbers(int a []){
   
   
  a[0] *= -33;
  a[1] *= 24;
  a[2] *= -14;
  a[3] *= -9;
  a[4] *= 9;
  a[5] *= 14;
  a[6] *= 24;
  a[7] *= 33;
  
}

//helper function that sums all the values
//in the array and returns the sum
int sumArray(int a[8]){

    int sum = 0;

    for(int i = 0; i < 8; i++){
        sum += a[i];      
    }

    return sum;
}

int toDegrees (int distance, int radius) {
    return 360 * distance / (PI * 2 * radius);
}
