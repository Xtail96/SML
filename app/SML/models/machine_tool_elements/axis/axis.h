#ifndef AXIS_H
#define AXIS_H

#include <QString>
#include <QObject>
#include <QDebug>

class Axis : public QObject
{
    Q_OBJECT
public:
    explicit Axis(QString id, double initialPos, QObject* parent = nullptr);
    ~Axis();

    double currentPosition() const;
    void setCurrentPosition(double currentPosition);

    QString axisSettings() const;

    QString id() const;

private:
    QString m_id;
    double m_currentPosition;

signals:
    void currentPositionChanged();
};

#endif // AXIS_H
