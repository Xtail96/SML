#ifndef GCODESMANAGER_H
#define GCODESMANAGER_H

#include <QString>
#include <QDebug>

#include "libs/gpr/parser.h"

class GCodesManager
{
protected:
    QString m_gcodes;
public:
    GCodesManager();
    ~GCodesManager();

    void updateGCodesProgram(QString content);

    QString gcodes() const;
    void setGcodes(const QString &gcodes);
};

#endif // GCODESMANAGER_H
