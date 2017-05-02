#ifndef ARC_H
#define ARC_H

#include "command.h"

class Arc : public Command
{
public:
    Arc();

    void send() const override;
    void draw() const override;

    std::string getName() const override;
};

#endif // ARC_H
