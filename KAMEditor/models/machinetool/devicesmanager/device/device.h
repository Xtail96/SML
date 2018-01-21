#ifndef DEVICE_H
#define DEVICE_H
#include <string>

#include <QMainWindow>

#include "models/machinetool/settingsmanager/settingsmanager.h"
#include "models/structs.h"

/*!
 * \brief Класс Устройство
 */
class Device
{
    QString code;

    /// Имя устройства
    QString name;

    /// Имя платы, к которой подключено устройство
    QString boardName;

    /// Номер порта, к которому подключено устройство
    unsigned int portNumber;

    /// Номер выхода, к которому подключено устройство
    unsigned int outputNumber;

    /// Активное состояние устройства (устройство включено)
    bool activeState;

    /// Текущее состояние устройства (true или false стоит на соответсвующем выходе)
    bool currentState;

    /// Требуется ли отображать устройство для пользователя в панели устройств
    bool needToDisplay;

    /// Маска, включающее устройство
    byte mask;
public:
    /*!
     * \brief Конструктор класса Устрйоство
     * \param _name - имя устройства
     * \param _boardName - имя платы, к которой подключено устройство (по умолчанию undefined)
     * \param _portNumber - номер порта, к которому подключено устройство (по умолчанию 0)
     * \param _outputNumber - номер выхода, к которому подключено устройство (по умолчанию 0)
     * \param _activeState - активаное состояние устройства (по умолчанию false)
     * \param _currentState - текущее состояние устройства (по умолчанию true)
     * \param _needToDisplay - нужно ли отображать устройство для пользователя на панели устройств (по умолчанию true)
     * \param _mask - маска, включающая устройство (по умолчанию 0xff)
     */
    Device(QString _code,
           QString _name = "undefined",
           QString _boardName = "undefined",
           unsigned int _portNumber = 0,
           unsigned int _outputNumber = 0,
           bool _activeState = false,
           bool _currentState = true,
           bool _needToDisplay = true,
           byte _mask = 0xff);

    /*!
     * \brief Настраивает устройство по менеджеру настроек
     * \param settingsManager - константная ссылка на менеджер настроек
     */
    void setup();

    /*!
     * \brief Проверяет включено ли устройство
     * \return true, если устройство включено, false - иначе
     */
    bool isEnable() const;

    /*!
     * \brief Возвращает имя платы, к которой подкллючено устройство
     * \return имя платы, к которой подключено устройство
     */
    QString getBoardName() const;

    /*!
     * \brief Устанавливает новое значение имени платы, к которой подключено устройство
     * \param value - имя платы, к которой подключено устройство
     */
    void setBoardName(const QString &value);

    /*!
     * \brief Возвращает имя порта, к которому подкллючено устройство
     * \return имя порта, к которому подключено устройство
     */
    unsigned int getPortNumber() const;

    /*!
     * \brief Устанавливает новое значение имени порта, к которому подключено устройство
     * \param value - имя порта, к которому подключено устройство
     */
    void setPortNumber(unsigned int value);

    /*!
     * \brief Возвращает имя выхода, к которому подкллючено устройство
     * \return имя выхода, к которому подключено устройство
     */
    unsigned int getOutputNumber() const;

    /*!
     * \brief Устанавливает новое значение имени выхода, к которому подключено устройство
     * \param value - имя выхода, к которому подключено устройство
     */
    void setOutputNumber(unsigned int value);

    /*!
     * \brief Возвращает имя устройства
     * \return имя устройства
     */
    QString getName() const;

    /*!
     * \brief Устанавливает новое значение имени устройства
     * \param value - имя устройства
     */
    void setName(const QString &value);

    /*!
     * \brief Возвращает активное состояние устройства
     * \return true, если устройство включается 1, false - иначе
     */
    bool getActiveState() const;

    /*!
     * \brief Устанавливает новое значение активного состояния устройства
     * \param value - true, если устройство включается 1, false - иначе
     */
    void setActiveState(bool value);

    /*!
     * \brief Возвращает текущее состояние устройства
     * \return true, если на выходе соответсвующего устройства установлена 1, false - иначе
     */
    bool getCurrentState() const;

    /*!
     * \brief Устанавливает новое значение текущего состояния устройства
     * \param value - true, если на выходе соответсвующего устройства установлена 1, false - иначе
     */
    void setCurrentState(bool value);

    /*!
     * \brief Возвращает нужно ли отображать устройство для пользователя
     * \return true, если устройство нужно отображать, false - иначе
     */
    bool getNeedToDisplay() const;

    /*!
     * \brief Устанавливает новое значение необходимости отображения устройства
     * \param value - true, если устройство нужно отображать, false - иначе
     */
    void setNeedToDisplay(bool value);

    /*!
     * \brief Возвращает текущую маску включения устройства
     * \return маска включения устройства
     */
    byte getMask() const;

    /*!
     * \brief Устанавливает новое значение маски включения устройства
     * \param value - маска, включающая устройство
     */
    void setMask(const byte &value);

    QString getCode() const;
};

#endif // DEVICE_H
