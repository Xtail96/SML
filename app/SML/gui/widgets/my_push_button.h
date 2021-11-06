#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QShortcut>
#include <QTimer>
#include <QDebug>

class MyPushButton : public QPushButton
{
public:
    MyPushButton(QWidget* parent=nullptr);

    void setShortcut(const QKeySequence &key);

private:
    QShortcut* m_shortcut;
    QTimer* m_timer;
    bool m_pressed = false;
};

#endif // MYPUSHBUTTON_H
