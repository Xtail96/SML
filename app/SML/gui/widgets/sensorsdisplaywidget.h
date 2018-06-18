#ifndef SENSORSDISPLAYWIDGET_H
#define SENSORSDISPLAYWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLayout>
#include <QTableWidget>
#include <QLabel>
#include <QDebug>

class SensorsDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsDisplayWidget(QWidget *parent = nullptr);
protected:
    struct{
        QString name;
        QString label;
        QColor led;
    } m_sensors;

signals:

public slots:
};

#endif // SENSORSDISPLAYWIDGET_H
