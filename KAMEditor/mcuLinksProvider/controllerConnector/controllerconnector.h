#ifndef CONTROLLERCONNECTOR_H
#define CONTROLLERCONNECTOR_H
#include <string>

#include <QMainWindow>
#include <QSerialPort>

#include "structs.h"

/**
 * \brief Класс "Модуль взаимодействия с контроллером"
 * \warning Является синглтоном
 * \brief Класс получает данные из буфера обмена данными и следит за корректностью разрядности;
 */
class ControllerConnector
{
private:
    QSerialPort serialPort;
public:
    ControllerConnector();
    //! Возвращает экземпляр класса "Модуль взаимосвязи с  контроллером"
    static ControllerConnector& Instance();
public slots:

    //! Отправляет данные на контроллер
    void send();
};

#endif // CONTROLLERCONNECTOR_H
