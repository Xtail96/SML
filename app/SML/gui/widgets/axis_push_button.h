#ifndef AXISPUSHBUTTON_H
#define AXISPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QShortcut>
#include <QTimer>
#include <QDebug>

#include "models/hardware/controllers/motion_controller/axis.h"

class AxisPushButton : public QPushButton
{
public:
    AxisPushButton(QWidget* parent=nullptr);
    void bindAxis(Axis::Id axis);
    void bindShortcut(const QKeySequence &key);
    QList<Axis::Id> getAxes() const;
    bool getContiniousMovement() const;
    void setContiniousMovement(bool continiousMovement);

private:
    QList<Axis::Id> m_axes;
    QList<QShortcut*> m_shortcuts;
    QTimer* m_shortcutDelayTimer;
    bool m_continiousMovement;
};

#endif // AXISPUSHBUTTON_H
