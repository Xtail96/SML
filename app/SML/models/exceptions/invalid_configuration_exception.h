#ifndef INVALIDCONFIGURATIONEXCEPTION_H
#define INVALIDCONFIGURATIONEXCEPTION_H

#include <QException>

class InvalidConfigurationException : public QException
{
public:
    InvalidConfigurationException(QString message);
    void raise() const;
    InvalidConfigurationException *clone() const;

    QString message() const;

protected:
    QString m_message;
};

#endif // INVALIDCONFIGURATIONEXCEPTION_H
