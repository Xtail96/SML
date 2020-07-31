#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QFile>
#include <QFileDialog>

#include "models/structs.h"
#include "models/settings_manager/settings_manager.h"
#include "models/machine_tool/controllers/motion_controller/axis/point.h"
#include "./gcodes/gcodes_file_manager/gcodes_file_manager.h"

class MachineTool;

/**
 * @brief Класс Репозиторий.
 *
 * Предназначен для хранения всей оперативной информации о станке:
 * подключения, список устройств и датчиков и их состояния, состояния осей,
 * текущие координаты и прочее.
 */
class Repository : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса
     * @param parent родительский объект
     */
    explicit Repository(QObject *parent = nullptr);

    // Settings

    /**
     * @brief Экспортирует настройки станка в *.ini файл
     */
    void exportSettings();

    /**
     * @brief Импортирует настройки станка из *.ini файла
     */
    void importSettings();

    // Adapters

    /**
     * @brief Возвращает порт, на котором работает сервер
     * @return строковое представления номера порта
     */
    QString getServerPort();

    // Points

    /**
     * @brief Добавляет точку
     * @param coordinates координаты точки
     */
    void addPoint(QMap<QString, double> coords);

    /**
     * @brief Возвращает список координат всех доступных точек
     * @return список координат всех доступных точек
     */
    QList<Point> getPoints();

    /**
     * @brief Возвращает координаты точки по ее индексу
     * @param index индекс (номер, идентификатор) точки
     * @return координаты точки
     */
    Point getPoint(unsigned int index);

    /**
     * @brief Удаляет точку
     * @param index индекс (номер, идентификатор) точки
     */
    void deletePoint(unsigned int index);

    /**
     * @brief Обнновляет координаты точки
     * @param coordinates новые координаты точки
     * @param index индекс (номер, идентификатор) точки
     */
    void updatePoint(QMap<QString, double> coordinates, unsigned int index);

    Point createEmptyPoint();

    // Program

    /**
     * @brief Устанавливает текущее значение УП в G-Codes
     * @param data УП в G-Codes
     */
    void setGCodes(const QString &data);

    /**
     * @brief Возвращает текущую УП в G-Codes
     * @return УП в G-Codes
     */
    QStringList getGCodesProgram();

    /**
     * @brief Возвращает путь до открытого файла
     * @param type тип файла (gcodes / sml. По умолчанию gcodes)
     * @return путь до текущего файла
     */
    QString getFilePath(QString type = "gcodes");

    /**
     * @brief Открывает файл с УП в G-Codes
     */
    void openGCodesFile();

    /**
     * @brief Сохраняет УП в G-Codes в тот же файл
     * @param data УП в G-Codes
     */
    void saveGCodesFile(const QString data);

    /**
     * @brief Сохраняет УП в G-Codes в другой файл
     * @param data УП в G-Codes
     */
    void saveGCodesFileAs(const QString data);

    /**
     * @brief Инициализирует новый файл G-Codes
     */
    void newGCodesFile();

    /**
     * @brief Добавляет содержимое файла G-Codes к текущей УП
     * @param data текущая УП в G-Codes
     */
    void addGCodesFile(const QString data);

    // Options

    /**
     * @brief Возвращает список доступных опций
     * @return список доступных опций
     */
    QStringList getOptionsLabels();

    double getMovementStep() const;
    void setMovementStep(double movementStep);

    Point getZeroCoordinates() const;
    void setZeroCoordinates(const Point &zeroCoordinates);

    Point getParkCoordinates() const;
    void setParkCoordinates(const Point &parkCoordinates);

private:
    /// Менеджер настроек
    SettingsManager m_settingsManager;

    /// Менеджер файлов G-Codes
    GCodesFileManager m_gcodesFilesManager;

    QList<Point> m_points;

    /// Координаты точки Ноль
    Point m_zeroCoordinates;

    /// Координаты точки Парк
    Point m_parkCoordinates;

    /// Максимальная скорость перемещения
    double m_velocity;

    /// Дискретность перемещений из наладки
    double m_movementStep;

    /// Класс-друг!
    friend class MachineTool;

signals:
    void errorOccurred(ERROR_CODE code);
    void pointsUpdated();

public slots:

private slots:
};

#endif // REPOSITORY_H
