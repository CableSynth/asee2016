#include <Servo.h>
#include "LineSensor.h"


//servo pins
int const steering = 3;
Servo steeringMotor;

//had problems with pin 10 on practice arduino

int const backLeftPWM = 11;
int const backLeftIn1 = 14;
int const backLeftIn2 = 15;
int const STBY = 16;

//line sensor
//the array is the pins L3, L2 ... R2, R3
LineSensor lineSensor( new int [8] {4, 5, 6, 7, 8, 9, 2, 12} );
int* lineData = new int [8];


void setup() {
    // put your setup code here, to run once:

    steeringMotor.attach(3); //attach servo to pin 3
    
    pinMode(backLeftIn1, OUTPUT);
    pinMode(backLeftIn2, OUTPUT);
    pinMode(STBY, OUTPUT);
  
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    lineSensor.update();

    //getSensorData(lineData, lineSensorPins, 8);
    
    lineSensor.getCurrent(lineData);

    steer(lineData, steeringMotor);

    analogWrite(backLeftPWM,128);
    digitalWrite(backLeftIn1, 1);
    digitalWrite(backLeftIn2, 0);
    digitalWrite(STBY,1);

    for (int i = 0; i < 8; ++i) {
      Serial.print(lineData[i]);
    }

    Serial.println(' ');

}





/**
 * This function moves a servo to an angle between -100 and 100. 
 * -100 is all the way to the left and 100 is all the way to the right.
 * This function limits the input to the [-100, 100] range.
 * 
 * @author Blake Lasky
 * 
 * @param angle the angle to set 
 * 
 * @return returns whether or not there was at least one true value
 */
/*void setServo (int angle, Servo motor ) {

	// make sure angle is within valid range
	if (angle < -100) {
		angle = -100;
	} else if (angle > 100) {
		angle = 100;
	}
	
	int scaledAngle = ( (angle * 9) / 10 ) + 90;

	motor.write(angle);
	
	return;
}*/


/**
 * This function moves a servo to an angle between -100 and 100. 
 * -100 is all the way to the left and 100 is all the way to the right.
 * This function limits the input to the [-100, 100] range.
 * 
 * @author Blake Lasky
 * 
 * @param angle the angle to set 
 * 
 * @return returns whether or not there was at least one true value
 */
void moveServo (int delta, Servo motor ) {    

    int angle = delta + motor.read();
    if (angle < 45) {
        angle = 45;
    } else if (angle > 135) {
        angle = 135;
    }   

    motor.write(angle);

    Serial.println(angle);
    
    return;
}



//function that takes the array of 1 or 0 values from the line 
//sensor and converts them into an array of values  
void convertArrayToNumbers(int a []){
   
   
	a[0] *= 4;
	a[1] *= 3;
	a[2] *= 2;
	a[3] *= 0;
	a[4] *= 0;
	a[5] *= -2;
	a[6] *= -3;
	a[7] *= -4;
  
}

//takes the array with numbers in it
//adds the numbers together and steers with it
void steer(int data[8], Servo motor){

	convertArrayToNumbers(data);
    int sum = sumArray(data);
	
	sum *=1;
	
	moveServo(sum, motor);
	
	return;
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

int milimetersToDegrees (int distance, int radius) {
    return 360 * distance / (PI * 2 * radius);
}
