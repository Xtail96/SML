#ifndef SPINDEL_H
#define SPINDEL_H

#include "models/machine_tool_elements/device/device.h"

class Spindel : public Device
{
    Q_OBJECT
public:
    Spindel(QString settingsUid,
            QString label,
            QString uid,
            bool activeState,
            size_t lowerBound,
            size_t upperBound,
            QObject *parent = nullptr);

    ~Spindel() override;

    QStringList getParams() override;

    QString getSettings() override;

    void setCurrentState(bool value, QMap<QString, QString> attributes) override;

    void setCurrentState(bool value, size_t rotations);

    void setCurrentRotations(const size_t &rotations);

    void setUpperBound(const size_t &upperBound);

    void setLowerBound(const size_t &lowerBound);

    size_t getUpperBound() const;

    size_t getLowerBound() const;

    size_t getCurrentRotations() const;

protected:
    size_t m_upperBound;

    size_t m_lowerBound;

    size_t m_currentRotations;

signals:
    void stateChanged();

public slots:
    void update(bool state, size_t rotations);
};

#endif // SPINDEL_H
