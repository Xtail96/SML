#ifndef SENSOR_H
#define SENSOR_H

#include <QString>
#include <QDebug>
#include <QColor>

/**
 * @brief Класс Датчик
 */
class Sensor
{
public:
    Sensor(QString id,
           bool activeState,
           bool currentState,
           QString label = "",
           QColor ledColor = QColor("green"));
    bool operator<(const Sensor &sensor) const;
    bool operator>(const Sensor &sensor) const;
    bool operator<=(const Sensor &sensor) const;
    bool operator>=(const Sensor &sensor) const;
    bool operator==(const Sensor &sensor) const;
    bool currentState() const;
    QString id() const;
    bool activeState() const;
    QColor ledColor() const;
    QString label() const;
    bool isEnabled();
private:
    /// Уникальный идентификатор (имя) датчика
    QString m_id;

    /// Пользовательское имя датчика
    QString m_label;

    /// Состояние входа, при котором датчик считается активным
    bool m_activeState;

    /**
     * @brief Текущее сотояние входа (есть напряжение / нет напряжения)
     * @warning Это "сырое" состояние датчика, никак не говорящее о том, сработал он или нет.
     * Дело в том, что некторые датчики при срабатывании устанавливают на входе в логический ноль (большинство),
     * а некоторые - логическую единицу.
     */
    bool m_currentState;

    /// Цвет датчика
    QColor m_ledColor;
};

#endif // SENSOR_H
