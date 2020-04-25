#include <ArduinoJson.h>

class StepMotor
{
public:
	StepMotor(int uid, byte stepPin, byte directionPin, byte enablePin):
		m_uid(uid),
		m_stepPin(stepPin),
		m_directionPin(directionPin),
		m_enablePin(enablePin)
	{
		this->init();
	}

	void makeMove(unsigned long steps, bool direction, int motorDelay)
	{
		// Подаём питание на двигатель
		switchOnStepperMotor();

		// Задаём направление вращения
		setDirection(direction);

		// Выполняем перемещние
		makeSteps(steps, motorDelay, direction);

		// Переходим в режим экономичного удержания двигателя...
		analogWrite(m_enablePin, 100);

		// Ничего не делаем без отключения двигателя
		delay(100);

		// Отключаем двигатель
		switchOffStepperMotor();
	}

private:
	int m_uid;
	byte m_stepPin;
	byte m_directionPin;
	byte m_enablePin;

	void init()
	{
		// Настраиваем нужные контакты на выход
		pinMode(m_stepPin, OUTPUT);
		pinMode(m_directionPin, OUTPUT);
		pinMode(m_enablePin, OUTPUT);
	}

	// Включает ШД
	void switchOnStepperMotor()
	{
		digitalWrite(m_enablePin, HIGH);
	}

	// Выключает ШД 
	void switchOffStepperMotor()
	{
		digitalWrite(m_enablePin, LOW);
	}

	// Задает направление вращения двигателя
	// true == HIGH (против часовой стрелки), false == LOW (по часовой стрелке)
	void setDirection(bool value)
	{
		value ? digitalWrite(m_directionPin, HIGH) : digitalWrite(m_directionPin, LOW);
	}

	// Вращает вал двигателя на указанное число шагов
	void makeSteps(unsigned long stepCount, int motorDelay, bool invertedDirection)
	{

		for (unsigned long i = 0; i < stepCount; ++i)
		{
			// Делаем шаг
			digitalWrite(m_stepPin, HIGH);
			delay(motorDelay);

			digitalWrite(m_stepPin, LOW);
			delay(motorDelay);

			this->sendState(stepCount, i + 1, invertedDirection);
		}
	}

	void sendState(unsigned long task, unsigned long progress, bool invertedDirection)
	{
		unsigned int fieldNamesLength = 55;
		unsigned int jsonMaxLength = (ceil(log10(task)) * 2 + ceil(log10(m_uid + 1)) + fieldNamesLength) * 2;

		DynamicJsonDocument doc(jsonMaxLength);
		doc["motor"] = m_uid;
		doc["isMoving"] = task > progress;
		doc["task"] = task;
		doc["progress"] = progress;
		doc["taskCompleted"] = task <= progress;
		doc["invertedDirection"] = invertedDirection;
		serializeJson(doc, Serial);
	}
};
