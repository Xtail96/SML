#ifndef SPINDEL_H
#define SPINDEL_H

#include "models/devicesmanager/device/device.h"
class Spindel : public Device
{
public:
    Spindel(QString code, const SettingsManager &sm = SettingsManager());
    ~Spindel();
    QStringList getParams() override;

    void setCurrentRotations(const size_t &rotations);

    void setUpperBound(const size_t &upperBound);

    void setLowerBound(const size_t &lowerBound);

protected:
    size_t m_currentRotations;
    size_t m_upperBound;
    size_t m_lowerBound;

    void initialize(const SettingsManager &sm);
};

#endif // SPINDEL_H
