#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "models/structs.h"
#include "models/settingsmanager/settingsmanager.h"

/*!
 * \brief Класс Датчик
 */
class Sensor
{
protected:
    /// код датчика для получения информации из файла настроек
    QString code;

    /// имя датчика
    QString name;

    /// подпись датчика для отображения в итнтерфейсе
    QString label;

    /// имя платы, к которой подключен датчик
    QString boardName;

    /// номер порта, ко входу которого подключен датчик
    unsigned int portNumber;

    /// номер входа, к которому подключен датчик
    unsigned int inputNumber;

    /// активное состояние датчика
    bool activeState;

    /// сотояние датчика (включен/выключен)
    bool currentState;

    /// цвет индикатора при срабатывании датчика
    QColor color;

    /*!
     * \brief Устанавливает параметры датчика
     * \param sm - указатель на менеджер настроек
     */
    void setup(SettingsManager *sm);
public:
    /*!
     * \brief Конструктор класса "Датчик"
     * \param _code - код датчика
     * \param _name - имя датчика
     * \param _boardName - имя платы, к которой подключается датчик
     * \param _portNumber - номер порта
     * \param _inputNumber - номер входа
     * \param _activeState - активное состояние датчика
     * \param _color - цвет инидкатора при срабатывании датчика
     */
    Sensor(QString _code,
           QString _name, QString _label,
           QString _boardName,
           unsigned int _portNumber,
           unsigned int _inputNumber,
           bool _activeState = false,
           QColor _color = QColor(0, 125, 0));

    /*!
     * \brief Конструктор класса "Датчик"
     * \param _code - код датчика
     * \param sm - указатель на менеджер настроек (по умолчанию nullptr)
     */
    Sensor(QString _code,
           SettingsManager *sm = nullptr);

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
};

#endif // SENSOR_H
