#ifndef SENSORDISPLAY_H
#define SENSORDISPLAY_H

#include <QWidget>

class SensorDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit SensorDisplay(QWidget *parent = nullptr);
protected:
    struct{
        QString name;
        QString label;
        QColor led;
    } m_sensors;

signals:

public slots:
};

#endif // SENSORDISPLAY_H
