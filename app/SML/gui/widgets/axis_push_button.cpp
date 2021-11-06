#include "axis_push_button.h"

AxisPushButton::AxisPushButton(QWidget *parent):
    QPushButton(parent),
    m_shortcutDelayTimer(new QTimer(this)),
    m_continiousMovement(false)
{
    this->setAutoRepeat(false);
    QObject::connect(m_shortcutDelayTimer, &QTimer::timeout, [=]() {
        m_shortcutDelayTimer->stop();
        this->setDown(false);
        emit this->released();
    });
}

void AxisPushButton::bindAxis(Axis::Id axis)
{
    m_axes.append(axis);
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

QList<Axis::Id> AxisPushButton::getAxes() const
{
    return m_axes;
}

bool AxisPushButton::getContiniousMovement() const
{
    return m_continiousMovement;
}

void AxisPushButton::setContiniousMovement(bool continiousMovement)
{
    m_continiousMovement = continiousMovement;
    for(auto shortcut : m_shortcuts)
        shortcut->setAutoRepeat(m_continiousMovement);
}
