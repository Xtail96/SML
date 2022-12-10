#ifndef SPINDEL_H
#define SPINDEL_H

#include "./device.h"

class Spindel : public Device
{
public:
    Spindel(QString id,
            bool enabled,
            size_t currentRotations,
            size_t minRotations,
            size_t maxRotations,
            QString label = "");
    ~Spindel() override;
private:
    size_t m_maxRotations;
    size_t m_minRotations;
    size_t m_currentRotations;
};

#endif // SPINDEL_H
