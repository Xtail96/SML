#ifndef SPINDELCONTROLWIDGET_H
#define SPINDELCONTROLWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>

class SpindelControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpindelControlWidget(QString spindelLabel, QString spindelName, size_t rotationsUpperBound, size_t rotationsLowerBound, size_t currentRotations, bool enable, QWidget *parent = nullptr);

signals:
    void switchOn(QString m_spindelName, size_t rotations);
    void switchOff(QString m_spindelName);

public slots:

protected:
    QString m_spindelLabel;
    QString m_spindelName;
    size_t m_rotationsUpperBound;
    size_t m_rotationsLowerBound;
    size_t m_currentRotations;
    bool m_enable;
};

#endif // SPINDELCONTROLWIDGET_H
