#ifndef SPINDEL_H
#define SPINDEL_H

#include "models/devicesmanager/device/device.h"
class Spindel : public Device
{
public:
    Spindel(QString code, const SettingsManager &sm = SettingsManager());
    ~Spindel();

    QStringList getParams() override;

    void setRotations(const size_t &rotations);

protected:
    size_t m_rotations;
};

#endif // SPINDEL_H
