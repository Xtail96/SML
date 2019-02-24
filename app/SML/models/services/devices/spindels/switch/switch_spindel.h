#ifndef SWITCHSPINDEL_H
#define SWITCHSPINDEL_H

#include <QObject>

#include "models/server/sml_server.h"
#include "models/types/base/interactor.h"

/**
 * @brief Класс Включения/Отключения шпинделя
 * Запускает процесс включения/отключения шпинделя.
 * Реализует паттерн интерактор.
 */
class SwitchSpindel : public QObject, public Interactor
{
    Q_OBJECT
public:

    /**
     * @brief Конструктор класса
     * @param server web-socket сервер, который будет отправлять посылку к адаптерам для включения/отключения шпинделя
     * @param uid уникальный идентификатор шпинделя
     * @param enable требуемое состояние шпинделя, после отправки посылки. True - шпиндель включен. False - шпиндель выключен.
     * @param rotations требуемое число оборотом, после отправки посылки
     * @param parent родительский объект в дереве объектов
     */
    explicit SwitchSpindel(SMLServer* server, QString uid, bool enable, size_t rotations = 0, QObject *parent = nullptr);
    ~SwitchSpindel();

    /**
     * @brief Запускает процесс включения/отключения шпинделя
     */
    void execute();

protected:

    /// Web-socket сервер для отправки запроса к адаптерам
    SMLServer* m_server;

    /// Уникальный идентификатор шпинделя
    QString m_uid;

    /// Требуемое число оборотов шпинделя, которое нужно установить после включения
    size_t m_rotations;

    /// Требуемое состояние шпинделя, после отправки посылки. True - шпиндель включен. False - шпиндель выключен.
    bool m_enable;

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

signals:

public slots:
};

#endif // SWITCHSPINDEL_H
