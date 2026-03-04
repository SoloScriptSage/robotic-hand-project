const int FLEX_PINS[5] = {A1, A2, A3, A4, A5};

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.print("F1:"); Serial.print(analogRead(FLEX_PINS[0])); Serial.print("\t");
    Serial.print("F2:"); Serial.print(analogRead(FLEX_PINS[1])); Serial.print("\t");
    Serial.print("F3:"); Serial.print(analogRead(FLEX_PINS[2])); Serial.print("\t");
    Serial.print("F4:"); Serial.print(analogRead(FLEX_PINS[3])); Serial.print("\t");
    Serial.print("F5:"); Serial.print(analogRead(FLEX_PINS[4])); Serial.println();
    delay(500);
}
