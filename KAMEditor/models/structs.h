#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <vector>
#include <map>

#include <QDebug>

typedef unsigned char byte;
typedef std::vector<byte> byte_array;

struct VectorDouble
{
    double x;
    double y;
    double z;

    double a;
    double b;

    VectorDouble(double _x = 0, double _y = 0, double _z = 0, double _a = 0, double _b = 0) : x(_x), y(_y), z(_z), a(_a), b(_b) {}
};

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
    /// \details Словарь имен всех осей в формате <ключ, значение> = <индекс оси, имя оси>
    std::map<unsigned int, std::string> axisNames =
    {
        {0, "X"},
        {1, "Y"},
        {2, "Z"},
        {3, "A"},
        {4, "B"},
        {5, "C"},
        {6, "D"},
        {7, "E"},
        {8, "F"},
        {9, "G"},
        {10, "H"},
    };

    /// \details Получение имени оси(значения) по ключу(индексу);
    std::string getNameByKey(const unsigned int &value)
    {
        if(value < axisNames.size())
        {
            return axisNames[value];
        }
        else
        {
            throw std::invalid_argument("Axis does not exist");
        }
    }

    /// \details Получение индекса(ключа) по имени оси(значению);
    int getKeyByName(const std::string &s) const
    {
        int axisNumber = -1;
        for(auto it : axisNames)
        {
            if(it.second == s)
            {
                axisNumber =  it.first;
                break;
            }
        }
        if(axisNumber != -1)
        {
            return axisNumber;
        }
        else
        {
            throw std::invalid_argument("Unknown Axis");
        }
    }
} axisesNames;

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

#endif // VECTOR_H
