#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// NRF24L01 setup
RF24 radio(9, 10); // CE, CSN pins for Uno
byte address[6] = "1Node"; // Communication channel

Servo servos[5]; // Servo motor objects
int servoPins[5] = {2, 3, 4, 5, 6}; // Servo pins

int gotByte[5]; // Data package to receive

void setup() {
  Serial.begin(9600); // Serial port for debugging
  radio.begin();
  radio.setAutoAck(1);        
  radio.setRetries(0, 15);    
  radio.enableAckPayload();   
  radio.setPayloadSize(32);   

  radio.openReadingPipe(1, address);  // Channel for data reception
  radio.setChannel(0x60);             
  radio.setPALevel(RF24_PA_MAX);      
  radio.setDataRate(RF24_250KBPS);    
  radio.startListening();             // We are receiver

  // Attach servo motors
  for (int i = 0; i < 5; i++) {
    servos[i].attach(servoPins[i]);
  }
}

void loop() {
  if (radio.available()) { // Check if data is available
    radio.read(&gotByte, sizeof(gotByte));

    Serial.print("Received: ");
    for (int i = 0; i < 5; i++) {
      Serial.print(gotByte[i]);
      Serial.print("\t");
    }
    Serial.println("");

    // Update servos with received data
    for (int i = 0; i < 5; i++) {
      servos[i].write(gotByte[i]);
    }

    delay(100); // Small delay for smoother operation
  }
}
