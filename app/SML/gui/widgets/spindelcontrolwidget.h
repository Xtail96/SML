#ifndef SPINDELCONTROLWIDGET_H
#define SPINDELCONTROLWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QDebug>

class SpindelControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpindelControlWidget(QString spindelLabel, QString spindelName, size_t rotationsUpperBound, size_t rotationsLowerBound, size_t currentRotations, bool enable, QWidget *parent = nullptr);

    void update(bool enable, size_t rotations);

signals:
    void switchOn(QString spindelName, size_t rotations);
    void switchOff(QString spindelName);
    void spindelRotationsChanged(QString spindelName, size_t rotations);

protected slots:
    void onSwitchSpindelClicked();
    void onWarmingSpindelUpClicked();
    void onRotationsSliderValueChanged(int value);

protected:
    QString m_spindelLabel;
    QString m_spindelName;
    size_t m_rotationsUpperBound;
    size_t m_rotationsLowerBound;
    size_t m_currentRotations;
    bool m_enable;


    QLabel* m_titleLabel;
    QLCDNumber* m_rotationsLCDNumber;
    QSlider* m_rotationsSlider;
    QPushButton* m_switchPushButton;
    QPushButton* m_warmingUpPushButton;
};

#endif // SPINDELCONTROLWIDGET_H
