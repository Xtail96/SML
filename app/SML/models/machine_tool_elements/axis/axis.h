#ifndef AXIS_H
#define AXIS_H

#include <QString>
#include <QObject>
#include <QDebug>

class Axis : public QObject
{
    Q_OBJECT
public:
    explicit Axis(QString name, double length, double step, bool invertDirection, double basingVelocity, double lowerBound, double upperBound, QObject* parent = nullptr);
    ~Axis();

    QString name() const;
    void setName(const QString &name);

    double length() const;
    void setLength(double length);

    double step() const;
    void setStep(double step);

    double currentPosition() const;
    void setCurrentPosition(double currentPosition);

    bool invertDirection() const;
    void setInvertDirection(bool invertDirection);

    double currentVelocity() const;
    void setCurrentVelocity(double currentVelocity);

    double basingVelocity() const;
    void setBasingVelocity(double basingVelocity);

    bool softLimitsEnable() const;
    void setSoftLimitsEnable(bool softLimitsEnable);

    QString axisSettings() const;

    double lowerBound() const;
    void setLowerBound(double lowerBound);

    double upperBound() const;
    void setUpperBound(double upperBound);

private:
    QString m_name;
    double m_length;
    double m_step;
    double m_currentPosition;
    bool m_invertDirection;
    double m_currentVelocity;
    double m_basingVelocity;
    double m_lowerBound;
    double m_upperBound;

    bool m_softLimitsEnable;

signals:
    void currentPositionChanged(QString axisUid, double currentPosition);
};

#endif // AXIS_H