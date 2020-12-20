#ifndef AXIS_H
#define AXIS_H

#include <QString>
#include <QDebug>

namespace Axis {
    enum Id {
        X, Y, Z, A, B, C, U, V, W
    };

    QString decorateId(Id id);
    Id idFromStr(QString value);

    class State
    {
    public:
        State(Id id, double currentPosition);
        ~State();

        double currentPositionFromBase() const;
        double currentPositionFromZero() const;
        void setCurrentPosition(double absPosition);

        double zeroPosition() const;
        double parkPosition() const;
        void setZeroPosition(double zeroPosition);
        void setParkPosition(double parkPosition);

        QString toString() const;

        Id id() const;
        QString decoratedId() const;

        bool operator==(const State& other) const;
        bool operator!=(const State& other) const;
        bool operator>=(const State& other) const;
        bool operator<=(const State& other) const;
        bool operator>(const State& other) const;
        bool operator<(const State& other) const;

        static bool isEqual(double pos1, double pos2);

    private:
        Id m_id;
        double m_currentPosition;
        double m_zeroPosition;
        double m_parkPosition;

        static double decoratePosition(double pos);
    };
}





#endif // AXIS_H
