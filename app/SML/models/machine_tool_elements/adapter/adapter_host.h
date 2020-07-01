#ifndef ADAPTERHOST_H
#define ADAPTERHOST_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

class AdapterHost : public QObject
{
    Q_OBJECT
public:
    /// Конструктор класса
    explicit AdapterHost(quint16 port, QObject *parent);

    /// Деструктор класса
    ~AdapterHost();

    /// Запускает сервер
    bool startServer();

    /// Останавливает сервер
    void stopServer();

    /**
     * @brief Отправляет сообщение
     * @param dest - целевой сокет
     * @param message - сообщение
     * @return количество переданых байт
     */
    qint64 sendMessage(QWebSocket* dest, QString message);

    /**
     * @brief Отправляет сообщение
     * @param dest - целевой сокет
     * @param message - сообщение
     * @return количество переданых байт
     */
    qint64 sendMessage(QWebSocket* dest, QByteArray message);

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

#endif // ADAPTERHOST_H
