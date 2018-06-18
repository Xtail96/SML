#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "models/structs.h"
#include "models/settingsmanager/settingsmanager.h"

/*!
 * \brief Класс Датчик
 */
class Sensor : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса "Датчик"
     * \param _code - код датчика
     * \param sm - менеджер настроек
     */
    Sensor(QString code, const SettingsManager &sm = SettingsManager(), QObject *parent = nullptr);

    /*!
     * \brief Получает текущее состояние датчика
     * \return текущее состояние датчика
     */
    bool getCurrentState() const;

    /*!
     * \brief Обновляет текущее состояния датчика, если новое значение НЕ совпадает с текущим
     * \param value - новое состояние датчика
     */
    void setCurrentState(bool value);

    /*!
     * \brief Получает номер порта датчика
     * \return номер порта датчика
     */
    unsigned int getPortNumber() const;

    /*!
     * \brief Получает номер входа датчика
     * \return  номер входа датчика
     */
    unsigned int getInputNumber() const;

    /*!
     * \brief Возвращает имя датчика
     * \return имя датчика
     */
    QString getName() const;

    /*!
     * \brief Возвращает имя платы, к которой подключается датчик
     * \return имя платы, к которой подключается датчик
     */
    QString getBoardName() const;

    /*!
     * \brief Возвращает значение активного состояния датчика
     * \return значение активного состояния датчика
     */
    bool getActiveState() const;

    /*!
     * \brief Возвращает цвет индикатора при срабатывании датчика
     * \return цвет индикатора при срабатывании датчика
     */
    QColor getColor() const;

    /*!
     * \brief Сработал ли датчик
     * \return true, если датчик сработал, false - иначе
     */
    bool isEnable();

    /*!
     * \brief Возвращает код датчика
     * \return код датчика в формате строки (QString)
     */
    QString getCode() const;

    /*!
     * \brief Возврщает подпись датчика
     * \return подпись датчика в формате строки (QString)
     */
    QString getLabel() const;

    QString getSettings();

protected:
    /// код датчика для получения информации из файла настроек
    QString m_code;

    /// имя датчика
    QString m_name;

    /// подпись датчика для отображения в итнтерфейсе
    QString m_label;

    /// имя платы, к которой подключен датчик
    QString m_boardName;

    /// номер порта, ко входу которого подключен датчик
    unsigned int m_portNumber;

    /// номер входа, к которому подключен датчик
    unsigned int m_inputNumber;

    /// активное состояние датчика
    bool m_activeState;

    /// сотояние датчика (включен/выключен)
    bool m_currentState;

    /// цвет индикатора при срабатывании датчика
    QColor m_color;

    /*!
     * \brief Инициализирует датчик с помощью менеджера настроек
     * \param sm - менеджер настроек
     */
    void initialize(const SettingsManager &sm);

signals:
    void stateChanged(QString name, bool state);

public slots:
    void update(bool state);
};

#endif // SENSOR_H
