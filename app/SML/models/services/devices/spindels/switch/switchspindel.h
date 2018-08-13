#ifndef SWITCHSPINDEL_H
#define SWITCHSPINDEL_H

#include <QObject>

#include "models/types/server/smlserver.h"
#include "models/types/base/interactor.h"

class SwitchSpindel : public QObject, public Interactor
{
    Q_OBJECT
public:
    explicit SwitchSpindel(SMLServer* server, QString index, bool enable, size_t rotations = 0, QObject *parent = nullptr);
    void execute();

protected:
    SMLServer* m_server;
    QString m_index;
    size_t m_rotations;
    bool m_enable;

    void switchOn();
    void switchOff();

signals:

public slots:
};

#endif // SWITCHSPINDEL_H
