#include "switchspindel.h"

SwitchSpindel::SwitchSpindel(QString index, bool enable, size_t rotations, QObject *parent) :
    QObject(parent),
    m_index(index),
    m_rotations(rotations),
    m_enable(enable)
{

}

void SwitchSpindel::execute(SMLServer *server)
{
    if(m_enable)
    {
        switchOn(server);
    }
    else
    {
        switchOff(server);
    }
}

void SwitchSpindel::switchOn(SMLServer *server)
{
    QtJson::JsonObject generalMessage;
    QtJson::JsonObject u1Message;
    QtJson::JsonObject device;
    device["Index"] = m_index;
    device["Target"] = "On";
    device["Type"] = "Spindel";
    device["Rotations"] = QVariant::fromValue(m_rotations);
    u1Message["SwitchDevice"] = device;
    generalMessage["MessageToU1"] = u1Message;

    bool ok = false;
    QByteArray message = QtJson::serialize(generalMessage, ok);
    qDebug() << "Try to switch on device =" << message;
    if(ok)
    {
        server->sendMessageToU1(message);
    }
}

void SwitchSpindel::switchOff(SMLServer *server)
{
    QtJson::JsonObject generalMessage;
    QtJson::JsonObject u1Message;
    QtJson::JsonObject device;
    device["Index"] = m_index;
    device["Target"] = "Off";
    device["Type"] = "Spindel";
    u1Message["SwitchDevice"] = device;
    generalMessage["MessageToU1"] = u1Message;

    bool ok = false;
    QByteArray message = QtJson::serialize(generalMessage, ok);
    qDebug() << "Try to switch off device =" << message;
    if(ok)
    {
        server->sendMessageToU1(message);
    }
}
