#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(9, 10);

const byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

Servo servos[5];
const int SERVO_PINS[5] = {2, 3, 4, 5, 6};

int gotByte[5];

void setup() {
    Serial.begin(9600);

    radio.begin();
    radio.setAutoAck(true);
    radio.setRetries(3, 15);
    radio.enableAckPayload();
    radio.setPayloadSize(sizeof(gotByte));
    radio.openReadingPipe(1, address[0]);
    radio.setChannel(0x60);
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    radio.powerUp();
    radio.startListening();

    for (int i = 0; i < 5; i++) {
        servos[i].attach(SERVO_PINS[i]);
        servos[i].write(90); // center position on startup
    }
}

void loop() {
    byte pipeNo;
    if (radio.available(&pipeNo)) {
        radio.read(&gotByte, sizeof(gotByte));

        Serial.print("Received: ");
        for (int i = 0; i < 5; i++) {
            gotByte[i] = constrain(gotByte[i], 1, 180);
            servos[i].write(gotByte[i]);
            Serial.print(gotByte[i]);
            Serial.print("\t");
        }
        Serial.println();
    }
}
