// Troyka-Stepper подключён к следующим пинам:
const byte stepPin = A4;
const byte directionPin = A3;
const byte enablePin = 11;
 
// Выдержка для регулировки скорости вращения
int delayTime = 20;

long stepsCount = 0;
bool currentDirection = false;

// Включает ШД
void switchOnStepperMotor();

// Выключает ШД 
void switchOffStepperMotor();

// Задает направление вращения двигателя
void setDirection(bool value);

// Вращает вал двигателя на указанное число шагов
void makeSteps(long stepCount);

// Проверяет содержимое буфера обмена последовательного порта
void checkSerialPort();

void sendLongValueBySerial(long value);
 
void setup()
{
  // Настраиваем нужные контакты на выход
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // setup communication via serial port
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}
 
void loop() {
  checkSerialPort();

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

void switchOnStepperMotor()
{
  digitalWrite(enablePin, HIGH);
}

void switchOffStepperMotor()
{
  digitalWrite(enablePin, LOW);
}

// true == HIGH (по часовой стрелке), false == LOW (против часовой стрелки)
void setDirection(bool value)
{
  value ? digitalWrite(directionPin, HIGH) : digitalWrite(directionPin, LOW);
}

void makeSteps(long stepCount)
{
  for (int i = 0; i < stepCount; ++i)
  {
    // Делаем шаг
    digitalWrite(stepPin, HIGH);
    delay(delayTime);
 
    digitalWrite(stepPin, LOW);
    delay(delayTime);
  }
}

// Serial Communication
void checkSerialPort()
{
  //char buffer[];
  //Serial.readBytes(buffer, Serial.available());
  String data = Serial.readString();
  char charVar[sizeof(data)];
  data.toCharArray(charVar, sizeof(charVar));
  
  Serial.write(charVar, data.length());

  
  /*long tmp = 0;
  while (Serial.available()) tmp = tmp * 10 + (Serial.read() - '0');
  stepsCount = tmp;
  currentDirection = ((tmp % 2) == 0);*/
}

void sendLongValueBySerial(long value)
{
  byte result[4];

  result[0] = value & 255;
  result[1] = (value >> 8) & 255;
  result[2] = (value >> 16) & 255;
  result[3] = (value >> 24) & 255;

  Serial.write(result, sizeof(result));
  delay(500);
}
