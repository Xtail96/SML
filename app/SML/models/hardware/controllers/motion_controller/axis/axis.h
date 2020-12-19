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
    explicit Axis(AxisId id,
                  double initialPosition,
                  QObject* parent = nullptr);
    ~Axis();

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

    bool operator==(const Axis& other) const;
    bool operator!=(const Axis& other) const;
    bool operator>=(const Axis& other) const;
    bool operator<=(const Axis& other) const;
    bool operator>(const Axis& other) const;
    bool operator<(const Axis& other) const;

private:
    AxisId m_id;
    double m_currentPosition;
    double m_zeroPosition;
    double m_parkPosition;

    static double decoratePosition(double pos);
    static bool isEqual(double pos1, double pos2);

signals:
    void currentPositionChanged();
};

#endif // AXIS_H
