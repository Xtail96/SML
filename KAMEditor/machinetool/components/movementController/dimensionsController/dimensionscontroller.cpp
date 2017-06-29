#include "dimensionscontroller.h"

bool DimensionsController::getIsDimensionControlEnable() const
{
    return isDimensionControlEnable;
}

void DimensionsController::setIsDimensionControlEnable(bool value)
{
    isDimensionControlEnable = value;
}

DimensionsController::DimensionsController(bool _isDimensionControlEnable) :
    isDimensionControlEnable(_isDimensionControlEnable)
{

}

bool DimensionsController::isMovementCorrect(const Point &axisesLength, const Point &newCoordinates)
{
    bool isMovementCorrect = true;
    // проверка не выходим ли за пределы стола
    if(isDimensionControlEnable /*&& axisesLength < newCoordinates*/)
    {
        isMovementCorrect = false;
    }
    return isMovementCorrect;
}
