#ifndef SENSORSDISPLAYWIDGET_H
#define SENSORSDISPLAYWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>


class SensorsDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsDisplayWidget(QWidget *parent = nullptr);
    void addSensor(QString name, QString label, QColor led);
    void removeSensor(QString name);
    void updateSensorState(QString name, QColor led);
    void update();
protected:

    struct SensorWidget{
        QString name;
        QString label;
        QColor led;
        SensorWidget(QString _name, QString _label, QColor _led) :
            name(_name),
            label(_label),
            led(_led){}
    };

    QList< QSharedPointer<SensorWidget> > m_sensors;
    QTableWidget* m_sensorsTable;

    QSharedPointer<SensorWidget> findSensor(QString name);

signals:

public slots:
};

#endif // SENSORSDISPLAYWIDGET_H
