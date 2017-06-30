#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QCoreApplication>
#include <QFile>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <QMessageBox>
#include <memory>

/**
 * @brief Класс для работы с настройками станка
 *
 * Данный класс отвечает за:
 * - считывание настрока станка по заданному пути, либо пути по умолчанию
 * - генерацию настроек станка по умолчанию
 * - экспорт настроек по произвольному пути
 * - поиск и изменение значения по паре группа-ключ
 * - сохранение настроек
 */
class SettingsManager
{
private:
    /// Путь, где по умолчанию хранится файл с настройками
    const QString defaultSettingsIniPath = "settings.ini";

    /// Класс, непосредственно отвечающий за хранение "группа-ключ-значение"
    std::shared_ptr<QSettings> settings;

public:
    /**
     * @brief Импортирует настройки из файла, находящегося в директории по умолчанию
     */
    SettingsManager();
    /**
     * @brief Импортирует настройки из заданного файла
     * @param settingsIniPath путь к файлу с настройками
     */
    SettingsManager(QString settingsIniPath);

    ~SettingsManager();

    /**
     * @brief Сохраняет настройки в текущий файл
     */
    void saveSettings();

    /**
     * @brief Экспортирует настройки по заданному пути
     * @param path путь, куда будут экспортированы настройки
     */
    void exportSettings(QString path);

    /**
     * @brief Позволяет получить значение по заданным группе и ключу
     * @param group имя группы
     * @param key ключ
     * @return полученное по группе и ключу значение
     * \warning Если по заданному ключу не содержится никакое значение, выбрасывает исключение invalid_argument
     */
    QVariant get(QString group, QString key);

    /**
     * @brief Позволяет установить значение по заданным группе и ключу
     * @param group имя группы
     * @param key ключ
     * @param value значение, которое следует установить
     */
    void set(QString group, QString key, QVariant value);

    /**
     * @brief Генерирует настройки станка по умолчанию
     */
    void generateDefaultSettings();
};

#endif // SETTINGSMANAGER_H
