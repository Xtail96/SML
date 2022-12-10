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
           bool enabled,
           QString label = "",
           QColor ledColor = QColor("green"));
    bool operator<(const Sensor &sensor) const;
    bool operator>(const Sensor &sensor) const;
    bool operator<=(const Sensor &sensor) const;
    bool operator>=(const Sensor &sensor) const;
    bool operator==(const Sensor &sensor) const;
    QString id() const;
    QColor ledColor() const;
    QString label() const;
    bool enabled() const;
    void setEnabled(bool enabled);

private:
    QString m_id;
    QString m_label;
    bool m_enabled;
    QColor m_ledColor;
};

#endif // SENSOR_H
