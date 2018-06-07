#ifndef DEVICE_H
#define DEVICE_H
#include <string>

#include <QMainWindow>

#include "models/settingsmanager/settingsmanager.h"
#include "models/structs.h"

/*!
 * \brief Класс Устройство
 */
class Device
{
public:
    /*!
     * \brief Конструктор класса "Устрйоство"
     * \param code - код устройства
     * \param sm - менеджер настроек
     */
    Device(QString code, const SettingsManager &sm = SettingsManager());

    virtual ~Device();

    virtual bool isEnable() const;

    virtual void updateCurrentState(bool value);

    virtual QStringList getParams() = 0;

    QString getLabel() const;

    bool getActiveState() const;

    bool getCurrentState() const;

    byte getMask() const;

    QString getCode() const;

    QString getIndex() const;

protected:

    /// Код устройства для получения информации из файла настроек
    QString m_code;

    /// Индекс устройства = номер байта, в котором лежит состояние устройства
    QString m_index;

    /// Имя устройства
    QString m_label;

    /// Активное состояние устройства (устройство включено)
    bool m_activeState;

    /// Текущее состояние устройства (true или false стоит на соответсвующем выходе)
    bool m_currentState;

    /// Маска, включающее устройство
    byte m_mask;

    /*!
     * \brief Инициализирует устройство с помощью менеджера настроек
     * \param sm - менеджер настроек
     */
    void initialize(const SettingsManager &sm);
};

#endif // DEVICE_H
