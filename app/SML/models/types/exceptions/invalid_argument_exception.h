#ifndef INVALIDARGUMENTEXCEPTION_H
#define INVALIDARGUMENTEXCEPTION_H

#include <QException>

class InvalidArgumentException : public QException
{
public:
    InvalidArgumentException(QString message);
    void raise() const;
    InvalidArgumentException *clone() const;

    QString message() const;

protected:
    QString m_message;
};

#endif // INVALIDARGUMENTEXCEPTION_H
