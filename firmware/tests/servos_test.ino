#include <Servo.h>

Servo servos[5];
const int SERVO_PINS[5] = {2, 3, 4, 5, 6};

void setup() {
    for (int i = 0; i < 5; i++) {
        servos[i].attach(SERVO_PINS[i]);
    }
}

void loop() {
    for (int pos = 0; pos <= 180; pos++) {
        for (int i = 0; i < 5; i++) servos[i].write(pos);
        delay(15);
    }
    for (int pos = 180; pos >= 0; pos--) {
        for (int i = 0; i < 5; i++) servos[i].write(pos);
        delay(15);
    }
}
