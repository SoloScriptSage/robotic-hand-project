//    _____       __     _____           _       __  _____                
//   / ___/____  / /___ / ___/__________(_)___  / /_/ ___/____ _____ ____ 
//   \__ \/ __ \/ / __ \\__ \/ ___/ ___/ / __ \/ __/\__ \/ __ `/ __ `/ _ \
//  ___/ / /_/ / / /_/ /__/ / /__/ /  / / /_/ / /_ ___/ / /_/ / /_/ /  __/
// /____/\____/_/\____/____/\___/_/  /_/ .___/\__//____/\__,_/\__, /\___/ 
//                                    /_/                    /____/       

#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int NUM_SENSORS = 5;
int servoPins[NUM_SENSORS] = {3, 5, 6, 9, 10};
Servo servos[NUM_SENSORS];

RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int sensorValues[NUM_SENSORS];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; ++i) {
    servos[i].attach(servoPins[i]);
  }
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(sensorValues, sizeof(sensorValues));
    Serial.print("RX: ");
    for (int i = 0; i < NUM_SENSORS; ++i) {
      int angle = map(sensorValues[i], 300, 600, 0, 180); // вставити свої min/max
      angle = constrain(angle, 0, 180);
      servos[i].write(angle);
      Serial.print(sensorValues[i]);
      Serial.print("->");
      Serial.print(angle);
      Serial.print(" ");
    }
    Serial.println();
  }
  delay(20);
}
