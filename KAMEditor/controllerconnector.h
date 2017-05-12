#ifndef CONTROLLERCONNECTOR_H
#define CONTROLLERCONNECTOR_H
#include <string>

#include <QMainWindow>

/**
 * \brief Класс "Модуль взаимодействия с контроллером"
 * \warning Является синглтоном
 * \brief Класс формирует буфер для записи данных о том, какие действия нужно выполнить контроллеру и предоставляет необходимый программный интерфейс для работы с буфером;
 */
class ControllerConnector
{
private:
    //! Буфер для взаимодействия с контроллером, содержащий данные для полученные или отправляемые на котроллер;
    std::string buffer;

    //! Очищает буфер для взаимодействия с контроллером;
    void clearBuffer();
public:
    ControllerConnector();
    //! Возвращает экземпляр класса "Модуль взаимосвязи с  контроллером"
    static ControllerConnector& Instance();

    //! Возвращает данные из буфера обмена данных с контроллером в формате строки
    std::string getBuffer() const;

    //! Записывает информацию в буфер данных для взаимодействия с контроллером в формате строки
    void setBuffer(const std::string &s);
public slots:

    //! Отправляет данные на контроллер
    void send();
};

#endif // CONTROLLERCONNECTOR_H
