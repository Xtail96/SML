#ifndef COMMAND_H
#define COMMAND_H


#include <string>
#include <vector>
#include <map>

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
enum COLORSNAME
{
    defaultColor,
    functionColor,
    commentColor,
    cycleColor,
    labelColor,
    warningColor,
    safeColor,
    zeroColor,
    finishColor,
    modifyColor
};
static std::map<COLORSNAME, std::string> COMMANDCOLORS =
{
    {defaultColor, "#333"},
    // functionColor = "#2f4f4f";
    {functionColor, "#4682B4"},
    {commentColor, "#2E8B57"},
    {cycleColor, "#999900"},
    {labelColor, "#3300ff"},
    {warningColor, "#990000"},
    {safeColor, "#2E8B57"},
    {zeroColor, "#000099"},
    {finishColor, "#660099"},
    {modifyColor, "#770077"}
};
struct Command
{
    COMMAND id;
    std::string commandColor;
    std::vector<std::string> args;
};

#endif // COMMAND_H
