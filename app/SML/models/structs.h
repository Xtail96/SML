#ifndef STRUCTS_H
#define STRUCTS_H
#include <string>
#include <vector>
#include <map>

#include <QDebug>

#include "models/exceptions/exceptions.h"

typedef unsigned char byte;
typedef QList<byte> byte_array;

/*!
 * \brief Коды всех возможных ошибок
 * (нужны для более строгой работы с ошибками, транслируются в SmlErrorFlags в
 * MachineTool::setErrorFlag(ERROR_CODE e))
 */
enum ERROR_CODE
{
    OK,
    INVALID_SETTINGS,
    U1_DISCONNECTED,
    U2_DISCONNECTED,
    SYNC_STATE_ERROR,
    PROGRAM_EXECUTION_ERROR,
    UNKNOWN_ERROR
};

bool axisesNamesComparator(QString a1, QString a2);

/*!
 * \brief Объект "Имена осей"
 * \brief Данная структура содержит список всех доступных осей и их имен для использования в системе управления.
 * \warning Имена оси - заглавне латинские буквы;
 * \warning Даная структура не имеет имени и существует только один объект "axisNames" такого типа;
 *
 * Способы взаимодействия со структурой:
 * 1) Получения имени оси(значения) по ее индексу(ключу);
 * 2) Получения индекса оси(ключа) по ее имени(значению);
 */
struct
{
public:
    /// \details Словарь имен всех осей в формате <ключ, значение> = <индекс оси, имя оси>
    std::map<size_t, QString> axisesNames =
    {
        {0, "X"},
        {1, "Y"},
        {2, "Z"},
        {3, "A"},
        {4, "B"},
        {5, "C"},
        {6, "U"},
        {7, "V"},
        {8, "W"}
    };

    /// \details Получение имени оси(значения) по ключу(индексу);
    QString getNameByKey(const size_t &value)
    {
        if(value < axisesNames.size())
        {
            return axisesNames[value];
        }
        else
        {
            throw InvalidArgumentException("Axis does not exist");
        }
    }

    /// \details Получение индекса(ключа) по имени оси(значению);
    size_t getKeyByName(const QString &s) const
    {
        for(auto it : axisesNames)
        {
            if(it.second == s)
            {
                return it.first;
            }
        }

        throw InvalidArgumentException("Unknown Axis");
    }

    /// \details Проверка сущетсвания оси с указанным именем;
    bool contains(const QString &name) const
    {
        for(auto it : axisesNames)
        {
            if(it.second == name)
            {
                return true;
            }
        }

        return false;
    }

    QStringList sort(QStringList axisesNames)
    {
        QList< QPair<size_t, QString> > axisesMeta = {};
        QStringList unresolved = {};
        for(auto axisName : axisesNames)
        {
            if(this->contains(axisName))
            {
                axisesMeta.append(QPair<size_t, QString>(this->getKeyByName(axisName), axisName));
            }
            else
            {
                unresolved.append(axisName);
            }
        }

        std::sort(axisesMeta.begin(), axisesMeta.end(), [] (QPair<size_t, QString> a1, QPair<size_t, QString> a2) {
            return a1.first < a2.first;
        });

        QStringList result = {};
        for(auto axisesMetaItem : axisesMeta)
        {
            result.append(axisesMetaItem.second);
        }

        return result + unresolved;
    }
} SML_AXISES_NAMES;



/*!
 * \brief Структура 3D-Точка
 * Используется для 3D-представления команд, выбранных пользователем
 */
struct Point3D
{
    /// Координата точки по оси X
    double x;

    /// Координата точки по оси Y
    double y;

    /// Координата точки по оси Z
    double z;

    /*!
     * \brief Конструктор 3D-Точки
     * \param _x - координата точки по оси X
     * \param _y - координата точки по оси Y
     * \param _z - координата точки по оси Z
     */
    Point3D(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
};

/*!
 * \brief Структура SML-цвета
 * Возвращает цвет в формтае QString с помощью соответсвующего static метода
 */
struct SmlColors
{
    /*!
     * \brief Возвращает зеленый цвет
     * \return #2e8b57
     */
    static QString green()
    {
        return QString("#2e8b57");
    }

    /*!
     * \brief Возвращает светло-зеленый цвет
     * \return #55bb55
     */
    static QString lightGreen()
    {
        return QString("#55bb55");
    }

    /*!
     * \brief Возвращает красный цвет
     * \return #b22222
     */
    static QString red()
    {
        return QString("#b22222");
    }

    /*!
     * \brief Возвращает серый цвет
     * \return #333
     */
    static QString gray()
    {
        return QString("#333");
    }

    /*!
     * \brief Возвращает светло-серый цвет
     * \return #dfdfdf
     */
    static QString lightGray()
    {
        return QString("#888");
    }

    /*!
     * \brief Возвращает белый цвет
     * \return #fff
     */
    static QString white()
    {
        return QString("#fff");
    }

    /*!
     * \brief Возвращает голубой цвет
     * \return #4682b4
     */
    static QString blue()
    {
        return QString("#4682b4");
    }

};

/*!
 * \brief Перечисление идентификаторов команд
 */
enum COMMANDS_IDS
{
    /// Дуга
    CMD_ARC,

    /// Относительная дуга
    CMD_RELARC,

    /// ТТТ-Дуга
    CMD_TTTARC,

    /// ТТТZ-Дуга
    CMD_TTTZARC,

    /// Вызов подпрограммы
    CMD_CALL,

    /// Окончить
    CMD_END,

    /// Цикл
    CMD_CYCLE,

    /// Конец цикла
    CMD_END_CYCLE,

    /// Переход на метку
    CMD_GOTO,

    /// Метка
    CMD_LABEL,

    /// Линия
    CMD_LINE,

    /// Включить
    CMD_SWITCH_ON,

    /// Выключить
    CMD_SWITCH_OFF,

    /// Парк
    CMD_PARK,

    /// Пауза
    CMD_PAUSE,

    /// Подпрограмма
    CMD_FUNCTION,

    /// Комментарий
    CMD_COMMENT,

    /// Вернуться
    CMD_RETURN,

    /// Поворот
    CMD_ROTATE,

    /// Масштаб
    CMD_SCALE,

    /// Скорость
    CMD_SPEED,

    /// Стоп
    CMD_STOP,

    /// В Парк
    CMD_TO_PARK,

    /// В Ноль
    CMD_TO_ZERO,

    /// ТТ-Линия
    CMD_TTLINE,

    /// Сплайн
    CMD_SPLINE,

    /// ТТТТ-Сплайн
    CMD_TTTTSPLINE,

    /// Ноль
    CMD_ZERO,

    /// Переменная
    CMD_VARIABLE
};

/*!
 * \brief Структура Идентификаторы команд
 * Задает каждой команде идентификатор из перечисления идентификаторов
 * Позволяет получить идентификатор команды по ее имени
 */
struct
{
    /*!
     * \brief Карта имен команд и соответствующих им идентификаторов
     * Ключь - имя команды
     * Значение - идентификатор команд
     */
    std::map<std::string, int> ids =
    {
        {"Линия", CMD_LINE},
        {"ТТ-Линия", CMD_TTLINE},
        {"Дуга", CMD_ARC},
        {"Относительная дуга", CMD_RELARC},
        {"ТТТ-Дуга", CMD_TTTARC},
        {"ТТТZ-Дуга", CMD_TTTZARC},
        {"Сплайн", CMD_SPLINE},
        {"ТТТТ-Сплайн", CMD_TTTTSPLINE},
        {"Поворот", CMD_ROTATE},
        {"Масштаб", CMD_SCALE},
        {"Метка", CMD_LABEL},
        {"На метку", CMD_GOTO},
        {"Цикл", CMD_CYCLE},
        {"Конец цикла", CMD_END_CYCLE},
        {"Попрограмма", CMD_FUNCTION},
        {"Вернуться", CMD_RETURN},
        {"Вызов подпрограммы", CMD_CALL},
        {"***", CMD_COMMENT},
        {"Обнулить", CMD_ZERO},
        {"Окончить", CMD_END},
        {"Включить", CMD_SWITCH_ON},
        {"Выключить", CMD_SWITCH_OFF},
        {"Скорость", CMD_SPEED},
        {"Пауза", CMD_PAUSE},
        {"Стоп", CMD_STOP},
        {"В Ноль", CMD_TO_ZERO},
        {"Переменная", CMD_VARIABLE}
    };

    /*!
     * \brief Возвращает идентификатор команды по ее имени
     * \param name - имя команды
     * \return идентификатор команды
     */
    int getId(const std::string &name) const
    {
        int commandNumber = -1;
        for(auto it : ids)
        {
            if(it.first == name)
            {
                commandNumber = it.second;
                break;
            }
        }
        return commandNumber;
    }

} CommandsIds;

#endif // STRUCTS_H
