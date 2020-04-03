#include "servo_motor_utils.h"
#include "receive_buffer.h"

void setup()
{
  setupMotor();
  RECIEVE_BUFFER.init();
}
 
void loop() {
  JsonObject root = RECIEVE_BUFFER.readAsJson();
  if(root.isNull()) return;

  serializeJson(root, Serial);
  Serial.write(" ");
  
  if(!root.containsKey("steps") or !root.containsKey("feedrate")) return;
  double steps = root["steps"];
  Serial.print(steps);
  Serial.write(" ");

  int feedrate = root["feedrate"];
  Serial.print(feedrate);
  Serial.println();
  
  
  
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
