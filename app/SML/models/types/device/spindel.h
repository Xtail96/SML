#ifndef SPINDEL_H
#define SPINDEL_H

#include "models/types/device/device.h"
class Spindel : public Device
{
public:
    Spindel(QString name,
            QString label,
            QString index,
            bool activeState,
            int mask,
            size_t lowerBound,
            size_t upperBound,
            QObject *parent = nullptr);
    ~Spindel();
    QStringList getParams() override;

    void setCurrentRotations(const size_t &rotations);

    void setUpperBound(const size_t &upperBound);

    void setLowerBound(const size_t &lowerBound);

    size_t getUpperBound() const;

    size_t getLowerBound() const;

    size_t getCurrentRotations() const;

protected:
    size_t m_currentRotations;
    size_t m_upperBound;
    size_t m_lowerBound;
};

#endif // SPINDEL_H
