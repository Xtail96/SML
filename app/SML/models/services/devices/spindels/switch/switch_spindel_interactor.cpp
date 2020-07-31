#include "switch_spindel_interactor.h"

SwitchSpindelInteractor::SwitchSpindelInteractor()
{

}

SwitchSpindelInteractor::~SwitchSpindelInteractor()
{

}

/*void SwitchSpindelInteractor::execute(SMLAdapterServer &server, QString uid, bool enable, size_t rotations)
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
    QtJson::JsonObject deviceControllerMessage;
    QtJson::JsonObject params;
    params["uid"] = uid;
    params["target"] = "on";
    params["type"] = "spindel";
    params["rotations"] = QVariant::fromValue(rotations);
    deviceControllerMessage["params"] = params;
    deviceControllerMessage["action"] = "switch_device";
    deviceControllerMessage["target"] = "deviceController";

    bool ok = false;
    QByteArray message = QtJson::serialize(deviceControllerMessage, ok);
    if(!ok) { qDebug() << "SwitchSpindelInteractor::switchOn: serialize error" << message; return; }

    qDebug() << "SwitchSpindelInteractor::switchOn:" << message;
    server.sendMessageToDeviceAdapter(message);
}

void SwitchSpindelInteractor::switchOff(QString uid, SMLAdapterServer& server)
{
    QtJson::JsonObject deviceControllerMessage;
    QtJson::JsonObject params;
    params["uid"] = uid;
    params["target"] = "off";
    params["type"] = "spindel";
    deviceControllerMessage["params"] = params;
    deviceControllerMessage["action"] = "switch_device";
    deviceControllerMessage["target"] = "deviceController";

    bool ok = false;
    QByteArray message = QtJson::serialize(deviceControllerMessage, ok);
    if(!ok) { qDebug() << "SwitchSpindelInteractor::switchOff: serialize error" << message; return; }

    qDebug() << "SwitchSpindelInteractor::switchOff: " << message;
    server.sendMessageToDeviceAdapter(message);
}*/
