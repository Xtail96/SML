#include "movementcontroller.h"

MovementController::MovementController()
{
    // получить у станка длины по каждой оси и присвоить их в axisesLength
    // получить у станка и установить текущие координаты, текущие координаты от базы и координаты парка
    // получить у станка и установить скорость
    // получить у станка и установить текущий шаг
}

void MovementController::stepMove(const Point &to)
{
    double current_step = (step > 0) ? step : 0.01;
    if(checkCurrentCoordinates(to))
    {
        //currentCoordinatesFromBase += offset*current_step;
    }
}

void MovementController::move(const Point& offset)
{
    double current_step = (step > 0) ? step : 0.01;
    /*if(checkCurrentCoordinates(currentCoordinates + offset))
    {
        currentCoordinatesFromBase += offset*current_step;
    }*/
}

bool MovementController::checkCurrentCoordinates(const Point &newCoordinates)
{
    bool isMovementCorrect = true;
    if(!dimensionsController.isMovementCorrect(axisesLength, newCoordinates))
    {
        isMovementCorrect = false;
    }
    return isMovementCorrect;
}
