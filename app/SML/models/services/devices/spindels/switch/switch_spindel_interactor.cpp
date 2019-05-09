#include "switch_spindel_interactor.h"

SwitchSpindelInteractor::SwitchSpindelInteractor()
{

}

SwitchSpindelInteractor::~SwitchSpindelInteractor()
{

}

void SwitchSpindelInteractor::execute(SMLServer *server, QString uid, bool enable, size_t rotations)
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

void SwitchSpindelInteractor::switchOn(QString uid, size_t rotations, SMLServer* server)
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

void SwitchSpindelInteractor::switchOff(QString uid, SMLServer* server)
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
