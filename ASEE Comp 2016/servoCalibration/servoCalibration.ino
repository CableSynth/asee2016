#include <Servo.h>
#define prt Serial
Servo steeringMotor;
int serial_temp;

void setup() {
   steeringMotor.attach(9);
   prt.begin(115200);
 
} 

void loop() {
     
     while(true) {
        if(prt.available() > 2) {
            serial_temp = prt.read()-'0';
            serial_temp = serial_temp * 10 + prt.read()-'0';
            serial_temp = serial_temp * 10 + prt.read()-'0';
            prt.println(serial_temp);
            steeringMotor.write(serial_temp);
        }
    }
}
