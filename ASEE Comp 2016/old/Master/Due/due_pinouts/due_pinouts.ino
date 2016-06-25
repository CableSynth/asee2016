#include "pinouts.h"
#include <Servo.h>

Servo servo_ring_dispenser_R1;
Servo servo_ring_dispenser_R2;
Servo servo_ring_dispenser_L1;
Servo servo_ring_dispenser_L2;
Servo servo_RING_CHUTE_R;
Servo servo_RING_CHUTE_L;
Servo servo_STEERING_MIDDLE;
int sweep = 0;
bool LED1_value = HIGH;

void setup() {
  // put your setup code here, to run once:

  setPinDirections();

}

void loop() {
  // put your main code here, to run repeatedly:
  if(sweep < 180) {
    sweep++;
  } else {
    sweep = 0;
  }
  delay(20);

  analogWrite(WHEEL_PWM_FR, 75);
  analogWrite(WHEEL_PWM_FL, 25);
  analogWrite(WHEEL_PWM_BL, 175);
  analogWrite(WHEEL_PWM_BR, 50);
  digitalWrite(WHEEL_PWM_R_STBY, LED1_value);
  digitalWrite(WHEEL_PWM_L_STBY, LED1_value);

  
  if(sweep%10==0){LED1_value = !LED1_value;}
  digitalWrite(LED1,LED1_value);
  digitalWrite(LED2, !LED1_value);
    
  
   
   
   digitalWrite(COLOR_SENSOR_R,LED1_value);//Direction is set for debug only, set as output only for testing purposes
   digitalWrite(COLOR_SENSOR_L,LED1_value );//Direction is set for debug only, set as output only for testing purposes
   digitalWrite(LINE_SENSOR_BR, LED1_value);//Direction is set for debug only, set as output only for testing purposes
   digitalWrite(LINE_SENSOR_BL, LED1_value);//Direction is set for debug only, set as output only for testing purposes
   digitalWrite(LINE_SENSOR_BL, LED1_value);//Direction is set for debug only, set as output only for testing purposes
   digitalWrite(WALL_SENSOR_R, LED1_value);//Direction is set for debug only, set as output only for testing purposes
   digitalWrite(WALL_SENSOR_L, LED1_value);//Direction is set for debug only, set as output only for testing purposes
   digitalWrite(GARAGE_SENSOR, LED1_value);//Direction is set for debug only, set as output only for testing purposes

  digitalWrite( LINE_SENSOR_1, LED1_value);//Direction is set for debug only, set as output only for testing purposes    
  digitalWrite( LINE_SENSOR_2, LED1_value );//Direction is set for debug only, set as output only for testing purposes 
  digitalWrite( LINE_SENSOR_3, LED1_value );//Direction is set for debug only, set as output only for testing purposes    
  digitalWrite( LINE_SENSOR_4, LED1_value );//Direction is set for debug only, set as output only for testing purposes          
  digitalWrite( LINE_SENSOR_5, LED1_value );//Direction is set for debug only, set as output only for testing purposes    
  digitalWrite( LINE_SENSOR_6, LED1_value);//Direction is set for debug only, set as output only for testing purposes
  digitalWrite( LINE_SENSOR_7, LED1_value);//Direction is set for debug only, set as output only for testing purposes    
  digitalWrite( LINE_SENSOR_8, LED1_value);//Direction is set for debug only, set as output only for testing purposes        

  digitalWrite( WHEEL_DIR_FR1, LED1_value); 
  digitalWrite( WHEEL_DIR_FR2, LED1_value);        
  digitalWrite( WHEEL_DIR_FL1, LED1_value);  
  digitalWrite( WHEEL_DIR_FL2, LED1_value);      
  digitalWrite( WHEEL_DIR_BR1, LED1_value);      
  digitalWrite( WHEEL_DIR_BR2, LED1_value);          
  digitalWrite( WHEEL_DIR_BL1, LED1_value);      
  digitalWrite( WHEEL_DIR_BL2, LED1_value);      

  //digitalWrite( BUTTON1, HIGH);            
  //digitalWrite( BUTTON2, HIGH);            

  servo_ring_dispenser_R1.write(sweep);
  servo_ring_dispenser_R2.write(sweep);
  servo_ring_dispenser_L1.write(sweep);
  servo_ring_dispenser_L2.write(sweep);
  servo_RING_CHUTE_R.write(sweep);
  servo_RING_CHUTE_L.write(sweep);
  servo_STEERING_MIDDLE.write(sweep);               
       

// analogWrite( BLUETOOTH_TX1,150);         //Note: 3.3V MAX!!
//analogWrite( BLUETOOTH_RX1,50);        //    For any pin
analogWrite( SPEAKER_DAC0 ,100);
analogWrite( SPEAKER_DAC1 ,250);    
//digitalWrite( SPEAKER_DAC1,HIGH);      


}

//Created by Michael Hayes
//This function sets the various pins to 
//either inputs or outputs
void setPinDirections(){
//
//  pinMode(COLOR_SENSOR_R, INPUT);
//  pinMode(COLOR_SENSOR_L, INPUT);
//  pinMode(LINE_SENSOR_BR, INPUT);
//  pinMode(LINE_SENSOR_BL, INPUT);
//  pinMode(WALL_SENSOR_R, INPUT);
//  pinMode(WALL_SENSOR_L, INPUT);
//  pinMode(GARAGE_SENSOR, INPUT);
//  
//  pinMode(LINE_SENSOR_1, INPUT);
//  pinMode(LINE_SENSOR_2, INPUT);
//  pinMode(LINE_SENSOR_3, INPUT);
//  pinMode(LINE_SENSOR_4, INPUT);
//  pinMode(LINE_SENSOR_5, INPUT);
//  pinMode(LINE_SENSOR_6, INPUT);
//  pinMode(LINE_SENSOR_7, INPUT);
//  pinMode(LINE_SENSOR_8, INPUT);


  pinMode(COLOR_SENSOR_R, OUTPUT); //Direction is set for debug only, set as output only for testing purposes 
  pinMode(COLOR_SENSOR_L, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_BR, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_BL, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(WALL_SENSOR_R, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(WALL_SENSOR_L, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(GARAGE_SENSOR, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  
  pinMode(LINE_SENSOR_1, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_2, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_3, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_4, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_5, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_6, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_7, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  pinMode(LINE_SENSOR_8, OUTPUT);//Direction is set for debug only, set as output only for testing purposes
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(WHEEL_DIR_FR1, OUTPUT);
  pinMode(WHEEL_DIR_FR2, OUTPUT);
  pinMode(WHEEL_DIR_FL1, OUTPUT);
  pinMode(WHEEL_DIR_FL2, OUTPUT);
  pinMode(WHEEL_DIR_BR1, OUTPUT);
  pinMode(WHEEL_DIR_BR2, OUTPUT);
  pinMode(WHEEL_DIR_BL1, OUTPUT);
  pinMode(WHEEL_DIR_BL2, OUTPUT);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  servo_ring_dispenser_R1.attach(RING_DISPENSER_R1);
  servo_ring_dispenser_R2.attach(RING_DISPENSER_R2);
  servo_ring_dispenser_L1.attach(RING_DISPENSER_L1);
  servo_ring_dispenser_L2.attach(RING_DISPENSER_L2);
  servo_RING_CHUTE_R.attach(RING_CHUTE_R);
  servo_RING_CHUTE_L.attach(RING_CHUTE_L);
  servo_STEERING_MIDDLE.attach(STEERING_MIDDLE);

  pinMode(STEERING_MIDDLE, OUTPUT);

  pinMode(WHEEL_PWM_FR, OUTPUT);
  pinMode(WHEEL_PWM_FL, OUTPUT);
  pinMode(WHEEL_PWM_BR, OUTPUT);
  pinMode(WHEEL_PWM_BL, OUTPUT);
  pinMode(WHEEL_PWM_R_STBY, OUTPUT);
  pinMode(WHEEL_PWM_L_STBY, OUTPUT);

  pinMode(BLUETOOTH_TX1, OUTPUT);
  pinMode(BLUETOOTH_RX1, INPUT);
  pinMode(SPEAKER_DAC0, OUTPUT);
  pinMode(SPEAKER_DAC1, OUTPUT);
  
}

