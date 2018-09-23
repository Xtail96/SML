#ifndef OUTOFRANGEEXCEPTION_H
#define OUTOFRANGEEXCEPTION_H

#include <QException>

class OutOfRangeException : public QException
{
public:
    OutOfRangeException(QString message);
    void raise() const;
    OutOfRangeException *clone() const;

    QString message() const;

protected:
    QString m_message;
};

#endif // OUTOFRANGEEXCEPTION_H
