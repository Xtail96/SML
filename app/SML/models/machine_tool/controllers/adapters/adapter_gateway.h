#ifndef ADAPTERGATEWAY_H
#define ADAPTERGATEWAY_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

/**
 * @brief Точка подключения адаптеров к системе.
 */
class AdapterGateway : public QObject
{
    Q_OBJECT
public:
    /// Конструктор класса.
    explicit AdapterGateway(QObject *parent);

    /// Деструктор класса.
    ~AdapterGateway();

    /// Запускает сервер.
    bool startServer(quint16 port);

    /// Останавливает сервер.
    void stopServer();

    /// Возвращает порт сервера.
    quint16 port() const;

private:
    /// Web-soket сервер.
    QWebSocketServer m_server;

    /// Порт, на котором работает сервер.
    quint16 m_port;

    /// Мета-информация о подключенных слотах.
    QList<QMetaObject::Connection> m_connections;

    /// Подключает необходимые слоты.
    void setupConnections();

    /// Отключает слоты.
    void resetConnections();

signals:
    /// Произошло подключение нового сокета.
    void newConnection(QWebSocket* s);

    /// Сервер остановлен.
    void serverStopped();
};

#endif // ADAPTERGATEWAY_H
