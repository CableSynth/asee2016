#include <Servo.h>

//servo pins
int const steering = 3;
Servo steeringMotor;

//line sensor input pins
int const L3 =  4;
int const L2 =  5;
int const L1 =  6;
int const L0 =  7;
int const R0 =  8;
int const R1 =  9;
int const R2 = 10;
int const R3 = 11;
int const lineSensorPins[8] = {L3, L2, L1, L0, R0, R1, R2, R3};

//store data from each optical sensor
int lineData [] = {0, 0, 0, 0, 0, 0, 0, 0};
int lineDataLastSeen [] = {0, 0, 0, 0, 0, 0, 0, 0};


void setup() {

  for (int i = 0; i < 8; ++i) {
    pinMode(lineSensorPins[i], INPUT);
  }

  steeringMotor.attach(3); //attach servo to pin 3

  Serial.begin(9600);
}

void loop() {

  //updateSensorData(lineData, lineDataLastSeen, lineSensorPins, 8);

  getSensorData(lineData, lineSensorPins, 8);

  //steer(convertArrayToNumbers(lineData));

  for (int i = 0; i < 8; ++i) {
    Serial.print(lineData[i]);
  }

  Serial.println(' ');
}


/**
* This function reads pins from pinSpots into array lineData of size arraySize.
* 
* @author Blake Lasky
* @param lineData is an array which will be overidden with new data
* @param pinSpots stores the pin numbers to read data in to put in lineData
* @param arraySize stores the size of the other arrays; defaults to 8
*/
void getSensorData(int* lineData, int* pinSpots, int arraySize) {\

  for (int i = 0; i < arraySize; ++i) {      
    lineData[i] = digitalRead( pinSpots[i] );             
  }

  return;
}


/**
* This function updates the arrays current and lastSeen. 
* lastSeen will only be overwritten iff current has at least one true.
* 
* @author Blake Lasky
* @param current current line data array
* @param lastSeen reading data from last time we got at least one true reading
* @param pinSpots pins corresponding to the previous two data arrays
* @param arraySize size of the previous three arrays
*/
void updateSensorData (int current[], int lastSeen[], int pinSpots[], int arraySize) {
  
  int temp [8];

  getSensorData(temp, pinSpots, 8);

  if ( hasTrue(current, 8) ) { 
  // shifts data from current to lastSeen and from temp to current
    for (int i = 0; i < 8; ++i) {
      lastSeen[i] = current[i];
      current[i] = temp[i];
    }    

  } else { 
    //overwrites current with temp; does not affect lastSeen
    for (int i = 0; i < 8; ++i) {
      current[i] = temp[i];
    }     

  }


}

/**
* This function takes an array and check to make sure it has at least one true value

* @author Blake Lasky
* @param array the array to iterate through and check for a true value
* @param arraySize size of the array passed in
* @return returns whether or not there was at least one true value
*/
bool hasTrue (int const array[], int arraySize) {

  for (int i = 0; i < arraySize; ++i) {
    if (array[i]) {
      return true;
    }
  }

  return false;
}



//function that takes the array of 1 or 0 values from the line 
//sensor and converts them into an array of values  
void scaleLineSensor(int a []){

  a[0] *= -4;
  a[1] *= -3;
  a[2] *= -2;
  a[3] *= -1;
  a[4] *= 1;
  a[5] *= 2;
  a[6] *= 3;
  a[7] *= 4;

}

//takes the array with numbers in it
//adds the numbers together and steers with it
void steer (int a[8]) {

  int sum = sumArray(a);

  if ( sum < 0) {
    steeringMotor.write(0);
  } else {
    steeringMotor.write(180);
  }

}//end function

//helper function that sums all the values
//in the array and returns the sum

/**
 * This function takes an array and returns the sum of all the values in the array
 * 
 * @author Micahel Hayes
 * 
 * @param array the array to iterate through and sum the values
 * @param arraySize size of the array passed in
 * 
 * @return returns the sum of the array
 */
int sumArray(int* array, int arraySize) {

  int sum = 0;

  for(int i = 0; i < 8; ++i) {
    sum += array[i];
  }

  return sum;
}