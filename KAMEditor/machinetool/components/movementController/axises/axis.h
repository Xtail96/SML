#ifndef AXIS_H
#define AXIS_H
#include <string>
#include <map>

#include "../../../settingsManager/settingsmanager.h"

/*!
 * \brief Класс "Ось"
 * \brief Данный класс содержит информацию о настройках отдельной оси станка и позволяет взаимодействовать с ней.
 *
 * Способы взаимодействия с классом:
 * 1) Выполнение настройки парметорв оси;
 * 2) Осуществление взаимодействия(получение/установка) отдельных параметров оси;
 */

class Axis
{
private:
    /// \details содержит имя оси в строковом формате, например "X", "Y", "Z";
    std::string name;

    /// \details содержит данные о расстоянии, проходимом за один шаг по текущей оси;
    double step;

    /// \details содержит данные о максимальных перемещениях по текущей оси;
    double length;

    /// \details содержит данные об изменении направления движения по текущей оси;
    bool invertDirection;

    //! Настройки платы KFlop:
    /// \details содержит данные параметра "Рывок" для текущей оси;
    double jerk;

    /// \details содержит данные параметра "Ускорение" для текущей оси;
    double acceleration;

    /// \details содержит данные параметра "Скорость" для текущей оси;
    double velocity;

    /// \details содержит данные параметра "Канал" для текущей оси;
    int channel;

    /// \details содержит данные параметра "Скорость Базирования" для текущей оси;
    double basingVelocity;
public:
    //! Конструктор. Позволяет создавать объект класса Ось
    /// \details Конструктор принимает на вход настройки оси и имеет начальное значение по умолчанию для каждого параметра (если он не был передан);
    Axis(std::string id, double _step = 0, double _length = 1, bool invert = 0, double _jerk = 0, double _acceleration = 0, double _velocity = 0, int _channel = 0, double _basingVelocity = 0);

    ///! Методы получения и установки значений:
    /// \details Возвращает имя текущей Оси;
    std::string getName() const;

    /// \details Устанавливает имя для текущей Оси;
    void setName(const std::string &value);

    /// \details Возвращает расстояние проходимое за один шаг по текущей оси;
    double getStep() const;

    /// \details Устанавливает значение расстояние, проходимого за один шаг по текущей оси;
    void setStep(double value);

    /// \details Возвращает длину текущей оси;
    double getLength() const;

    /// \details Устанавливает длину текущей оси;
    void setLength(double value);

    /// \details Возвращает статус смены направления движения по текущей оси (Прямое/Обратное);
    bool getInvertDirection() const;

    /// \details Устанавливает направление движения по текущей оси (Прямое/Обратное);
    void setInvertDirection(bool value);

    /// \details Возвращает значение параметра "Рывок" для текущей оси;
    double getJerk() const;

    /// \details Устанавливает значение параметра "Рывок" для текущей оси;
    void setJerk(double value);

    /// \details Возвращает значение параметра "Ускорение" для текущей оси;
    double getAcceleration() const;

    /// \details Устанавливает значение параметра "Ускорение" для текущей оси;
    void setAcceleration(double value);

    /// \details Возвращает значение параметра "Скорость" для текущей оси;
    double getVelocity() const;

    /// \details Устанавливает значение параметра "Скорость" для текущей оси;
    void setVelocity(double value);

    /// \details Возвращает значение параметра "Канал" для текущей оси;
    int getChannel() const;

    /// \details Устанавливает значение параметра "Канал" для текущей оси;
    void setChannel(int value);

    /// \details Возвращает значение парметра "Скорость Базирования" для текущей оси;
    double getBasingVelocity() const;

    /// \details Устанавливает значение параметра "Скорость Базирования" для текущей оси;
    void setBasingVelocity(double value);

    //! Методы для настройки параметров Оси:
    /// \brief Метод комплексной настройки параметров текущей оси;
    /// @param settings ссылка на менеджер настроек, который будет производить настройку
    void setup(const SettingsManager &settings);
};

#endif // AXIS_H
