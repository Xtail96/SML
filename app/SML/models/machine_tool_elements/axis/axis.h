#ifndef AXIS_H
#define AXIS_H

#include <QString>
#include <QObject>
#include <QDebug>

class Axis : public QObject
{
    Q_OBJECT
public:
    explicit Axis(QString name, double lowerBound, double upperBound, double basingFeedrate,
                  QObject* parent = nullptr);
    ~Axis();

    QString name() const;
    void setName(const QString &name);

    double length() const;

    double currentPosition() const;
    void setCurrentPosition(double currentPosition);

    double basingFeedrate() const;
    void setBasingFeedrate(double basingFeedrate);

    QString axisSettings() const;

    double lowerBound() const;
    void setLowerBound(double lowerBound);

    double upperBound() const;
    void setUpperBound(double upperBound);

private:
    QString m_name;
    double m_currentPosition;
    double m_basingFeedrate;
    double m_lowerBound;
    double m_upperBound;

signals:
    void currentPositionChanged(QString axisUid, double currentPosition);
};

#endif // AXIS_H
