#ifndef AXIS_H
#define AXIS_H
#include <string>
#include "settingsmanager.h"

class Axis
{
private:
    std::string name;
    double step;
    double length;
    bool invertDirection;
    double jerk;
    double acceleration;
    double velocity;
    int channel;
    double basingVelocity;
public:
    // конструкторы и деструкторы
    Axis(std::string id, double _step = 0, double _length = 1, bool invert = 0, double _jerk = 0, double _acceleration = 0, double _velocity = 0, int _channel = 0, double _basingVelocity = 0);

    // сеттеры и геттеры
    std::string getName() const;
    void setName(const std::string &value);
    double getStep() const;
    void setStep(double value);
    double getLength() const;
    void setLength(double value);
    bool getInvertDirection() const;
    void setInvertDirection(bool value);
    double getJerk() const;
    void setJerk(double value);
    double getAcceleration() const;
    void setAcceleration(double value);
    double getVelocity() const;
    void setVelocity(double value);
    int getChannel() const;
    void setChannel(int value);
    double getBasingVelocity() const;
    void setBasingVelocity(double value);

    // добавить метод настройки оси, путем получения из карты настроек нужных значений
    void setupAxisSettings();


    // методы для установки характеристик осей
    std::string makeKey(const std::string &name, std::string key_string);
    std::string getSettingsElement(std::string key, std::map<std::string, std::string> allSettings);

    void setupAxisAcceleration(const std::string &name, const std::map<std::string, std::string> &allSettings);
    void setupAxisBazaSearchSpeed(const std::string &name, const std::map<std::string, std::string> &allSettings);
    void setupAxisChannel(const std::string &name, const std::map<std::string, std::string> &allSettings);
    void setupAxisJerk(const std::string &name, const std::map<std::string, std::string> &allSettings);
    void setupAxisSpeed(const std::string &name, const std::map<std::string, std::string> &allSettings);
    void setupAxisStep(const std::string &name, const std::map<std::string, std::string> &allSettings);
    void setupAxisInvertStatus(const std::string &name, const std::map<std::string, std::string> &allSettings);
    void setupAxisTableSize(const std::string &name, const std::map<std::string, std::string> &allSettings);
};

#endif // AXIS_H
