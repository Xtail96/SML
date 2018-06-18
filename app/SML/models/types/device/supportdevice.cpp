#include "supportdevice.h"

SupportDevice::SupportDevice(QString name, QString label, QString index, bool activeState, int mask, QObject *parent) :
    Device(name, label, index, activeState, mask, parent)
{

}

QStringList SupportDevice::getParams()
{
    return QStringList();
}
