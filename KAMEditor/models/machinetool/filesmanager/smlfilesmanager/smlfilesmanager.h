#ifndef SMLFILESMANAGER_H
#define SMLFILESMANAGER_H

#include <QMessageBox>
#include <QFileDialog>

#include "models/machinetool/commandsmanager/commands/commandsbuilder.h"
#include "models/machinetool/pointsmanager/point/pointsbuilder.h"

/*!
 * \brief Класс Менеджер SML-Файлов
 */
class SMLFilesManager
{
public:
    /*!
     * \brief Конструктор класса Менеджер SML-файлов
     * \param _commandsManager указатель на менеджер команд
     * \param _pointsManager указатель на менеджер точек
     * \param _axisesCount число осей станка
     */
    SMLFilesManager(CommandsManager* _commandsManager, PointsManager* _pointsManager, DevicesManager* _devicesManager, size_t _axisesCount);

    /*!
     * \brief Создает файл по указанному пути
     * \param path путь к файлу
     * \warning является статическим методом класса Менеджер SML-файлов
     */
    static void createFile(const QString path);

    /*!
     * \brief Создает новый *.7Kam файл
     */
    void new7KamFile();

    /*!
     * \brief Открывает *.7Kam файл
     */
    void open7KamFile();

    /*!
     * \brief Открывает *.7Kam файл по указанному пути
     * \param path путь к файлу
     */
    void open7KamFile(QString path);

    /*!
     * \brief Сохраняет *.7Kam файл
     */
    void save7KamFile();

    /*!
     * \brief Сохраняет *.7Kam файл в явно указанную директорию
     */
    void save7KamFileAs();

    /*!
     * \brief Добавляет к текущей программе *.7Kam файл
     * Путь до текущего файла при этом остается тем же
     */
    void add7KamFile();

private:

    /*!
     * \brief Указатель на менеджер команд
     */
    CommandsManager* commandsManager;

    /*!
     * \brief Указатель на менеджер точек
     */
    PointsManager* pointsManager;

    DevicesManager* devicesManager;

    /*!
     * \brief Число осей станка
     */
    size_t axisesCount;

    /*!
     * \brief Путь до текущего файла
     */
    QString filePath;
    //bool changed;

    /*!
     * \brief Сохраняет команды в формате *.7Kam в указанный файл
     * \param file файл, куда требуется сохранить команды
     */
    void saveCommands(QFile& file);

    /*!
     * \brief Сохраняет точки в формате *.7Kam в указанный файл
     * \param file файл, куда требуется сохранить точки
     */
    void savePoints(QFile& file);

    /*!
     * \brief Очищает контейнеры менеджера команд и менеджера точек
     */
    void resetContainers();

    /*!
     * \brief Очищает контейнер менеджера команд
     */
    void resetCommands();

    /*!
     * \brief Очищает контейнер менеджера точек
     */
    void resetPoints();

    /*!
     * \brief Читает содержимое из файла по указанному пути
     * \param path путь к файлу
     * \return содержимое файла в формате строки
     */
    QString readFileInfo(QString path);

    /*!
     * \brief Заполняет контенеры менеджера команд и менеджера точек по строке
     * \param content содержимое для заполнения контейнеров
     */
    void transferToSML(QString content);

    /*!
     * \brief Зполняет контейнер менеджера команд по строке
     * \param commandsStrings содержимое для заполнения контейнера менеджера команд
     */
    void transferToSMLCommands(QStringList commandsStrings);

    /*!
     * \brief Заполняет контейнер менеджера точек по строке
     * \param pointsStrings содержимое для заполнения контейнера менеджера точек
     */
    void transferToSMLPoints(QStringList pointsStrings);

    /*!
     * \brief Создает SML-Команду по строке
     * \param commandString строка, описывающая SML-Команду
     * \return умный указатель на SML-Команду
     */
    std::shared_ptr<Command> makeCommand(QString commandString);

    /*!
     * \brief Создает SML-Точку по строке
     * \param pointString строка, описывающая SML-Точку
     * \return умный указатель на SML-Точку
     */
    Point *makePoint(QString pointString);

    /*!
     * \brief Создает строку, описывающую SML-Команду в формате *.7Kam
     * \param commmand умный указатель на SML-команду
     * \return строка, описывающая SML-Команду в формате *.7Kam
     */
    QString makeCommandString(std::shared_ptr<Command> commmand);

    /*!
     * \brief Создает строку, описывающую SML-Точку в формате *.7Kam
     * \param point умный указатель на SML-Точку
     * \return строка, описывающая SML-Точку в формате *.7Kam
     */
    QString makePointString(std::shared_ptr<Point> point);

};

#endif // SMLFILESMANAGER_H
