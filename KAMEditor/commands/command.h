#ifndef COMMAND_H
#define COMMAND_H


#include <string>
#include <vector>

enum COMMAND {CMD_ARC,
              CMD_ARC2,
              CMD_CALL, //
              CMD_COMMENT,
              CMD_END, //
              CMD_FOR, //
              CMD_ENDFOR, //
              CMD_GOTO, //
              CMD_LABEL, //
              CMD_LINE,
              CMD_MILL,
              CMD_ON,
              CMD_OFF,
              CMD_PARK,
              CMD_PAUSE,
              CMD_PROC,
              CMD_RELARC,
              CMD_REM,
              CMD_RETURN, //
              CMD_ROTATE,
              CMD_SCALEX,
              CMD_SCALEY,
              CMD_SCALEZ,
              CMD_SPEED,
              CMD_STOP,
              CMD_TOPARK,
              CMD_TOZERO,
              CMD_TPARC,
              CMD_TTZARC,
              CMD_TTARC,
              CMD_TTLINE,
              CMD_TTPOINT,
              CMD_SPLINE,
              CMD_TTTARC,
              CMD_TTTLINE,
              CMD_TTTTSPLINE,
              CMD_TZARC,
              CMD_ZERO,
              CMD_UNDEFINED
             };

class Command
{
    COMMAND id;
    std::string commandColor;
    std::vector<std::string> args;
};

#endif // COMMAND_H
