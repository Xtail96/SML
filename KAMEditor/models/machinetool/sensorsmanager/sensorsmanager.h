#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <map>
#include <vector>

#include "models/machinetool/sensorsmanager/sensor/sensor.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"

/*!
 * \brief Класс "Менеджер датчиков"
 */
class SensorsManager
{
private:
    /*!
     * \brief вектор умных указателей на датчики станка
     */
    std::vector< std::shared_ptr<Sensor> > sensors;
public:
    /*!
     * \brief Конструктор класса "Датчик"
     */
    SensorsManager();

    /*!
     * \brief Инициализирует датчики по файлу настроек
     */
    void initilize();

    /*!
     * \brief Возвращает датчики станка
     * \return вектор умных указателей на датчики станка
     */
    std::vector<std::shared_ptr<Sensor> > &getSensors();
};

#endif // SENSORSMANAGER_H
