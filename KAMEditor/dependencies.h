#include <QtGlobal>

// libusb
#if defined(Q_OS_LINUX)
#include <libusb-1.0/libusb.h>
#elif defined(Q_OS_WIN)
#include "libusb/include/libusb.h"
#endif
