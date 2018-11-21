#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial secBoard(8,2); // RX/TX Arduino Seguranca
SoftwareSerial coolIlumiBoard(9,3);// RX/TX Arduino Refrigeracao e Iluminacao
SoftwareSerial hydroBoard(10,4);// RX/TX Arduino Hidraulica

int id = 0;

void setup() {
  
  Serial.begin(9600);// Inicializa comunicacao USB
  secBoard.begin(9600);// Inicializa comunicacao
  coolIlumiBoard.begin(9600);// Inicializa comunicacao
  hydroBoard.begin(9600);// Inicializa comunicacao
  
}

void loop() {
  id = id++;
  DynamicJsonBuffer jb(1024);
  DynamicJsonBuffer jbnested(256);
  
  JsonObject& root = jb.createObject();
  root["log"] = id;
  root["secjson"] = jbnested.parseObject(secBoard);
  jbnested.clear();
  root["cooljson"] = jbnested.parseObject(coolIlumiBoard);
  jbnested.clear();
  root["hydrojson"] = jbnested.parseObject(hydroBoard);
  jbnested.clear();
  root.printTo(Serial);
}
