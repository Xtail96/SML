#include "axis_push_button.h"

AxisPushButton::AxisPushButton(QWidget *parent):
    QPushButton(parent),
    m_shortcutDelayTimer(new QTimer(this))
{
    QObject::connect(m_shortcutDelayTimer, &QTimer::timeout, [=]() {
        m_shortcutDelayTimer->stop();
        this->setDown(false);
        emit this->released();
    });
}

void AxisPushButton::bindShortcut(const QKeySequence &key)
{
    auto shortcut = new QShortcut(key, this);
    shortcut->setAutoRepeat(true);
    QObject::connect(shortcut, &QShortcut::activated, [=]() {
        if(this->isDown())
        {
            m_shortcutDelayTimer->stop();
        }
        else
        {
            this->setDown(true);
            emit this->pressed();
        }
        m_shortcutDelayTimer->start(200);
    });
    m_shortcuts.append(shortcut);
}
