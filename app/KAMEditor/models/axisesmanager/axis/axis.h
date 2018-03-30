#ifndef AXIS_H
#define AXIS_H

#include <QObject>

#include "models/settingsmanager/settingsmanager.h"

class Axis : public QObject
{
    Q_OBJECT
public:
    explicit Axis(SettingsManager* settingsManager = nullptr, QObject *parent = nullptr);

protected:
    QString m_name;
    double m_length;
    double m_currentPosition;

    void setup(SettingsManager* settingsManager);

signals:
    void currentPositionUpdated(double newPosition);

public slots:
};

#endif // AXIS_H
