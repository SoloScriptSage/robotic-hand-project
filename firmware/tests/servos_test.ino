#include <Servo.h>

Servo servo1; 
Servo servo2; 
Servo servo3; 
Servo servo4; 
Servo servo5; 

void setup() {
  servo1.attach(A0);
  servo2.attach(A1);
  servo3.attach(A2);
  servo4.attach(A3);
  servo5.attach(A4);
}

void loop() {
  for (int pos = 0; pos <= 180; pos += 1) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
    servo5.write(pos);
    delay(15);
  }

  for (int pos = 180; pos >= 0; pos -= 1) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
    servo5.write(pos);
    delay(15);
  }
}
