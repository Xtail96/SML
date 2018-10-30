#include "switchspindel.h"

SwitchSpindel::SwitchSpindel(SMLServer *server, QString uid, bool enable, size_t rotations, QObject *parent) :
    QObject(parent),
    m_server(server),
    m_uid(uid),
    m_rotations(rotations),
    m_enable(enable)
{

}

void SwitchSpindel::execute()
{
    if(m_enable)
    {
        switchOn();
    }
    else
    {
        switchOff();
    }
}

void SwitchSpindel::switchOn()
{
    QtJson::JsonObject generalMessage;
    QtJson::JsonObject u1Message;
    QtJson::JsonObject device;
    device["Index"] = m_uid;
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
        m_server->sendMessageToU1(message);
    }
}

void SwitchSpindel::switchOff()
{
    QtJson::JsonObject generalMessage;
    QtJson::JsonObject u1Message;
    QtJson::JsonObject device;
    device["Index"] = m_uid;
    device["Target"] = "Off";
    device["Type"] = "Spindel";
    u1Message["SwitchDevice"] = device;
    generalMessage["MessageToU1"] = u1Message;

    bool ok = false;
    QByteArray message = QtJson::serialize(generalMessage, ok);
    qDebug() << "Try to switch off device =" << message;
    if(ok)
    {
        m_server->sendMessageToU1(message);
    }
}
