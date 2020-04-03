class StepMotor
{
public:
	StepMotor(byte stepPin, byte directionPin, byte enablePin) :
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
		makeSteps(steps, motorDelay);

		// Переходим в режим экономичного удержания двигателя...
		analogWrite(m_enablePin, 100);

		// Ничего не делаем без отключения двигателя
		delay(100);

		// Отключаем двигатель
		switchOffStepperMotor();
	}

private:
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
	// true == HIGH (по часовой стрелке), false == LOW (против часовой стрелки)
	void setDirection(bool value)
	{
		value ? digitalWrite(m_directionPin, HIGH) : digitalWrite(m_directionPin, LOW);
	}

	// Вращает вал двигателя на указанное число шагов
	void makeSteps(unsigned long stepCount, int motorDelay)
	{
		for (unsigned long i = 0; i < stepCount; ++i)
		{
			// Делаем шаг
			digitalWrite(m_stepPin, HIGH);
			delay(motorDelay);

			digitalWrite(m_stepPin, LOW);
			delay(motorDelay);
		}
	}
};
