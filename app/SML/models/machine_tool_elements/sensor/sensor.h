#ifndef SENSOR_H
#define SENSOR_H

#include <QColor>

#include "models/structs.h"

/**
 * @brief Класс Датчик
 * Базовый тип, описывающий любой из датчиков станка
 */
class Sensor : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса Датчик
     * @param uid уникальный идентификатор (имя) датчика
     * @param label подпись датчика для вывода в интерфейс
     * @param portNumber номер порта, к которому подключен датчик
     * @param inputNumber номер входа, к которому подключен датчик
     * @param boardName навание платы, к которой подключен датчик (u1 / u2)
     * @param inputActiveState состояние входа (логический ноль или логическая единица), при котором датчик считается активным
     * @param color цвет индикатора датчика
     * @param parent родительский объект
     */
    Sensor(QString uid,
           QString label,
           size_t portNumber,
           size_t inputNumber,
           QString boardName,
           bool inputActiveState,
           QColor color,
           QMap<QString, double> position,
           QObject *parent = nullptr);

    /**
     * @brief Оператор меньше для порядковой сортировки датчиков
     */
    bool operator<(const Sensor &sensor);

    /**
     * @brief Оператор равенства для сравнения датчиков
     */
    bool operator==(const Sensor &sensor);

    /**
     * @brief Возвращает текущее состояние входа, к которому подключен датчик
     * @return текущее состояние входа, к которому подключен датчик. true - есть напряжение на входе. false - нет напряжения на входе.
     */
    bool getInputCurrentState() const;

    /**
     * @brief Обновляет текущее состояния входа, если новое значение НЕ совпадает с текущим
     * @param value - новое состояние входа, к которому подключен датчик
     */
    void setInputCurrentState(bool value);

    /**
     * @brief Возвращает номер порта датчика
     * @return номер порта, к которому подключен датчик
     *
     * Порт датчика приходит снаружи в конструктор датчика.
     */
    size_t getPortNumber() const;

    /**
     * @brief Возвращает номер входа датчика
     * @return номер входа, к которому подключен датчик
     */
    size_t getInputNumber() const;

    /**
     * @brief Возвращает уникальный идентификатор датчика
     * @return уникальный идентификатор (имя) датчика
     */
    QString getUid() const;

    /**
     * @brief Возвращает имя платы, к которой подключен датчик
     * @return имя платы, к которой подключен датчик (u1 / u2)
     */
    QString getBoardName() const;

    /**
     * @brief Возвращает активное состояние входа, к которому подключен датчик
     * @return состояние входа (логический ноль или логическая единица), при котором датчик считается активным
     */
    bool getInputActiveState() const;

    /**
     * @brief Возвращает цвет индикатора активного датчика
     * @return цвет индикатора, который необходмо установить при срабатывании датчика
     *
     * В системе, для наглядности, у каждого датчика задается цвет индикатора, который необходимо выводить
     * в интерфейс при срабатывании датчика.
     */
    QColor getActiveStateLedColor() const;

    /**
     * @brief Проверяет сработал ли датчик
     * @return состояние датчика. true - датчик активен в данный момент времени. false - датчик не активен в данный момент времени.
     */
    bool isEnable();

    /**
     * @brief Возврщает неуникальное имя датчика
     * @return имя датчика, для вывода в интерфейс
     *
     * @warning Этот параметр нужно использовать исключительно для отображения имени датчика в интерфейсе.
     * @warning Поиск датчика по этому параметру проводить нельзя.
     */
    QString getLabel() const;

    /**
     * @brief Возвращает актуальные настройки датчика
     * @return настройки датчика в виде строки, формата
     * "setting1_key:setting1_value;setting2_key:setting2_value"
     */
    QString getSettings();

    QMap<QString, double> getPosition() const;
    void setPosition(const QMap<QString, double> &position);

protected:
    /// Уникальный идентификатор (имя) датчика
    QString m_uid;

    /// Пользовательское имя датчика
    QString m_label;

    /// Имя платы, к которой подключен датчик (u1 / u2)
    QString m_boardName;

    /// Номер порта, ко входу которого подключен датчик
    size_t m_portNumber;

    /// Номер входа, к которому подключен датчик
    size_t m_inputNumber;

    /// Состояние входа, при котором датчик считается активным
    bool m_inputActiveState;

    /**
     * @brief Текущее сотояние входа (есть напряжение / нет напряжения)
     *
     * @warning Это "сырое" состояние датчика, никак не говорящее о том, сработал он или нет.
     * Дело в том, что некторые датчики при срабатывании устанавливают на входе в логический ноль (большинство),
     * а некоторые - логическую единицу.
     */
    bool m_inputCurrentState;

    /// Цвет индикатора датчика
    QColor m_activeStateLedColor;

    QMap<QString, double> m_position;

signals:
    /**
     * @brief Сигнал об изменении состояния датчика
     * @param name уникальный идентификатор датчика
     * @param enable обновленное состояние датчика. true - датчик активен. false - датчик не активен.
     */
    void stateChanged(QString name, bool enable);

public slots:

    /**
     * @brief Обновляет текущее состояние входа, к которому подключен датчик
     * @param state обновленное состояние входа, к которому подключен датчик
     */
    void updateInputState(bool state);
};

#endif // SENSOR_H
