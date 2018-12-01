#ifndef U1STATE_H
#define U1STATE_H

#include <QList>

struct U1State
{
    QList<QVariant> sensors;
    QList<QVariant> devices;
    int errorCode;
    int workflowState;
};

#endif // U1STATE_H
