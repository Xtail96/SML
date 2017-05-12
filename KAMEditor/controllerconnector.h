#ifndef CONTROLLERCONNECTOR_H
#define CONTROLLERCONNECTOR_H
#include <string>

#include <QMainWindow>

#include "structs.h"

/**
 * \brief Класс "Модуль взаимодействия с контроллером"
 * \warning Является синглтоном
 * \brief Класс формирует буфер для записи данных о том, какие действия нужно выполнить контроллеру и предоставляет необходимый программный интерфейс для работы с буфером;
 */
class ControllerConnector
{
private:
    //! Буфер для взаимодействия с контроллером, содержащий данные для полученные или отправляемые на котроллер;
    /**
     * Структура буфера:
     * Буфер представляет собой вектор строк;
     * Каждая строка содержит следующие параметры:
     * 1 символ
     */
    std::vector< std::vector<unsigned int> > buffer;

    //! Очищает буфер для взаимодействия с контроллером;
    void clearBuffer();
public:
    ControllerConnector();
    //! Возвращает экземпляр класса "Модуль взаимосвязи с  контроллером"
    static ControllerConnector& Instance();

    void pushBackToBuffer(const std::vector<unsigned int> &element);

    std::vector< std::vector<unsigned int> >getBuffer() const;

    std::vector<unsigned int> readInputInformation(const unsigned int &inputNumber) const;
public slots:

    //! Отправляет данные на контроллер
    void send();
};

#endif // CONTROLLERCONNECTOR_H
