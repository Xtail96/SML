#ifndef AXIS_H
#define AXIS_H

#include <QString>
#include <QObject>
#include <QDebug>

enum AxisId {
    X, Y, Z, A, B, C, U, V, W
};

class Axis : public QObject
{
    Q_OBJECT
public:
    explicit Axis(AxisId id, double initialPos, QObject* parent = nullptr);
    ~Axis();

    double currentPosition() const;
    void setCurrentPosition(double absPosition);

    QString axisSettings() const;

    AxisId id() const;
    QString decoratedId() const;
    static AxisId idFromStr(QString value);

    bool operator==(const Axis& other) const;
    bool operator!=(const Axis& other) const;

private:
    AxisId m_id;
    double m_currentPosition;

signals:
    void currentPositionChanged();
};

#endif // AXIS_H
