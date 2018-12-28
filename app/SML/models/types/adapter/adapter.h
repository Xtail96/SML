#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

/**
 * @brief Класс Адаптер
 *
 * Высокоуровневое представление адаптера в системе.
 * Адптер не хранит код ошибки, возникшей в процессе работы во избежание дублирования.
 * Всю работу с ошибками берет на себя MachineTool.
 */
class Adapter : public QObject
{
    Q_OBJECT
public:

    enum Type {U1, U2};

    /**
     * @brief Конструктор класса
     * @param parent родительский объект в дереве объектов
     */
    explicit Adapter(Type type, QObject *parent = nullptr);

    /**
     * @brief Возвращает текущее значение состояния подключения
     * @return текущее состояние подключения (true - адаптер подключен. false - адаптер не подключен)
     */
    bool connectionState() const;

    /**
     * @brief Устанавливает значение состояния подключения
     *
     * Новое состояние будет установлено, только если оно отлично от текущего.
     * При смене состояния испускается соответсвующий сигнал.
     * @param connected обновленное состояние подключения
     */
    void setConnectionState(bool connectionState);

    /**
     * @brief Возвращает текущее значение выполенения задания
     * @return код выполенения работ адаптером
     */
    int workflowState() const;

    /**
     * @brief Устанавливает новое значение выполения задания
     *
     * Новое состояние будет установлено, только если оно отлично от текущего.
     * При смене состояния испускается соответсвующий сигнал.
     * @param workflowState код выполнения задания
     */
    void setWorkflowState(int workflowState);

    /**
     * @brief Возвращает тип адаптера
     * @return тип адаптера (U1 или U2).
     */
    Adapter::Type type() const;

protected:

    /// Тип адаптера (U1 или U2)
    Type m_type;

    /// Состояние подключения адптера (true - адаптер подключен. false - адаптер не подключен)
    bool m_connected;

    /// Состояние выполения задания адаптера (0 - адаптер совободен. 1 - адаптер занят. >= 2 - ошибка выполеннеия задания)
    int m_workflowState;

signals:

    /**
     * @brief Состояние подключения изменилось
     */
    void connectionStateChanged();

    /**
     * @brief Состояние выполения заданий изменилось
     */
    void workflowStateChanged();

public slots:
};

#endif // CONNECTION_H
