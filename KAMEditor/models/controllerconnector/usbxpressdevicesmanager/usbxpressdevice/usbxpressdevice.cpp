#include "usbxpressdevice.h"

UsbXpressDevice::UsbXpressDevice()
{
    initialize();
}

void UsbXpressDevice::initialize()
{
    DWORD num;
    SI_STATUS res = SI_GetNumDevices(&num);
}
