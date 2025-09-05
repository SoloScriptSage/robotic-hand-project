#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>

#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>

#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>

#include <Servo.h>

#include <LiquidCrystal_I2C.h>  // LCD I2C Monitor

#include <RF24.h>               // Modules
#include <RF24_config.h>
#include <nRF24L01.h>

#include <RF24.h>               // Modules just in case
#include <RF24_config.h>
#include <nRF24L01.h>

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


RF24 radio(9, 10);  // CE, CSN

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

Servo Servo0;     // Definition of Servo Motors
Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

void setup() {
  Serial.begin(9600);         // открываем порт для связи с ПК
  radio.begin();              // активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах

  radio.openReadingPipe(1, address[0]);   // хотим слушать трубу 0
  radio.setChannel(0x60);     // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);   // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp();        // начать работу
  radio.startListening(); // начинаем слушать эфир, мы приёмный модуль

  //define the servo input pins
  Servo0.attach(2); //D2
  Servo1.attach(3); //D3
  Servo2.attach(4); //D4
  Servo3.attach(5); //D5
  Servo4.attach(6); //D6
}

int gotByte[5];

void loop() {
  byte pipeNo;
  if (radio.available(&pipeNo)) {        // слушаем эфир со всех труб
    radio.read(&gotByte, sizeof(gotByte));    
    
    Serial.print("Connected: ");
    Serial.print(gotByte[0]);
    Serial.print("\t");
    Serial.print(gotByte[1]);
    Serial.print("\t");
    Serial.print(gotByte[2]);
    Serial.print("\t");
    Serial.print(gotByte[3]);
    Serial.print("\t");
    Serial.print(gotByte[4]);
    Serial.print("\t");
    Serial.println("");
    
    delay(500);
    if(gotByte[0] || gotByte[1] || gotByte[2] || gotByte[3] || gotByte[4]){
      int pos0 = gotByte[0];
      int pos1 = gotByte[1];
      int pos2 = gotByte[2];
      int pos3 = gotByte[3];
      int pos4 = gotByte[4];

      

      radio.stopListening();

      delay(1000);
      Serial.println("1");
      delay(1000);
      Serial.println("2");
      delay(1000);
      Serial.println("3");
      delay(1000);
      Serial.println("Reload...");

      radio.startListening();

    }
  }
}
