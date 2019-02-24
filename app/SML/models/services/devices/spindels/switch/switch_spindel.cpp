#include "switch_spindel.h"

SwitchSpindel::SwitchSpindel(SMLServer *server, QString uid, bool enable, size_t rotations, QObject *parent) :
    QObject(parent),
    m_server(server),
    m_uid(uid),
    m_rotations(rotations),
    m_enable(enable)
{

}

SwitchSpindel::~SwitchSpindel()
{

}

void SwitchSpindel::execute()
{
    if(m_enable)
    {
        switchOn(m_uid, m_rotations, m_server);
    }
    else
    {
        switchOff(m_uid, m_server);
    }
}

void SwitchSpindel::switchOn(QString uid, size_t rotations, SMLServer* server)
{
    QtJson::JsonObject generalMessage;
    QtJson::JsonObject u1Message;
    QtJson::JsonObject device;
    device["Index"] = uid;
    device["Target"] = "On";
    device["Type"] = "Spindel";
    device["Rotations"] = QVariant::fromValue(rotations);
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

void SwitchSpindel::switchOff(QString uid, SMLServer* server)
{
    QtJson::JsonObject generalMessage;
    QtJson::JsonObject u1Message;
    QtJson::JsonObject device;
    device["Index"] = uid;
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
