#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <vector>
#include "point.h"

class CommandInterpreter
{
public:
    static CommandInterpreter& Instance();

    // методы для работы с точками
    void addPoint(Point p);
    void setPoint(unsigned int num, Point p);
    void removePoint(unsigned int num);

    void setPointToSelect(unsigned int num);
    unsigned int getPointToSelect();

    std::vector<Point> getPoints();

private:
    // точки
    std::vector<Point> points;

    unsigned int point_to_select;

    // конструктор и деструктор недоступны публично
    CommandInterpreter() {}
    ~CommandInterpreter() {}

    // запрет копирования
    CommandInterpreter(CommandInterpreter const&);
    CommandInterpreter& operator=(CommandInterpreter const&);
};

#endif // COMMANDINTERPRETER_H
