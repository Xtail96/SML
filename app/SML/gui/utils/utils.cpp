#include "utils.h"


QMetaObject::Connection bindShortcut(QAbstractButton *button, const QKeySequence &shortcut)
{
    return QObject::connect(new QShortcut(shortcut, button), &QShortcut::activated, [button]() {
        if(button->isEnabled())
            button->animateClick();
    });
}
