#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// NRF24L01 setup
RF24 radio(9, 10); // CE, CSN pins for Uno
byte address[6] = "1Node"; // Communication channel

int msg[5]; // Data package to send

// Flex sensor input pins
int flexPins[5] = {A1, A2, A3, A4, A5};
int flexVals[5];

// Helper function to display sensor data
void ShowInfo(int arr[]) {
  Serial.print("Sensors: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(arr[i]);
    Serial.print("\t");
  }
  Serial.println("");
  delay(250);
}

void setup() {
  Serial.begin(9600); // Serial port for debugging
  radio.begin();
  radio.setAutoAck(1);        
  radio.setRetries(0, 15);    
  radio.enableAckPayload();   
  radio.setPayloadSize(32);   

  radio.openWritingPipe(address);  // Channel for data transmission
  radio.setChannel(0x60);          
  radio.setPALevel(RF24_PA_MAX);   
  radio.setDataRate(RF24_250KBPS); 
  radio.stopListening();           // We are transmitter
}

void loop() {
  for (int i = 0; i < 5; i++) {
    flexVals[i] = analogRead(flexPins[i]);
    flexVals[i] = map(flexVals[i], 535, 680, 1, 180);
    
    // Optional threshold (if needed):
    if (flexVals[i] > 50) {
      flexVals[i] = 0;
    }
  }

  for (int i = 0; i < 5; i++) {
    msg[i] = flexVals[i];
  }

  ShowInfo(msg); // Display the data
  radio.write(&msg, sizeof(msg)); // Send data over NRF24L01
}
