#include <SoftwareSerial.h>

#define pino_sensor1 2
#define pino_sensor2 3
#define pino_sensor3 4
#define pino_sensor4 5
#define push_button 12
#define tempo 10
int frequencia = 0;
int Pinofalante = 10;
int fired = 0;

int alarm_mem = 0 ;
SoftwareSerial coreBoard(6,7); //RX/TX


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  coreBoard.begin(9600);
  // Define o pino do sensor como entrada
  pinMode(pino_sensor1, INPUT);//infrared
  pinMode(pino_sensor2, INPUT);
  pinMode(pino_sensor3, INPUT);//infrared
  pinMode(pino_sensor4, INPUT);
  
  pinMode(push_button, INPUT_PULLUP);//botao
  pinMode(LED_BUILTIN, OUTPUT);//led embutido
  pinMode(Pinofalante,OUTPUT); //Pino do buzzer
  //int estado_sensor2 = LOW;
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("-------------INIT--------");
  Serial.println(alarm_mem);
 
  int alarm= digitalRead(push_button);

  int estado_sensor1 = digitalRead(pino_sensor1);
  int estado_sensor2 = digitalRead(pino_sensor2);
  int estado_sensor3 = digitalRead(pino_sensor3);
  int estado_sensor4 = digitalRead(pino_sensor4);
  
  if(alarm == LOW){
    if(alarm_mem == 0){
      alarm_mem = 1;
      Serial.println("-");
      Serial.println("Alarme Ativado");
      Serial.println("-");
      delay(1000);
    }
    else{
      if(alarm_mem == 1){
        alarm_mem = 0;
        Serial.println("-");
        Serial.println("Alarme Desativado");
        Serial.println("-");
        delay(1000);
      }
    }
  }
  else{
    delay(1000);
  }
  
 
  if (alarm_mem == 1)
  {
     if(estado_sensor1 == HIGH || estado_sensor2 == HIGH || estado_sensor3 == HIGH || estado_sensor4 == HIGH){
      fired = 1;
    }  
  }
  else
  {
    fired = 0;    
  }

  if(fired == 1){
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("-");
      Serial.println("Movimento detectado!");
      Serial.println("-");
      for (frequencia = 150; frequencia < 1800; frequencia += 1) 
      {
        tone(Pinofalante, frequencia, tempo); 
        delay(1);
      }
      for (frequencia = 1800; frequencia > 150; frequencia -= 1) 
      {
        tone(Pinofalante, frequencia, tempo); 
        delay(1);
      }
      delay(1000);
  }
  else{
    if(fired = 0){

        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
    }
    
  }
  String strLog;
  strLog = String("{ ");
  strLog += "IRSensor1: ";
  strLog += estado_sensor1;
  strLog += ", ";
  strLog += "IRSensor2: ";
  strLog += estado_sensor2;
  strLog += ", ";
  strLog += "IRSensor3: ";
  strLog += estado_sensor3;
  strLog += ", ";
  strLog += "IRSensor4: ";
  strLog += estado_sensor4;
  strLog += ", ";
  strLog += "AlarmeAtivado: ";
  strLog += alarm_mem;
  strLog += ", " ;
  strLog += "Alerta: ";
  strLog += fired;
  strLog += "} ";
  

  coreBoard.println(strLog);
  

}
