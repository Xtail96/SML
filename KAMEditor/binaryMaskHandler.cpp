#include "binaryMaskHandler.h"

BinaryMaskHandler::BinaryMaskHandler()
{

}

BinaryMaskHandler& BinaryMaskHandler::Instance()
{
    static BinaryMaskHandler b;
    return b;
}
