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
           bool enable,
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

    bool m_enable;

signals:
    void currentStateChanged(bool on);
};

#endif // DEVICE_H
