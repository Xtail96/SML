#include "commandhandler.h"


void CMD_ARC_HANDLER(arguments args)
{
    MachineTool::Instance().stepMove( {1, 0, 0, 0, 0} );
}
