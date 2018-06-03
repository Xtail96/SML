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
protected:

    /// Код устройства для получения информации из файла настроек
    QString m_code;

    /// Имя устройства
    QString m_name;

    /// Имя платы, к которой подключено устройство
    QString m_boardName;

    /// Номер порта, к которому подключено устройство
    unsigned int m_portNumber;

    /// Номер выхода, к которому подключено устройство
    unsigned int m_outputNumber;

    /// Активное состояние устройства (устройство включено)
    bool m_activeState;

    /// Текущее состояние устройства (true или false стоит на соответсвующем выходе)
    bool m_currentState;

    /// Требуется ли отображать устройство для пользователя в панели устройств
    bool m_needToDisplay;

    /// Маска, включающее устройство
    byte m_mask;

    /*!
     * \brief Настраивает устройство по менеджеру настроек
     * \param sm - менеджер настроек
     */
    void setup(const SettingsManager &sm);

public:
    /*!
     * \brief Конструктор класса "Устрйоство"
     * \param code - код устройства
     * \param name - имя устройства
     * \param boardName - имя платы, к которой подключено устройство
     * \param portNumber - номер порта, к которому подключено устройство (по умолчанию 0)
     * \param outputNumber - номер выхода, к которому подключено устройство (по умолчанию 0)
     * \param activeState - активаное состояние устройства (по умолчанию false)
     * \param needToDisplay - нужно ли отображать устройство для пользователя на панели устройств (по умолчанию true)
     * \param mask - маска, включающая устройство (по умолчанию 0xff)
     */
    Device(QString code,
           QString name,
           QString boardName,
           unsigned int portNumber = 0,
           unsigned int outputNumber = 0,
           bool activeState = false,
           bool needToDisplay = true,
           byte mask = 0xff);

    /*!
     * \brief Конструктор класса "Устрйоство"
     * \param _code - код устройства
     * \param sm - менеджер настроек
     */
    Device(QString code, const SettingsManager &sm = SettingsManager());

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

    /*!
     * \brief Возвращает код устройства
     * \return код устройства в формате строки (QString)
     */
    QString getCode() const;
};

#endif // DEVICE_H