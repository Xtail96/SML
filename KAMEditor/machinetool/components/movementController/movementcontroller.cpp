#include "movementcontroller.h"

MovementController::MovementController(unsigned int _axisesCount, double _step, double _velocity) :
    step(_step), velocity(_velocity), dimensionsController(_axisesCount)
{
    addAxises(_axisesCount);
    axisesLength = getAxisesLength();
}

void MovementController::addAxises(const unsigned int &count)
{
    unsigned int axisCount = count;
    if(axisCount > 11)
    {
       axisCount = 11;
    }
    axises.reserve(axisCount);
    for(unsigned int i = 0; i < axisCount; i++)
    {
        std::string axisName = axisNames.getNameByKey(i);
        Axis* newAxis = new Axis(axisName);
        axises.push_back(std::shared_ptr<Axis>(newAxis));
    }
    setupAxises();
}

void MovementController::setupAxises()
{
    SettingsManager settingsManager;
    for(auto axis : axises)
    {
        axis->setup(settingsManager);
    }
}

std::vector<std::shared_ptr<Axis> > MovementController::getAxises() const
{
    return axises;
}

void MovementController::setAxises(const std::vector<std::shared_ptr<Axis> > &value)
{
    axises = value;
}

void MovementController::stepMove(Point &to)
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
    Point newCoordinates = currentCoordinates + offset;
    if(checkCurrentCoordinates(newCoordinates))
    {
        currentCoordinatesFromBase = newCoordinates;
    }
}

bool MovementController::checkCurrentCoordinates(Point &newCoordinates)
{
    bool isMovementCorrect = true;
    if(!dimensionsController.isMovementCorrect(axisesLength, newCoordinates))
    {
        isMovementCorrect = false;
    }
    return isMovementCorrect;
}

Point MovementController::getAxisesLength()
{
    Point _axisesLength(axises.size());
    for(unsigned int i = 0; i < axises.size(); i++)
    {
        _axisesLength[i] = axises[i]->getLength();
    }
    return _axisesLength;
}
