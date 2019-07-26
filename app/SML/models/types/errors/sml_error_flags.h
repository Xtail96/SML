#ifndef SML_ERROR_FLAGS_H
#define SML_ERROR_FLAGS_H

#include <QObject>

#include "models/types/structs.h"

/*!
 * \brief Флаги ошибок в работе системы
 */
class SmlErrorFlags : public QObject
{
    Q_OBJECT
public:
    explicit SmlErrorFlags(QObject *parent = nullptr);

    bool isSystemHasErrors();

    void insertErrorFlag(ERROR_CODE code);

    void dropErrorFlag(ERROR_CODE code);

    QList<ERROR_CODE> getCurrentErrorFlags();

private:
    QSet<ERROR_CODE> m_errors;

signals:
    void stateChanged();

public slots:
};

#endif // ERROR_FLAGS_H

