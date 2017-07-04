#include "dimensionscontroller.h"

bool DimensionsController::getIsDimensionControlEnable() const
{
    return isDimensionControlEnable;
}

void DimensionsController::setIsDimensionControlEnable(bool value)
{
    isDimensionControlEnable = value;
}

DimensionsController::DimensionsController(int _axisesCount, bool _isDimensionControlEnable) :
    axisesCount(_axisesCount), isDimensionControlEnable(_isDimensionControlEnable)
{

}

bool DimensionsController::isMovementCorrect(Point &axisesLength, Point &newCoordinates)
{
    bool isMovementCorrect = true;
    // проверка не выходим ли за пределы стола
    if(isDimensionControlEnable && checkAxisesCoordinates(axisesLength, newCoordinates))
    {
        isMovementCorrect = false;
    }
    return isMovementCorrect;
}

bool DimensionsController::checkAxisesCoordinates(Point &axisesLength, Point &newCoordinates)
{
    bool isCoordinatesCorrect = true;
    for(int i = 0; i < axisesCount; i++)
    {
        if(newCoordinates[i] >= axisesLength[i])
        {
            isCoordinatesCorrect = false;
        }
    }
    return isCoordinatesCorrect;
}
