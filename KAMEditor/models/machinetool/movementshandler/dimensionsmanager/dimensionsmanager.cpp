#include "dimensionsmanager.h"

bool DimensionsManager::getIsDimensionControlEnable() const
{
    return isDimensionControlEnable;
}

void DimensionsManager::setIsDimensionControlEnable(bool value)
{
    isDimensionControlEnable = value;
}

DimensionsManager::DimensionsManager(int _axisesCount, bool _isDimensionControlEnable) :
    axisesCount(_axisesCount), isDimensionControlEnable(_isDimensionControlEnable)
{

}

bool DimensionsManager::isMovementCorrect(Point &axisesLength, Point &newCoordinates)
{
    bool isMovementCorrect = true;
    // проверка не выходим ли за пределы стола
    if(isDimensionControlEnable && !checkAxisesCoordinates(axisesLength, newCoordinates))
    {
        isMovementCorrect = false;
    }
    return isMovementCorrect;
}

bool DimensionsManager::checkAxisesCoordinates(Point &axisesLength, Point &newCoordinates)
{
    bool isCoordinatesCorrect = true;
    for(int i = 0; i < axisesCount; i++)
    {
        if(newCoordinates[i] >= axisesLength[i])
        {
            isCoordinatesCorrect = false;
        }
        else
        {
            if(newCoordinates[i] < 0)
            {
                isCoordinatesCorrect = true;
            }
        }
    }
    return isCoordinatesCorrect;
}
