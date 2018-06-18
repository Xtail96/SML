#ifndef DEVICE_H
#define DEVICE_H
#include "models/types/structs.h"

/*!
 * \brief Класс Устройство
 */
class Device : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор класса "Устрйоство"
     */
    Device(QString name, QString label, QString index, bool activeState, int mask, QObject *parent = nullptr);

    virtual ~Device();

    virtual bool isEnable() const;

    virtual void updateCurrentState(bool value);

    virtual QStringList getParams() = 0;

    QString getLabel() const;

    bool getActiveState() const;

    bool getCurrentState() const;

    byte getMask() const;

    QString getName() const;

    QString getIndex() const;

protected:

    /// Код устройства для получения информации из файла настроек
    QString m_name;

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
};

#endif // DEVICE_H
