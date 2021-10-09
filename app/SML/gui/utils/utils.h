#ifndef UTILS_H
#define UTILS_H

#include <QAbstractButton>
#include <QShortcut>
#include <QDebug>

QMetaObject::Connection bindShortcut(QAbstractButton *button, const QKeySequence &key);

#endif // UTILS_H
