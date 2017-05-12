#ifndef CONTROLLERCONNECTOR_H
#define CONTROLLERCONNECTOR_H
#include <string>

#include <QMainWindow>

class ControllerConnector
{
private:
    std::string buffer;
    void clearBuffer();
public:
    ControllerConnector();
    static ControllerConnector& Instance();
    std::string getBuffer() const;
    void setBuffer(const std::string &s);
public slots:
    void send();
};

#endif // CONTROLLERCONNECTOR_H
