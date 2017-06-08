#ifndef CONTROLLERCONNECTOR_H
#define CONTROLLERCONNECTOR_H
#include <string>

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>

#include "structs.h"

/**
 * \brief Класс "Модуль взаимодействия с контроллером"
 * \warning Является синглтоном
 * \brief Класс получает данные из буфера обмена данными и следит за корректностью разрядности;
 */
class ControllerConnector
{
private:
    QSerialPort *serialPort;
public:
    ControllerConnector();
    //! Возвращает экземпляр класса "Модуль взаимосвязи с  контроллером"
    static ControllerConnector& Instance();

    ~ControllerConnector();
public slots:

    //! Отправляет данные на контроллер
    void send();
    void recieved();
};

#endif // CONTROLLERCONNECTOR_H
