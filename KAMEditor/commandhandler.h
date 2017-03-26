#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <functional>
#include <vector>
#include <map>
#include <QString>

#include "command.h"
#include "machinetool.h"

typedef std::vector<std::string> arguments;
typedef std::function<void(arguments)> commandHandler;

void CMD_ARC_HANDLER(arguments args);


static std::map<COMMAND, commandHandler> commandHandlerMap = {
    { CMD_ARC, CMD_ARC_HANDLER }
//    {},
};

static std::map<COMMAND, std::string> commandNameMap = {
    {CMD_ZERO, "Обнулить"},
    {CMD_END, "Окончить"},
    {CMD_ON, "Включить"},
    {CMD_OFF, "Выключить"},
    {CMD_LINE, "Линия"},
    {CMD_TTLINE, "ТТ-Линия"},
    {CMD_TTTLINE, "ТТТ-Линия"},
    {CMD_ARC, "Дуга"},
    {CMD_ARC2, "Относительная дуга"},
    {CMD_ROTATE, "Поворот"},
    {CMD_FOR, "Цикл"},
    {CMD_ENDFOR, "Конец цикла"},
    {CMD_LABEL, "Метка"},
    {CMD_GOTO, "На метку"},
    {CMD_PROC, "Подпрограмма"},
    {CMD_RETURN, "Вернуться"}
};


std::string getNameByCommand(COMMAND cmd);


COMMAND getCommandByName(std::string name);

#endif // COMMANDHANDLER_H
