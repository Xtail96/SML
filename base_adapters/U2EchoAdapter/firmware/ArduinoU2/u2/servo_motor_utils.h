// Troyka-Stepper подключён к следующим пинам:
const byte stepPin = A4;
const byte directionPin = A3;
const byte enablePin = 11;
 
// Выдержка для регулировки скорости вращения
int delayTime = 20;

long stepsCount = 0;
bool currentDirection = false;

void setupMotor()
{
	// Настраиваем нужные контакты на выход
	pinMode(stepPin, OUTPUT);
	pinMode(directionPin, OUTPUT);
	pinMode(enablePin, OUTPUT);
}

// Включает ШД
void switchOnStepperMotor()
{
	digitalWrite(enablePin, HIGH);
}

// Выключает ШД 
void switchOffStepperMotor()
{
	digitalWrite(enablePin, LOW);
}

// Задает направление вращения двигателя
// true == HIGH (по часовой стрелке), false == LOW (против часовой стрелки)
void setDirection(bool value)
{
	value ? digitalWrite(directionPin, HIGH) : digitalWrite(directionPin, LOW);
}

// Вращает вал двигателя на указанное число шагов
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