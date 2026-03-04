#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);

const byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

const int FLEX_PINS[5] = {A1, A2, A3, A4, A5};

// TODO: Replace with real values from test_sensors.ino
// Bend each finger flat and fully bent, record the Serial Monitor values
const int FLEX_MIN[5] = {535, 535, 535, 535, 535}; // flat (unflexed)
const int FLEX_MAX[5] = {680, 680, 680, 680, 710}; // fully bent

int msg[5];

void setup() {
    Serial.begin(9600);

    radio.begin();
    radio.setAutoAck(true);
    radio.setRetries(3, 15);
    radio.enableAckPayload();
    radio.setPayloadSize(sizeof(msg));
    radio.openWritingPipe(address[0]);
    radio.setChannel(0x60);
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    radio.powerUp();
    radio.stopListening();
}

void loop() {
    for (int i = 0; i < 5; i++) {
        int raw = analogRead(FLEX_PINS[i]);
        msg[i] = constrain(map(raw, FLEX_MIN[i], FLEX_MAX[i], 1, 180), 1, 180);
    }

    Serial.print("Sensors: ");
    for (int i = 0; i < 5; i++) {
        Serial.print(msg[i]);
        Serial.print("\t");
    }
    Serial.println();

    radio.write(&msg, sizeof(msg));
    delay(50);
}
