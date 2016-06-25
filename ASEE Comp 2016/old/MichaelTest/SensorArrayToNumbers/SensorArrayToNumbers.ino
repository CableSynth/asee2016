#include <Servo.h>

int* convertArrayToNumbers(int a[8]);
Servo steering;

void setup() {
  // put your setup code here, to run once:

     // pinMode(3, OUTPUT);

      steering.attach(3); //attach servo to pin 3

}

void loop() {
  // put your main code here, to run repeatedly:

    steer(convertArrayToNumbers());

}


//function that takes the array of 1 or 0 values from the line 
//sensor and converts them into an array of values  
int* convertArrayToNumbers(int a[8]){

   int output[8];
   
   //loop through values in the input array
   for(int i = 0; i < 8; i++){

      //check the value of the sensor and use a switch to determine the output
      if(a[i] = 1){
        
          switch(i){

              case 0: output[0] = -4; break;
              case 1: output[1] = -3; break;
              case 2: output[2] = -2; break;
              case 3: output[3] = -1; break;
              case 4: output[4] = 1; break;
              case 5: output[5] = 2; break;
              case 6: output[6] = 3; break;
              case 7: output[7] = 4; break; 
                         
          }//end switch
       
      }//end if

      else{

        output[i] = 0; 
               
      }//end else
     
   }//end for

   return output;
  
}//end function

//takes the array with numbers in it
//adds the numbers together and steers with it
void steer(int a[8]){

    int sum = sumArray(a);

    if( sum < 0){

      steering.write(0);
      
    }//end if

    else{

      steering.write(180);
      
    }//end else
  
}//end function

//helper function that sums all the values
//in the array and returns the sum
int sumArray(int a[8]){

    int sum = 0;

    for(int i = 0; i < 8; i++){

        sum += a[i];
      
    }

    return sum;
}







