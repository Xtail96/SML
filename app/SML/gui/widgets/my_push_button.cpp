#include "my_push_button.h"

MyPushButton::MyPushButton(QWidget *parent):
    QPushButton(parent)
{

}

void MyPushButton::setShortcut(const QKeySequence &key)
{
    m_shortcut = new QShortcut(key, this);
    m_shortcut->setAutoRepeat(true);
    m_timer = new QTimer(this);
    QObject::connect(m_timer, &QTimer::timeout, [=]() {
        qDebug() << "timeout";
        m_timer->stop();
        this->setDown(false);
        m_pressed = false;
        emit this->released();

    });

    QObject::connect(m_shortcut, &QShortcut::activated, [=]() {
        qDebug() << "shortcut pressed";
        if(m_pressed)
        {
            qDebug() << "stop timer";
            m_timer->stop();
        }
        else
        {
            qDebug() << "new press";
            this->setDown(true);
            m_pressed = true;
            emit this->pressed();
        }
        m_timer->start(200);
    });
}
