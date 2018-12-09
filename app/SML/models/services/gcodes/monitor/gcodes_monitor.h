#ifndef GCODESMONITOR_H
#define GCODESMONITOR_H

#include <QObject>

#include "models/types/gcodes/gcodes_file_manager/gcodes_file_manager.h"

/**
 * @brief Класс Монитор состояния G-кодов
 *
 * Предназначен для отслеживания состояния файла с G-кодами в режиме реального времени.
 */
class GCodesMonitor : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Конструктор класса
     * Связывает каждый менеджер G-кодов с функциями обработчкиками (onGCodesManager_FilePathUpdated и onGCodesManager_FileContentUpdated).
     *
     * @param gcodesManager менеджер файлов G-кодов, управляющий файлом, состояние которого требуется отслеживать
     * @param parent родительский объект в дереве объектов
     */
    explicit GCodesMonitor(GCodesFileManager* gcodesManager, QObject *parent = nullptr);

signals:

    /**
     * @brief Сигнал об изменении пути до файла с G-кодом
     * @param filePath обновленный путь к файлу
     */
    void filePathUpdated(QString filePath);

    /**
     * @brief Сигнал об изменении содержимого файла с G-кодом
     * @param data обновленное содержимое файла
     */
    void fileContentUpdated(QStringList data);

protected slots:

    /**
     * @brief Испускает сигнал об изменении пути до файла с G-кодом
     * @param filePath обновленный путь к файлу
     */
    void onGCodesManager_FilePathUpdated(QString filePath);

    /**
     * @brief Испускает сигнал об изменении содержимого файла с G-кодом
     * @param data обновленное содержимое файла
     */
    void onGCodesManager_FileContentUpdated(QStringList data);
};

#endif // GCODESMONITOR_H
