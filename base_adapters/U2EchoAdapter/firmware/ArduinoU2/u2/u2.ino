#include <ArduinoJson.h>
#include "servo_motor_utils.h"
#include "receive_buffer.h"

JsonObject parseJsonFromBuffer();

void setup()
{
  setupMotor();
  RECIEVE_BUFFER.init();
}
 
void loop() {
  RECIEVE_BUFFER.read();
  Serial.write(RECIEVE_BUFFER.m_data);

  if(!RECIEVE_BUFFER.isEmpty())
  {
    JsonObject root = parseJsonFromBuffer();
    serializeJson(root, Serial);
  }

  RECIEVE_BUFFER.clear();
  /*if(stepsCount != 0)
  {
    // нужно пройти некоторое расстояние
    
    // Подаём питание на двигатель
    switchOnStepperMotor();

    // Задаём направление вращения
    setDirection(currentDirection);

    // Выполняем перемещние
    makeSteps(stepsCount);

    //sendLongValueBySerial(stepsCount);
    stepsCount = 0;
    
    // Переходим в режим экономичного удержания двигателя...
    analogWrite(enablePin, 100);

    // Ничего не делаем без отключения двигателя
    delay(100);
 
    // Отключаем двигатель
    switchOffStepperMotor();
  }*/
}

JsonObject parseJsonFromBuffer()
{
  DynamicJsonDocument doc(RECIEVE_BUFFER_SIZE);
  JsonObject root;
  auto error = deserializeJson(doc, RECIEVE_BUFFER.m_data);
  if (error)
  {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
      return root;
  }
  root = doc.as<JsonObject>(); 
  return root;
}
