#ifndef AXIS_H
#define AXIS_H
#include <string>
#include "settingsmanager.h"

/*!
 * \brief Класс "Ось"
 * \brief Данный класс содержит информацию о настройках отдельной оси станка и позволяет взаимодействовать с ней.
 *
 * Способы взаимодействия с классом:
 * 1) Добавление новой оси;
 * 2) Выполнение комплексной или частичной настройки парметорв оси;
 * 3) Осуществление взаимодействия(получени/установка) с параметрами оси;
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
    /**
     * Связывается с модулем "Settings Manager";
     * Получает от него карту настроек станка;
     * Вызывает методы настройки каждого из параметра оси;
     */
    void setupAxisSettings();

    //! Метод для получения значения элемента по ключу из карты настроек
    std::string getSettingsElement(std::string key, std::map<std::string, std::string> allSettings);

    /// \details Метод для настройки параметра "Ускорение";
    void setupAxisAcceleration(const std::string &name, const std::map<std::string, std::string> &allSettings);

    /// \details Метод для настройки параметра "Скорость Базирования";
    void setupAxisBazaSearchSpeed(const std::string &name, const std::map<std::string, std::string> &allSettings);

    /// \details Метод для настройки параметра "Канал";
    void setupAxisChannel(const std::string &name, const std::map<std::string, std::string> &allSettings);

    /// \details Метод для настройки параметра "Рывок";
    void setupAxisJerk(const std::string &name, const std::map<std::string, std::string> &allSettings);

    /// \details Метод для настройки параметра "Скорость";
    void setupAxisSpeed(const std::string &name, const std::map<std::string, std::string> &allSettings);

    /// \details Метод для настройки расстояния, проходимого за 1 шаг
    void setupAxisStep(const std::string &name, const std::map<std::string, std::string> &allSettings);

    /// \details Метод для настройки направления движения по оси;
    void setupAxisInvertStatus(const std::string &name, const std::map<std::string, std::string> &allSettings);

    /// \details Метод настройки габаритов перемещения по оси;
    void setupAxisTableSize(const std::string &name, const std::map<std::string, std::string> &allSettings);
};

#endif // AXIS_H
