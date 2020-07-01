#ifndef ADAPTERSERVER_H
#define ADAPTERSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

class AdapterServer : public QObject
{
    Q_OBJECT
public:
    /// Конструктор класса
    explicit AdapterServer(quint16 port, QObject *parent);

    /// Деструктор класса
    ~AdapterServer();

    /// Запускает сервер
    bool startServer();

    /// Останавливает сервер
    void stopServer();

    /// Возвращает порт сервера
    quint16 port() const;

private:
    /// Web-soket сервер
    QWebSocketServer m_server;

    /// Порт, на котором работает сервер
    quint16 m_port;

    /// Мета-информация о подключенных слотах
    QList<QMetaObject::Connection> m_connections;

    /// Подключает необходимые слоты
    void setupConnections();

    /// Отключает слоты
    void resetConnections();

signals:
    /// Произошло подключение нового сокета
    void newConnection(QWebSocket* s);

    /// Сервер остановлен
    void serverStopped();
};

#endif // ADAPTERSERVER_H
