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
    void addSensor(QString name, QString label, bool state, QColor led);
    void removeSensor(QString name);
    void updateSensorState(QString name, bool state);
    void update();
protected:

    struct SensorWidget{
        QString name;
        QString label;
        bool state;
        QColor activeStateLedColor;
        QColor inactiveStateLedColor;
        SensorWidget(QString _name, QString _label, bool _state, QColor _activeStateLedColor) :
            name(_name),
            label(_label),
            state(_state),
            activeStateLedColor(_activeStateLedColor),
            inactiveStateLedColor(Qt::white) {}
    };

    QList< QSharedPointer<SensorWidget> > m_sensors;
    QTableWidget* m_sensorsTable;

    QSharedPointer<SensorWidget> findSensor(QString name);

signals:

public slots:
};

#endif // SENSORSDISPLAYWIDGET_H
