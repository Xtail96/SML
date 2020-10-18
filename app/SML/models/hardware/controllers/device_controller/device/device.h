#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QMap>
#include <QDebug>

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
    Device(QString settingsUid,
           QString uid,
           QString label,
           bool activeState,
           QObject *parent = nullptr);

    virtual ~Device();

    /**
     * @brief Оператор меньше для порядковой сортировки устройств
     */
    bool operator<(const Device &device);

    /**
     * @brief Оператор равенства для сравнения устройств
     */
    bool operator==(const Device &device);

    virtual bool isEnable() const;

    virtual void setCurrentState(bool value, QMap<QString, QString> params);

    virtual QStringList getParams() = 0;

    QString getLabel() const;

    bool getActiveState() const;

    bool getCurrentState() const;

    QString getSettingsUId() const;

    QString getUid() const;

    /**
     * @brief Возвращает актуальные настройки устройства
     * @return настройки устройства в виде строки, формата
     * "setting1_key:setting1_value;setting2_key:setting2_value"
     */
    virtual QString getSettings();

protected:

    /// Код устройства для получения информации из файла настроек
    QString m_settingsUid;

    /// Уникальный идентификатор устройства = номер байта, в котором лежит состояние устройства
    QString m_uid;

    /// Пользовательское устройства
    QString m_label;

    /// Активное состояние устройства (устройство включено)
    bool m_activeState;

    /// Текущее состояние устройства (true или false стоит на соответсвующем выходе)
    bool m_currentState;

signals:
    void currentStateChanged(bool on);
};

#endif // DEVICE_H
