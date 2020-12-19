#ifndef AXISSTATE_H
#define AXISSTATE_H

#include <QString>
#include <QObject>
#include <QDebug>

enum AxisId {
    X, Y, Z, A, B, C, U, V, W
};

class AxisState
{
public:
    AxisState(AxisId id, double currentPosition);
    ~AxisState();

    double currentPositionFromBase() const;
    double currentPositionFromZero() const;
    void setCurrentPosition(double absPosition);

    double zeroPosition() const;
    double parkPosition() const;
    void setZeroPosition(double zeroPosition);
    void setParkPosition(double parkPosition);

    QString toString() const;

    AxisId id() const;
    QString decoratedId() const;

    static QString decorateId(AxisId id);
    static AxisId idFromStr(QString value);

    bool operator==(const AxisState& other) const;
    bool operator!=(const AxisState& other) const;
    bool operator>=(const AxisState& other) const;
    bool operator<=(const AxisState& other) const;
    bool operator>(const AxisState& other) const;
    bool operator<(const AxisState& other) const;

    static bool isEqual(double pos1, double pos2);

private:
    AxisId m_id;
    double m_currentPosition;
    double m_zeroPosition;
    double m_parkPosition;

    static double decoratePosition(double pos);
};

#endif // AXISSTATE_H
