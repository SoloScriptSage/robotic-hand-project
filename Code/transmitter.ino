#include <Servo.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <SPI.h>          // библиотека для работы с шиной SPI
#include "nRF24L01.h"     // библиотека радиомодуля
#include "RF24.h"         // ещё библиотека радиомодуля

RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

int msg[5]; //Total number of data to be sent (data package)

//define the flex sensor input pins
int flex_5 = A5;
int flex_4 = A4;
int flex_3 = A3;
int flex_2 = A2;
int flex_1 = A1;

//define variables for flex sensor values
int flex_5_val;
int flex_4_val;
int flex_3_val;
int flex_2_val;
int flex_1_val;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

void ShowInfo(int arr[]){
  Serial.print("Sensors: ");
  
  Serial.print(msg[0]);
  Serial.print("\t");

  Serial.print(msg[1]);
  Serial.print("\t");

  Serial.print(msg[2]);
  Serial.print("\t");

  Serial.print(msg[3]);
  Serial.print("\t");

  Serial.print(msg[4]);
  Serial.print("\t");

  Serial.println("");

  delay(250);
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

void setup() {
  Serial.begin(9600);         // открываем порт для связи с ПК

  radio.begin();              // активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах

  radio.openWritingPipe(address[0]);  // мы - труба 0, открываем канал для передачи данных
  radio.setChannel(0x60);             // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);   // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  radio.powerUp();        // начать работу
  radio.stopListening();  // не слушаем радиоэфир, мы передатчик

}



void loop() {
  flex_5_val = analogRead(flex_5); 
  flex_5_val = map(flex_5_val, 535, 680, 1, 180);
  
  flex_4_val = analogRead(flex_4);
  flex_4_val = map(flex_4_val, 535, 710, 1, 180);
 
  flex_3_val = analogRead(flex_3);
  flex_3_val = map(flex_3_val, 535, 680, 1, 180);
 
  flex_2_val = analogRead(flex_2);
  flex_2_val = map(flex_2_val, 535, 680, 1, 180);
  
  flex_1_val = analogRead(flex_1);
  flex_1_val = map(flex_1_val, 535, 680, 1, 180);

  if(flex_1_val > 50)
    flex_1_val = 0;
  else flex_1_val = 0;

  if(flex_2_val > 50)
    flex_2_val = 0;
  else flex_2_val = 0;
  
  if(flex_3_val > 50)
    flex_3_val = 0;
  else flex_3_val = 0;
  
  if(flex_4_val > 50)
    flex_4_val = 0;
  else flex_4_val = 0;

  if(flex_5_val > 50)
    flex_5_val = 0;
  else flex_5_val = 0;

  msg[0] = flex_5_val;
  msg[1] = flex_4_val;
  msg[2] = flex_3_val;
  msg[3] = flex_2_val;
  msg[4] = flex_1_val;

  ShowInfo(msg);
  radio.write(&msg, sizeof(msg));
}

