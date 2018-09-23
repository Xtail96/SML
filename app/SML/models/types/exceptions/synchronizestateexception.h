#ifndef SYNCHRONIZESTATEEXCEPTION_H
#define SYNCHRONIZESTATEEXCEPTION_H

#include <QException>

class SynchronizeStateException : public QException
{
public:
    SynchronizeStateException(QString message);
    void raise() const;
    SynchronizeStateException *clone() const;
    QString message() const;

protected:
    QString m_message;
};

#endif // SYNCHRONIZESTATEEXCEPTION_H
