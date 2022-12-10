#ifndef DEVICE_H
#define DEVICE_H

#include <QMap>
#include <QDebug>

/*!
 * \brief Класс Устройство
 */
class Device
{
public:
    /*!
     * \brief Конструктор класса "Устройство"
     */
    Device(QString id, bool enabled, QString label = "");
    virtual ~Device();
    bool operator<(const Device &device);
    bool operator==(const Device &device);
    bool isEnabled() const;
    QString getLabel() const;
    QString getId() const;
private:
    /// Код устройства для получения информации из файла настроек
    QString m_id;

    /// Пользовательское устройства
    QString m_label;

    /// Признак того, что устройство включено
    bool m_enabled;
};

#endif // DEVICE_H
