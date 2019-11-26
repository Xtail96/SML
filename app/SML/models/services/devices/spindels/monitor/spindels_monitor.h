#ifndef SPINDELSMONITOR_H
#define SPINDELSMONITOR_H

#include <QObject>
#include "models/machine_tool_elements/device/spindel.h"

/**
 * @brief Класс Монитор состояния шпинделей
 *
 * Предназначен для отслеживания состояния шпинделей в режиме реального времени.
 */
class SpindelsMonitor : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Конструктор класса
     * Связывает каждый шпиндель с функцией обработчкиком (onSpindel_StateChanged).
     *
     * @param spindels список умных указателей на шпиндели, состояние которых требуется отслеживать
     * @param parent родительский объект в дереве объектов
     */
    explicit SpindelsMonitor(QList< QSharedPointer<Spindel> > spindels, QObject *parent = nullptr);

signals:

    /**
     * @brief Сигнал об изменении состояния шпинделя
     * @param uid уникальный идентификатор шпинделя
     * @param enable обновленное состояние шпинделя
     * @param rotations обновленное число оборотов шпинделя
     */
    void stateChanged(QString uid, bool enable, size_t rotations);

protected slots:

    /**
     * @brief Испускает сигнал об изменении состояния шпинделя
     * @param uid уникальный идентификатор шпинделя
     * @param enable обновленное состояние шпинделя
     * @param rotations обновленное число оборотов шпинделя
     */
    void onSpindel_StateChanged(QString uid, bool enable, size_t rotations);
};

#endif // SPINDELSMONITOR_H
