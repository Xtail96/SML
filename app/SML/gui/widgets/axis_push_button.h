#ifndef AXISPUSHBUTTON_H
#define AXISPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QShortcut>
#include <QTimer>
#include <QDebug>

class AxisPushButton : public QPushButton
{
public:
    AxisPushButton(QWidget* parent=nullptr);
    void bindShortcut(const QKeySequence &key);
private:
    QList<QShortcut*> m_shortcuts;
    QTimer* m_shortcutDelayTimer;
};

#endif // AXISPUSHBUTTON_H
