//    _____       __     _____           _       __  _____                
//   / ___/____  / /___ / ___/__________(_)___  / /_/ ___/____ _____ ____ 
//   \__ \/ __ \/ / __ \\__ \/ ___/ ___/ / __ \/ __/\__ \/ __ `/ __ `/ _ \
//  ___/ / /_/ / / /_/ /__/ / /__/ /  / / /_/ / /_ ___/ / /_/ / /_/ /  __/
// /____/\____/_/\____/____/\___/_/  /_/ .___/\__//____/\__,_/\__, /\___/ 
//                                    /_/                    /____/       

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int NUM_SENSORS = 5;
const int flexPins[NUM_SENSORS] = {A0, A1, A2, A3, A4};

RF24 radio(9, 10);  // CE, CSN pin
const uint64_t pipe = 0xE8E8F0F0E1LL;

int sensorValues[NUM_SENSORS];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_HIGH); // or Min, depends from the distance
  radio.stopListening();
}

void loop() {
  for (int i = 0; i < NUM_SENSORS; ++i) {
    sensorValues[i] = analogRead(flexPins[i]);
  }
  radio.write(sensorValues, sizeof(sensorValues));
  Serial.print("TX: ");
  for (int i = 0; i < NUM_SENSORS; ++i) {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(50); // 20 recieves per sec
}
