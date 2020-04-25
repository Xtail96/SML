#ifndef MOTOR_H
#define MOTOR_H


class Motor
{
public:
    Motor(int id, double step);

    int id() const;

    double step() const;
    void setStep(double step);

    bool isMoving() const;
    void setIsMoving(bool isMoving);

private:
    int m_id;

    double m_step;

    bool m_isMoving;
};

#endif // MOTOR_H
