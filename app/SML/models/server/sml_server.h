#ifndef SMLSERVER_H
#define SMLSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

#include "libs/json_parser/json.h"

#include "models/types/exceptions/exceptions.h"

#include "models/types/structs.h"
#include "models/server/u1_state.h"
#include "models/utils/error_codes/error_codes.h"

/**
 * @brief Класс SML-сервер
 *
 * Предназначен для взаимодействия с адаптерами контроллеров U1 и U2
 * Использует технологию Web-Soket для реализации коммуникаций
 */
class SMLServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса
     * @param port порт сервера
     * @param parent родительский виджет в дереве объектов
     */
    explicit SMLServer(size_t port, QObject *parent = nullptr);

    /**
      * @brief Деструктор класса
      */
    ~SMLServer();

    /**
     * @brief Тип клиентской программы
     * Undefined - незарегистрированное подключение
     * U1Adapter - адаптер контроллера U1
     * U2Adapter - адаптер контроллера U2
     */
    enum CLIENT_TYPE {Undefined, U1Adapter, U2Adapter};

private:
    /// Web-soket сервер
    QScopedPointer<QWebSocketServer> m_server;

    /// Порт, на котором работает сервер
    qint16 m_port;

    /// Подключенные адаптеры контроллеров U1
    QList< QWebSocket* > m_u1Connections;

    /// Подключенные адаптеры контроллеров U2
    QList< QWebSocket* > m_u2Connections;

    /// Незарегистрированные подключения
    QList< QWebSocket* > m_unregistered;

    /// Необходимо ли выводить в консоль отладочные сообщения (true - вывод сообщений требуется. false - вывод сообщений не требуется.)
    bool m_debug;

    /**
     * @brief Подключает слоты к сигналам полей класса
     */
    void setupConnections();

    /**
     * @brief Отключает слоты от сигналов полей класса
     */
    void resetConnections();

    /**
     * @brief Регистрирует клиента
     * @param client указатель на сокет клиента
     * @param type тип, с которым нужно зарегистрировать клиента (U1Adapter или U2Adapter)
     */
    void registerClient(QWebSocket *client, int type);

    /**
     * @brief Преобразует бинарное сообщение от адаптера контроллера U1 в состояние контроллера U1
     * @param message сообщение от адаптера контроллера U1
     * @return структура, описывающая состояние контроллера U1
     */
    U1State parseU1BinaryMessage(QByteArray message);

signals:

    /**
     * @brief Сигнал подкючения адаптера контроллера U1
     */
    void u1Connected();

    /**
     * @brief Сигнал отключения адатпера контроллера U1
     */
    void u1Disconnected();

    /**
     * @brief Сигнал изменения состояния контроллера U1
     * @param sensors датчики, подключенные к контроллеру U1
     * @param devices устройства, подключенные к контроллеру U1
     * @param workflowState статус выполнения заданий контроллера U1 (0 - свободен. 1 - занят. >= 2 -  ошибка выполнения задания.)
     * @param lastError код последней ошибки, возникшей в процесе работы контроллера (0 - ошибок нет. Чем сильнее модуль кода ошибки отличается от 0, тем ошибка критичнее.)
     */
    void u1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, unsigned int workflowState, ERROR_CODE lastError);

    /**
     * @brief Сигнал подключения адаптера контроллера U1
     */
    void u2Connected();

    /**
     * @brief Сигнал отключения адаптера контроллера U1
     */
    void u2Disconnected();

    /**
     * @brief Сигнал изменения состояния ошибки, возникшей в работе сервера
     * @param code код ошибки (аналогичен коду ошибки, возникшей во время работы станка)
     */
    void errorOccured(ERROR_CODE code);

public slots:

    /**
     * @brief Запускает SML-сервер
     */
    void start();

    /**
     * @brief Останавливает SML-сервер
     */
    void stop();

    /**
     * @brief Осуществляет передачу собщения всем подключенным адаптерам контроллеров U1
     * @param message сериализованное сообщение для отправки
     */
    void sendMessageToU1(QByteArray message);

    /**
     * @brief Возвращает список подключенных адаптеров контроллеров U1
     * @return список подключенных адаптеров контроллеров U1 в данный момент времени
     */
    QStringList currentAdapters();

    /**
     * @brief Возвращает номер порта SML-сервера
     * @return номер порта, на котором работает SML-сервер
     */
    size_t port() const;

private slots:

    /**
     * @brief Обрабатывает сигнал отключения сервера веб-сокетов
     */
    void onQWebSocketServer_Closed();

    /**
     * @brief Обрабатывает сигнал нового подключения к серверу веб-сокетов
     */
    void onQWebSocketServer_NewConnection();

    /**
     * @brief Обрабатывает сигнал получения текстового сообщения от веб-сокета
     * @param message текстовое сообщение
     */
    void onQWebSocket_TextMessageReceived(QString message);

    /**
     * @brief Обрабатывает сигнал получения сериализованного сообщения от веб-сокета
     * @param message сериализованное сообщение
     */
    void onQWebSocket_BinaryMessageReceived(QByteArray message);

    /**
     * @brief Обрабатывает сигнал отключения веб-сокета от сервера
     */
    void onQWebSocket_Disconnected();
};

#endif // SMLRSERVER_H
