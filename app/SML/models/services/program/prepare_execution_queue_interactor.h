#ifndef PREPARE_EXECUTION_QUEUE_INTERACTOR_H
#define PREPARE_EXECUTION_QUEUE_INTERACTOR_H

#include "math.h"

#include <QQueue>
#include <QByteArray>

#include "libs/gpr/parser.h"
#include "libs/json_parser/json.h"

#include "models/exceptions/exceptions.h"


class PrepareExecutionQueueInteractor
{
public:
    PrepareExecutionQueueInteractor();

    static QQueue<QByteArray> execute(QStringList gcodesProgram);

private:
    static QPair<QString, double> chunkToKeyValuePair(gpr::chunk chunk);
};

#endif // PREPARE_EXECUTION_QUEUE_INTERACTOR_H
