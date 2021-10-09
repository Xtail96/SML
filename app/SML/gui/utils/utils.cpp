#include "utils.h"


QMetaObject::Connection bindShortcut(QAbstractButton *button, const QKeySequence &key)
{
    auto shortcut = new QShortcut(key, button);
    shortcut->setAutoRepeat(false);
    return QObject::connect(shortcut, &QShortcut::activated, [button]() {
        qDebug() << "activated";
        if(button->isEnabled())
        {
            qDebug() << "emit click";
            button->animateClick();
        }
    });
}
