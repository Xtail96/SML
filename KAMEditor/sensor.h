#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include <QSensor>

class Sensor
{
protected:
    unsigned int id;
    std::string name;
    bool isActive;
    bool isStateChanged;

    bool isEnabled;
    bool isDebugActive;

    bool buffer;
public:
    Sensor(unsigned int _id, std::string _name, bool _isEnabled);

    //! Методы получения и установки значений
    bool getIsActive() const;
    void setIsActive(bool value);
    bool getIsStateChanged() const;
    void setIsStateChanged(bool value);
    std::string getName() const;
    void setName(const std::string &value);
    unsigned int getId() const;
    void setId(unsigned int value);

    void setBuffer(const bool &value);

    bool getIsEnabled() const;
    void setIsEnabled(bool value);

private slots:
    bool update();
};

#endif // SENSOR_H
