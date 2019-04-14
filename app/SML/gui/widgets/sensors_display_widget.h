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
    void addSensor(QString uid, QString label, bool state, QColor activeStateLedColor);
    void removeSensor(QString uid);
    void updateSensorData(QString uid, QString label, bool state, QColor activeStateLedColor);
    void updateSensorState(QString uid, bool state);
    void update();

private:

    struct SensorWidget{
        QString uid;
        QString label;
        bool state;
        QColor activeStateLedColor;
        QColor inactiveStateLedColor;
        SensorWidget(QString _uid, QString _label, bool _state, QColor _activeStateLedColor) :
            uid(_uid),
            label(_label),
            state(_state),
            activeStateLedColor(_activeStateLedColor),
            inactiveStateLedColor(Qt::white) {}
    };

    QList< QSharedPointer<SensorWidget> > m_sensors;
    QTableWidget* m_sensorsTable;

    QSharedPointer<SensorWidget> findSensor(QString uid);

signals:

public slots:
};

#endif // SENSORSDISPLAYWIDGET_H
