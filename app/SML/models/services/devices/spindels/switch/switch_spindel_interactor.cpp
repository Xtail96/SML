#include "switch_spindel_interactor.h"

SwitchSpindelInteractor::SwitchSpindelInteractor()
{

}

SwitchSpindelInteractor::~SwitchSpindelInteractor()
{

}

void SwitchSpindelInteractor::execute(SMLAdapterServer &server, QString uid, bool enable, size_t rotations)
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

void SwitchSpindelInteractor::switchOn(QString uid, size_t rotations, SMLAdapterServer& server)
{
    QtJson::JsonObject u1Message;
    QtJson::JsonObject params;
    params["uid"] = uid;
    params["target"] = "on";
    params["type"] = "spindel";
    params["rotations"] = QVariant::fromValue(rotations);
    u1Message["params"] = params;
    u1Message["action"] = "switch_device";
    u1Message["target"] = "u1";

    bool ok = false;
    QByteArray message = QtJson::serialize(u1Message, ok);
    if(!ok) { qDebug() << "SwitchSpindelInteractor::switchOn: serialize error" << message; return; }

    qDebug() << "SwitchSpindelInteractor::switchOn:" << message;
    server.sendMessageToU1(message);
}

void SwitchSpindelInteractor::switchOff(QString uid, SMLAdapterServer& server)
{
    QtJson::JsonObject u1Message;
    QtJson::JsonObject params;
    params["uid"] = uid;
    params["target"] = "off";
    params["type"] = "spindel";
    u1Message["params"] = params;
    u1Message["action"] = "switch_device";
    u1Message["target"] = "u1";

    bool ok = false;
    QByteArray message = QtJson::serialize(u1Message, ok);
    if(!ok) { qDebug() << "SwitchSpindelInteractor::switchOff: serialize error" << message; return; }

    qDebug() << "SwitchSpindelInteractor::switchOff: " << message;
    server.sendMessageToU1(message);
}
