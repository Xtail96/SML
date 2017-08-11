#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <map>
#include <vector>

#include "models/machinetool/sensorsmanager/sensor/sensor.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"
#include "models/structs.h"

/*!
 * \brief Класс "Менеджер датчиков"
 */
class SensorsManager
{
private:
    /*!
     * \brief Вектор умных указателей на датчики станка
     */
    std::vector< std::shared_ptr<Sensor> > sensors;
public:
    /*!
     * \brief Конструктор класса "Менеджер датчиков"
     */
    SensorsManager();

    /*!
     * \brief Конструктор копирования класса Менеджер датчиков
     * \param object ссылка на объект класса Менеджер датчиков
     */
    SensorsManager(const SensorsManager &object);

    /*!
     * \brief Инициализирует датчики по файлу настроек
     */
    void initilize();

    /*!
     * \brief Возвращает ссылку на датчики станка
     * \return вектор умных указателей на датчики станка
     */
    std::vector<std::shared_ptr<Sensor> > &getSensors();

    /*!
     * \brief Обновляет состояния датчиков по буферу состояний станка
     * \param buffer - буфер состояний станка
     */
    void updateSensors(const StatesBuffer buffer);
};

#endif // SENSORSMANAGER_H
