#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

#include "models/structs.h"
#include "models/machinetool/machinetool.h"
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevicemanager.h"
#include "controllers/mainwindowcontroller/mainbridge/mainbridge.h"

/*!
 * \brief Класс Контроллер главного окна
 * Отвечает за всю логику работы с элементами главного окна
 */
class MainWindowController : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор класса Контроллер главного окна
     * \param parent - указатель на объект (по умолчанию равен nullptr)
     */
    explicit MainWindowController(QObject *parent = nullptr);

    /*!
      * \brief Деструктор класса Контроллер главного окна
      */
    ~MainWindowController();

    QStringList getSensorsNames();
    QStringList getSensorsParametrsNames();
    QList<QStringList> getSensorsSettings();
    QList<QColor> getSensorsLeds();

    QStringList getDevicesNames();
    QStringList getDevicesParametrsNames();
    QList<QStringList> getDevicesSettings();
    QStringList getOnScreenDevicesNames();
    QList<bool> getOnScreenDevicesStates();

    QStringList getAxisesNames();
    QStringList getAxisesParametrsNames();
    QList<QStringList> getAxisesSettings();

protected:
    /*!
     * \brief Указатель на станок, к которому требуется подключиться
     */
    MachineTool* machineTool;
#ifdef Q_OS_WIN
    /*!
     * \brief Указатель на класс для взаимодействия с контроллером u1 по usb
     * \warning с помощью данного объекта, взаимодействие по usb осуществляется только в операционной системе windows
     */
    UsbXpressDeviceManager* u1Manager;
#endif
    /*!
     * \brief Указатель на мост для связи с классом Главное окно
     */
    MainBridge* mainBridge;

signals:
    /// Настройки станка загружены
    void machineToolSettingsIsLoaded();

    /// Контроллер u1 подключен
    void u1Connected();

    /// Контроллер u1 отключен
    void u1IsDisconnected();

public slots:
    void loadMachineToolSettings();
    void connectWithU1();
};

#endif // MAINWINDOWCONTROLLER_H
