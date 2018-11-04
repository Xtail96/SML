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

    /**
     * @brief Конструктор класса
     * @param parent родительский объект в дереве объектов
     */
    explicit Adapter(QObject *parent = nullptr);

    /**
     * @brief Возвращает текущее значение состояния подключения
     * @return текущее состояние подключения (true - адаптер подключен. false - адаптер не подключен)
     */
    bool connected() const;

    /**
     * @brief Устанавливает значение состояния подключения
     *
     * Новое состояние будет установлено, только если оно отлично от текущего.
     * При смене состояния испускается соответсвующий сигнал.
     * @param connected обновленное состояние подключения
     */
    void setConnected(bool connected);

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

protected:

    /// Состояние подключения адптера (true - адаптер подключен. false - адаптер не подключен)
    bool m_connected;

    /// Состояние выполения задания адаптера (0 - адаптер совободен. 1 - адаптер занят. >= 2 - ошибка выполеннеия задания)
    int m_workflowState;

signals:

    /**
     * @brief Состояние подключения изменилось
     * @param connected обновленное состояние подключения
     */
    void connectionStateChanged(bool connected);

    /**
     * @brief Состояние выполения заданий изменилось
     * @param state обновленное состояние выполенния задний
     */
    void workflowStateChanged(int state);

public slots:
};

#endif // CONNECTION_H
