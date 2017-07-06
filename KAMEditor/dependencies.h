#include <QtGlobal>

// libusb
#ifdef Q_OS_LINUX
#include <libusb-1.0/libusb.h>
#elif Q_OS_WIN
#include "libusb/include/libusb.h"
#endif
