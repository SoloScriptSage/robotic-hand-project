#include <Arduino.h>

const int flex_5 = A5;  // Finger 5
const int flex_4 = A4;  // Finger 4
const int flex_3 = A3;  // Finger 3
const int flex_2 = A2;  // Finger 2
const int flex_1 = A1;  // Finger 1

void setup() {
  Serial.begin(9600); 
}

void loop() {
  int flex_5_val = analogRead(flex_5);
  int flex_4_val = analogRead(flex_4);
  int flex_3_val = analogRead(flex_3);
  int flex_2_val = analogRead(flex_2);
  int flex_1_val = analogRead(flex_1);

  Serial.print("Sensors: ");

  Serial.print(flex_1_val);
  Serial.print("\t");

  Serial.print(flex_2_val);
  Serial.print("\t");

  Serial.print(flex_3_val);
  Serial.print("\t");


  Serial.print(flex_4_val);
  Serial.print("\t");


  Serial.print(flex_5_val);
  Serial.println("");

  delay(500);
}
