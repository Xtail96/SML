#include "get_adapter_current_state_interactor.h"

GetAdapterCurrentStateInteractor::GetAdapterCurrentStateInteractor()
{

}

/*void GetAdapterCurrentStateInteractor::execute(SMLAdapterServer &server, Adapter::Type adapter)
{
    QString targetAdapter = "";
    switch (adapter)
    {
    case Adapter::Device:
        targetAdapter = "deviceAdapter";
        break;
    case Adapter::Motion:
        targetAdapter = "motionAdapter";
        break;
    }

    QtJson::JsonObject rootObj;
    rootObj["action"] = "getCurrentState";
    rootObj["target"] = targetAdapter;

    bool ok = false;
    QByteArray message = QtJson::serialize(rootObj, ok);
    qDebug() << "GetAdapterCurrentStateInteractor::execute =" << message;
    if(ok)
    {
        switch (adapter)
        {
        case Adapter::Device:
            server.sendMessageToDeviceAdapter(message);
            break;
        case Adapter::Motion:
            server.sendMessageToMotionAdapter(message);
            break;
        }
    }
}*/
