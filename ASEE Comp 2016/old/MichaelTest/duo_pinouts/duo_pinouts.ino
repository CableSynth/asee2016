#include "pinouts.h"

void setup() {
  // put your setup code here, to run once:

  setPinDirections();

}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(WHEEL_PWM_FR, 75);
  analogWrite(WHEEL_PWM_FL, 25);
   analogWrite(WHEEL_PWM_BL, 175);
  analogWrite(WHEEL_PWM_BR, 50);

  
  digitalWrite(LED1,HIGH);  
  digitalWrite(LED2,LOW);  
   analogWrite(COLOR_SENSOR_R,50);
   analogWrite(COLOR_SENSOR_L,10 );
   analogWrite(LINE_SENSOR_BR, 20);
   analogWrite(LINE_SENSOR_BL, 40);
   analogWrite(LINE_SENSOR_BL, 60);
   analogWrite(WALL_SENSOR_R, 80);
   analogWrite(WALL_SENSOR_L, 100);
   analogWrite(GARAGE_SENSOR, 120);

  digitalWrite( LINE_SENSOR_1, HIGH);    
  digitalWrite( LINE_SENSOR_2, LOW ); 
  digitalWrite( LINE_SENSOR_3, HIGH );    
  digitalWrite( LINE_SENSOR_4, LOW );          
  digitalWrite( LINE_SENSOR_5, HIGH );    
  digitalWrite( LINE_SENSOR_6, LOW);
  digitalWrite( LINE_SENSOR_7, HIGH);    
  digitalWrite( LINE_SENSOR_8, LOW );        

  digitalWrite( WHEEL_DIR_FR1, HIGH); 
  digitalWrite( WHEEL_DIR_FR2, HIGH);        
  digitalWrite( WHEEL_DIR_FL1, HIGH);  
  digitalWrite( WHEEL_DIR_FL2, HIGH);      
  digitalWrite( WHEEL_DIR_BR1, HIGH);      
  digitalWrite( WHEEL_DIR_BR2, HIGH);          
  digitalWrite( WHEEL_DIR_BL1, HIGH);      
  digitalWrite( WHEEL_DIR_BL2, HIGH);      

  digitalWrite( BUTTON1, HIGH);            
  digitalWrite( BUTTON2, HIGH);            

 analogWrite( RING_DISPENSER_R1, 20);            
 analogWrite( RING_DISPENSER_R2,40);            
 analogWrite( RING_DISPENSER_L1,60);            
 analogWrite( RING_DISPENSER_L2, 80);            
 analogWrite( RING_CHUTE_R,100);                  
 analogWrite( RING_CHUTE_L,120);                 
 analogWrite( STEERING_MIDDLE,160);               
       

// analogWrite( BLUETOOTH_TX1,150);         //Note: 3.3V MAX!!
//analogWrite( BLUETOOTH_RX1,50);        //    For any pin
// analogWrite( SPEAKER_DAC0 ,100);    
// digitalWrite( SPEAKER_DAC1,HIGH);      


}

//Created by Michael Hayes
//This function sets the various pins to 
//either inputs or outputs
void setPinDirections(){

  //pinMode(COLOR_SENSOR_R, INPUT);
  //pinMode(COLOR_SENSOR_L, INPUT);
  pinMode(LINE_SENSOR_BR, INPUT);
  pinMode(LINE_SENSOR_BL, INPUT);
  pinMode(WALL_SENSOR_R, INPUT);
  pinMode(WALL_SENSOR_L, INPUT);
  pinMode(GARAGE_SENSOR, INPUT);
  
  pinMode(LINE_SENSOR_1, INPUT);
  pinMode(LINE_SENSOR_2, INPUT);
  pinMode(LINE_SENSOR_3, INPUT);
  pinMode(LINE_SENSOR_4, INPUT);
  pinMode(LINE_SENSOR_5, INPUT);
  pinMode(LINE_SENSOR_6, INPUT);
  pinMode(LINE_SENSOR_7, INPUT);
  pinMode(LINE_SENSOR_8, INPUT);
  
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

  //pinMode(BUTTON1, INPUT);
  //pinMode(BUTTON2, INPUT);

  //pinMode(RING_DISPENSER_R1, OUTPUT);
  //pinMode(RING_DISPENSER_R2, OUTPUT);
  //pinMode(RING_DISPENSER_L1, OUTPUT);
  //pinMode(RING_DISPENSER_L2, OUTPUT);
  //pinMode(RING_CHUTE_R, OUTPUT);
  //pinMode(RING_CHUTE_L, OUTPUT);

  pinMode(STEERING_MIDDLE, OUTPUT);

  //pinMode(WHEEL_PWM_FR, OUTPUT);
  pinMode(WHEEL_PWM_FL, OUTPUT);
  pinMode(WHEEL_PWM_BR, OUTPUT);
  pinMode(WHEEL_PWM_BL, OUTPUT);

  pinMode(BLUETOOTH_TX1, OUTPUT);
  pinMode(BLUETOOTH_RX1, INPUT);
  pinMode(SPEAKER_DAC0, OUTPUT);
  pinMode(SPEAKER_DAC1, OUTPUT);
  
}

