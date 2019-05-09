#ifndef SWITCH_SPINDEL_INTERACTOR_H
#define SWITCH_SPINDEL_INTERACTOR_H

#include <QObject>

#include "models/server/sml_server.h"

/**
 * @brief Класс Включения/Отключения шпинделя
 * Запускает процесс включения/отключения шпинделя.
 * Реализует паттерн интерактор.
 */
class SwitchSpindelInteractor
{
public:
    /**
     * @brief Конструктор класса
     */
    explicit SwitchSpindelInteractor();
    ~SwitchSpindelInteractor();

    /**
     * @brief Запускает процесс включения/отключения шпинделя
     * @param server web-socket сервер, который будет отправлять посылку к адаптерам для включения/отключения шпинделя
     * @param uid уникальный идентификатор шпинделя
     * @param enable требуемое состояние шпинделя, после отправки посылки. True - шпиндель включен. False - шпиндель выключен.
     * @param rotations требуемое число оборотом, после отправки посылки
     */
    static void execute(SMLServer* server, QString uid, bool enable, size_t rotations = 0);

protected:
    /**
     * @brief Производит формирование и запускает процесс отправки посылки для включения шпинделя
     * @param uid уникальный идентификатор шпинделя
     * @param rotations требуемое число оборотов шпинделя после включения
     * @param server указатель на сервер, который должен выполнить отправку сообщения
     */
    static void switchOn(QString uid, size_t rotations, SMLServer* server);

    /**
     * @brief Производит формирование и запускает процесс отправки посылки для выключения шпинделя
     * @param uid уникальный идентификатор шпинделя
     * @param server указатель на сервер, который должен выполнить отправку сообщения
     */
    static void switchOff(QString uid, SMLServer *server);
};

#endif // SWITCH_SPINDEL_INTERACTOR_H
