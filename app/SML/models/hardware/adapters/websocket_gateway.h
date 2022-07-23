#ifndef WEBSOCKETGATEWAY_H
#define WEBSOCKETGATEWAY_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

class WebSocketGateway : public QObject
{
    Q_OBJECT
public:
    /// Конструктор класса.
    explicit WebSocketGateway(QObject *parent);

    /// Деструктор класса.
    ~WebSocketGateway();

    /// Запускает сервер.
    bool open(quint16 port);

    /// Останавливает сервер.
    void close();

    /// Возвращает порт сервера.
    quint16 port() const;

    bool isOpen();

private:
    /// Web-soket сервер.
    QWebSocketServer m_server;

    /// Порт, на котором работает сервер.
    quint16 m_port;

    /// Мета-информация о подключенных слотах.
    QList<QMetaObject::Connection> m_slotsInfo;

    /// Подключает необходимые слоты.
    void setupSlots();

    /// Отключает слоты.
    void resetSlots();

signals:
    /// Произошло подключение нового сокета.
    void newConnection(QWebSocket* s);

    /// Сервер остановлен.
    void serverStopped();
};

#endif // WEBSOCKETGATEWAY_H
