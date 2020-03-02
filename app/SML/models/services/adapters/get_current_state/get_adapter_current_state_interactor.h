#ifndef GETADAPTERCURRENTSTATEINTERACTOR_H
#define GETADAPTERCURRENTSTATEINTERACTOR_H

#include "models/machine_tool_elements/adapter/server/sml_adapter_server.h"
#include "models/machine_tool_elements/adapter/adapter.h"

class GetAdapterCurrentStateInteractor
{
public:
    GetAdapterCurrentStateInteractor();

    static void execute(SMLAdapterServer& server, Adapter::Type adapter);
};

#endif // GETADAPTERCURRENTSTATEINTERACTOR_H
