#include "switch_spindel_interactor.h"

SwitchSpindelInteractor::SwitchSpindelInteractor()
{

}

SwitchSpindelInteractor::~SwitchSpindelInteractor()
{

}

void SwitchSpindelInteractor::execute(SMLServer &server, QString uid, bool enable, size_t rotations)
{
    if(enable)
    {
        SwitchSpindelInteractor::switchOn(uid, rotations, server);
    }
    else
    {
        SwitchSpindelInteractor::switchOff(uid, server);
    }
}

void SwitchSpindelInteractor::switchOn(QString uid, size_t rotations, SMLServer& server)
{
    QtJson::JsonObject u1Message;
    QtJson::JsonObject device;
    device["uid"] = uid;
    device["target"] = "on";
    device["type"] = "spindel";
    device["rotations"] = QVariant::fromValue(rotations);
    u1Message["switch_device"] = device;
    u1Message["target"] = "u1";

    bool ok = false;
    QByteArray message = QtJson::serialize(u1Message, ok);
    qDebug() << "Try to switch on device =" << message;
    if(ok)
    {
        server.sendMessageToU1(message);
    }
}

void SwitchSpindelInteractor::switchOff(QString uid, SMLServer& server)
{
    QtJson::JsonObject u1Message;
    QtJson::JsonObject device;
    device["uid"] = uid;
    device["target"] = "off";
    device["type"] = "spindel";
    u1Message["switch_device"] = device;
    u1Message["target"] = "u1";

    bool ok = false;
    QByteArray message = QtJson::serialize(u1Message, ok);
    qDebug() << "Try to switch off device =" << message;
    if(ok)
    {
        server.sendMessageToU1(message);
    }
}
