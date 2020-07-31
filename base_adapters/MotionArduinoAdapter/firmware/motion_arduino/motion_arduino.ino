#include "step_motor.h"
#include "receive_buffer.h"

// Команда на перемещение двигателя на 100 шагов
// с задержкой между ними в 6 милисекунд:
// {"steps":100, "delay":6}

// Troyka-Stepper подключён к следующим пинам:
StepMotor motor(0, A4, A3, 11);

void setup()
{
  RECIEVE_BUFFER.init();
}
 
void loop() {
  JsonObject root = RECIEVE_BUFFER.readAsJson();
  if(root.isNull()) return;

  //serializeJson(root, Serial);
  //Serial.write(" ");
  
  if(!root.containsKey("steps")) return;
  int steps = root["steps"];
  //Serial.print(steps);
  //Serial.write(" ");

  if(!root.containsKey("delay")) return;
  int MotorDelay = root["delay"];
  //Serial.print(MotorDelay);
  //Serial.println();

  motor.makeMove(steps > 0 ? steps : steps * -1, steps < 0, MotorDelay);
}
