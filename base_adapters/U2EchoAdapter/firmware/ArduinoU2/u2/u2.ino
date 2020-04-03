#include "step_motor.h"
#include "receive_buffer.h"

// Troyka-Stepper подключён к следующим пинам:
StepMotor motor(A4, A3, 11);

void setup()
{
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

  motor.makeMove(steps > 0 ? steps : steps * -1, steps > 0, MotorDelay);
}
