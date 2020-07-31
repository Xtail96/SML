#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "models/types/axis_state/axis_state.h"

class MotionArduinoAdapter;

class Repository : public QObject
{
    Q_OBJECT
public:
    Repository(QObject *parent = nullptr);

    QtJson::JsonObject currentState();
    void updateCurrentState(QtJson::JsonObject serialPortMessage);

private:
    QString m_serialPortName;
    QByteArray m_serialPortReadBuffer;
    QList<AxisState> m_axes;

    void loadSettings();


    friend class MotionArduinoAdapter;

signals:
public slots:
};

#endif // REPOSITORY_H
