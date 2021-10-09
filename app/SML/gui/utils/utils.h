#ifndef UTILS_H
#define UTILS_H

#include <QAbstractButton>
#include <QShortcut>

QMetaObject::Connection bindShortcut(QAbstractButton *button, const QKeySequence &shortcut);

#endif // UTILS_H
