#ifndef DEVICE_H
#define DEVICE_H
#include <string>

#include <QMainWindow>

#include "structs.h"
#include "controllerconnector.h"

/**
 * \brief Класс "Устройство"
 * \warning Является базовым классом для всех внешний устройств;
 *
 * Содержит информацио о:
 * 1) Зарезервированном выходе;
 * 2) Имени устройства;
 * 3) Код ошибки, если таковая возникает при работе устройства;
 * 4) Задержки для включения/выключения устройства;
 * 5) Активности устройства;
 * 6) Включено/Выключено устройства;
 */
class Device
{
protected:
    //! Выход, зарезервированный на устройство
    unsigned int output;

    //! Имя устройства
    std::string name;

    //! Пауза для включения устройства
    unsigned int pause;

    //! Активно ли устрйоство;
    bool isActive;

    //! Включено ли устройство;
    bool isOn;

    //! Код ошибки
    unsigned int errorCode;
public:
    Device(unsigned int _output, std::string _name, unsigned int _pause = 1, bool _isActive = true, bool _isOn = false);

    //! Методы для получения и установки значений
    unsigned int getOutput() const;
    void setOutput(unsigned int value);
    std::string getName() const;
    void setName(const std::string &value);
    unsigned int getPause() const;
    void setPause(unsigned int value);
    bool getIsActive() const;
    void setIsActive(bool value);
    bool getIsOn() const;
    void setIsOn(const bool &value);
    unsigned int getErrorCode() const;
    void setErrorCode(const unsigned int &value);

    //! Включает устройство
    virtual void turnOn();

    //! Выключает устройство
    virtual void turnOff();

    //! Отправляет данные о состоянии устройства в модуль взаимодействия с контроллером
    void sendToControllerConnector();

    //! Формирует строку из номера выхода, текущего состояния(включено/выключено) и кода ошибки, содержащую информацию отекущем состоянии устройства;
    virtual std::vector<unsigned int> createArgument();
    //virtual void run();
    //void changeDeviceStatus();

signals:
    //! Сигнал о завершении передачи данных в модуль общения с контроллером
    void ready();
};

#endif // DEVICE_H
