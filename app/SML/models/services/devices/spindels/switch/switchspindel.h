#ifndef SWITCHSPINDEL_H
#define SWITCHSPINDEL_H

#include <QObject>

#include "models/types/server/smlserver.h"

class SwitchSpindel : public QObject
{
    Q_OBJECT
public:
    explicit SwitchSpindel(QString index, bool enable, size_t rotations = 0, QObject *parent = nullptr);
    void execute(SMLServer* server);

protected:
    QString m_index;
    size_t m_rotations;
    bool m_enable;

    void switchOn(SMLServer *server);
    void switchOff(SMLServer *server);

signals:

public slots:
};

#endif // SWITCHSPINDEL_H
