#include "movementshandler.h"

MovementsHandler::MovementsHandler(SettingsManager *sm) :
    dimensionsManager()
{
    size_t axisesCount = 3;
    try
    {
        axisesCount = sm->get("MachineToolInformation", "AxisesCount").toUInt();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации менеджера осей!") + QString(e.what())).exec();
    }

    addAxises(axisesCount, sm);
    dimensionsManager = new DimensionsManager(axisesCount);
    currentCoordinates.setCoordinatesCount(axisesCount);
    currentCoordinatesFromBase.setCoordinatesCount(axisesCount);
    parkCoordinates.setCoordinatesCount(axisesCount);
    step = -1;
    velocity = 30;
    axisesLength = getAxisesLength();
}

MovementsHandler::~MovementsHandler()
{
    delete dimensionsManager;
}

void MovementsHandler::addAxises(const unsigned int &count, SettingsManager *sm)
{
    unsigned int axisCount = count;
    if(axisCount > 11)
    {
       axisCount = 11;
    }
    axises.reserve(axisCount);
    for(unsigned int i = 0; i < axisCount; i++)
    {
        std::string axisName = axisesNames.getNameByKey(i);
        Axis* newAxis = new Axis(axisName, sm);
        axises.push_back(std::shared_ptr<Axis>(newAxis));
    }
}

Point MovementsHandler::getAxisesLength()
{
    Point _axisesLength(axises.size());
    for(unsigned int i = 0; i < axises.size(); i++)
    {
        _axisesLength[i] = axises[i]->getLength();
    }
    return _axisesLength;
}

void MovementsHandler::moveTo(Point &to, bool mode)
{
    if(mode)
    {
        // точка задана относительно базы
        if(checkCurrentCoordinates(to))
        {

            //currentCoordinatesFromBase += offset*current_step;
        }
    }
    //double current_step = (step > 0) ? step : 0.01;
}

void MovementsHandler::move(const Point& offset)
{
    //double current_step = (step > 0) ? step : 0.01;
    Point newCoordinates = currentCoordinates + offset;
    if(checkCurrentCoordinates(newCoordinates))
    {
        currentCoordinatesFromBase = newCoordinates;
    }
}

bool MovementsHandler::checkCurrentCoordinates(Point &newCoordinates)
{
    bool isMovementCorrect = true;
    if(!dimensionsManager->isMovementCorrect(axisesLength, newCoordinates))
    {
        isMovementCorrect = false;
    }
    return isMovementCorrect;
}

Point MovementsHandler::getCurrentCoordinatesFromBase() const
{
    return currentCoordinatesFromBase;
}

Point MovementsHandler::getParkCoordinates() const
{
    return parkCoordinates;
}

void MovementsHandler::updateAllCoordinates(Point currentCoordinatesAbsolute)
{
    currentCoordinatesFromBase = currentCoordinatesAbsolute;

}

Point MovementsHandler::getCurrentCoordinates() const
{
    return currentCoordinates;
}

std::vector<std::shared_ptr<Axis> > MovementsHandler::getAxises() const
{
    return axises;
}

void MovementsHandler::setAxises(const std::vector<std::shared_ptr<Axis> > &value)
{
    axises = value;
}

