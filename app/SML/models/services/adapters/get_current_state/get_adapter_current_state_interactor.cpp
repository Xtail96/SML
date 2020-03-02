#include "get_adapter_current_state_interactor.h"

GetAdapterCurrentStateInteractor::GetAdapterCurrentStateInteractor()
{

}

void GetAdapterCurrentStateInteractor::execute(SMLAdapterServer &server, Adapter::Type adapter)
{
    QString targetAdapter = "";
    switch (adapter)
    {
    case Adapter::U1:
        targetAdapter = "u1";
        break;
    case Adapter::U2:
        targetAdapter = "u2";
        break;
    }

    QtJson::JsonObject rootObj;
    rootObj["action"] = "get_current_state";
    rootObj["target"] = targetAdapter;

    bool ok = false;
    QByteArray message = QtJson::serialize(rootObj, ok);
    qDebug() << "GetAdapterCurrentStateInteractor::execute =" << message;
    if(ok)
    {
        switch (adapter)
        {
        case Adapter::U1:
            server.sendMessageToU1(message);
            break;
        case Adapter::U2:
            server.sendMessageToU2(message);
            break;
        }
    }
}
