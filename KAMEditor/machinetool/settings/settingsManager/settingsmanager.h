#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <algorithm>
#include <map>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

/*!
 * \brief Класс "Менеджер Настроек"
 * \brief Данный класс позволяет осуществлять взаимодействие с файлом настроек станка.
 * \warning Данный класс, может считывать файл настроек станка под управлением SML-02, но не обеспечивает обратную совметимость (сохраняет настройки в другом формате).
 *
 * Способы взаимодействия с классом:
 * 1) Получение настроек станка;
 * 2) Чтение настроекс танка из файла;
 * 2) Запись настроек станка в файл;
 * 4) Импорт настроек станка из файла;
 * 5) Экспорт настроек станка в файл;
 */

class SettingsManager
{
private:
    /// Настройки станка в формате словаря
    std::map<std::string, std::string> settingsMap;

    /// Директория для сохранения настроек
    std::string settingsPath = "settings.ini";
public:
    SettingsManager();

    //! Метод для чтения настроек из файла по указанному адресу.
    /// \details путь передается в качестве параметра (константной ссылки);
    std::string readSettings(const std::string &path);

    //! Метод для записи настроек в файл по указанному адресу.
    /// \details путь передается в качестве параметра (константной ссылки);
    void writeSettings(const std::string &path);

    //! Метод для импортирования настроек станка;
    void importSettings();

    //! Метод для экспортирования настроек станка;
    void exportSettings();
    //void setupToMachineTool();

    //! Методы для чтения файла настроек:
    /// \details
    char push_backToName(const char &e);

    /// \details Метод удаления специальных символов переноса строки '\r' из строки, считанной из файла настроек;
    std::string eraseSlashRSymbols(const std::string &settingsString);

    /// \details Метод для заполнения словаря настроек по строке, содержащей все настройки;
    void parseSettings(const std::string &settings);

    /// \details Метод выделения из строки, содержащей все настройки, отдельной настройки ф ормате пары строк <ключ, значение>;
    std::pair<std::string, std::string> parseSettingsStep(const std::string &settings, unsigned int &position, const std::string &name);

    //! Методы для получения и установки значений:
    /// \details получения словаря с настройками;
    std::map<std::string, std::string> getSettings();

    /// \details метод получения пути до директории, содержащей файл с настройками станка;
    QString getSettingsPath();
};

#endif // SETTINGSMANAGER_H
