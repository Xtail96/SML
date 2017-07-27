#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "models/structs.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"

/*!
 * \brief Класс Датчик
 */
class Sensor
{
private:
    /// имя датчика
    std::string name;

    /// имя платы, к которой подключен датчик
    std::string boardName;

    /// номер порта, ко входу которого подключен датчик
    unsigned int portNumber;

    /// номер входа, к которому подключен датчик
    unsigned int inputNumber;

    bool activeState;

    /// сотояние датчика (включен/выключен)
    bool isEnable;

    QColor color;
public:
    /*!
     * \brief Конструктор класса "Датчик"
     * \param _name -  имя датчика
     * \param _portNumber -  номер порта
     * \param _inputNumber - номер входа
     * \param _isEnable - текущее состояние датчика
     */
    Sensor(std::string _name, std::string _boardName, unsigned int _portNumber, unsigned int _inputNumber, bool _activeState = false, bool _isEnable = false, QColor _color = QColor(0, 125, 0));

    Sensor(std::string _name);

    /*!
     * \brief Получает текущее состояние датчика
     * \return текущее состояние датчика
     */
    bool getIsEnable() const;

    /*!
     * \brief Обновляет текущее состояния датчика, если новое значение НЕ совпадает с текущим
     * \param value - новое состояние датчика
     */
    void setIsEnable(bool value);

    /*!
     * \brief Получает номер порта датчика
     * \return номер порта датчика
     */
    unsigned int getPortNumber() const;

    /*!
     * \brief Получает номер входа датчика
     * \return  номер входа датчика
     */
    unsigned int getInputNumber() const;

    /*!
     * \brief Возвращает имя датчика
     * \return имя датчика
     */
    std::string getName() const;

    std::string getBoardName() const;

    bool getActiveState() const;

    void setup(SettingsManager settingsManager);

    bool isActive();

    QColor getColor() const;
};

#endif // SENSOR_H
