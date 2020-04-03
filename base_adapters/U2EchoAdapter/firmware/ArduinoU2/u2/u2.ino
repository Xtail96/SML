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
  
  if(!root.containsKey("steps")) return;
  int steps = root["steps"];
  Serial.print(steps);
  Serial.write(" ");

  if(!root.containsKey("delay")) return;
  int MotorDelay = root["delay"];
  Serial.print(MotorDelay);
  Serial.println();

  // Задаём скорость вращения
  delayTime = MotorDelay;
    
  // Подаём питание на двигатель
  switchOnStepperMotor();

  // Задаём направление вращения
  setDirection(steps > 0);

  // Выполняем перемещние
  makeSteps(steps > 0 ? steps : steps * -1);

  // Переходим в режим экономичного удержания двигателя...
  analogWrite(enablePin, 100);

  // Ничего не делаем без отключения двигателя
  delay(100);

  // Отключаем двигатель
  switchOffStepperMotor();
}
