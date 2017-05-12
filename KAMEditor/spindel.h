#ifndef SPINDEL_H
#define SPINDEL_H
#include "device.h"

class Spindel : public Device
{
    unsigned int currentJog;
    std::pair<unsigned int, unsigned int> jogLimits;
    bool isReady;
public:
    Spindel(unsigned int _output, std::string _spindle_name, unsigned int _minJog, unsigned int maxJog, bool _isReady = false);

    unsigned int getJog() const;
    void setJog(unsigned int value);
    std::pair<unsigned int, unsigned int> getJogLimits() const;
    void setJogLimits(const std::pair<unsigned int, unsigned int> &value);
    bool getIsReady() const;
    void setIsReady(bool value);

    //void run() override;
    void calibrateSpindelJog(unsigned int jog);
};

#endif // SPINDEL_H
