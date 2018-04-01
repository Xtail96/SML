#include "axis.h"

Axis::Axis(QString name, SettingsManager *settingsManager) :
    m_name(name)
{
    if(settingsManager != nullptr)
    {
        setup(settingsManager);
    }
    else
    {
        SettingsManager* sm = new SettingsManager();
        setup(sm);
        delete sm;
    }
}

Axis::~Axis()
{

}

void Axis::setup(SettingsManager *settingsManager)
{
    m_currentPosition = 0.0;
    try
    {
        QString fullAxisName = QString("Axis") + m_name;

        QVariant qLength = settingsManager->get("TableSize", QString("Size" + m_name));
        m_length = qLength.toDouble();

        QVariant qStep = settingsManager->get(fullAxisName, "Step");
        m_step = qStep.toDouble();

        m_currentPosition = 0.0;

        QVariant qInvertDirection = settingsManager->get(fullAxisName, "Invert");
        m_invertDirection = qInvertDirection.toBool();

        m_currentVelocity = 30.0;

        QVariant qBazaSearchSpeed = settingsManager->get(fullAxisName, "BazaSearchSpeed");
        m_basingVelocity = qBazaSearchSpeed.toDouble();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, QString("Ошибка настройки оси ") + m_name, e.what()).exec();
    }
}

QString Axis::name() const
{
    return m_name;
}

void Axis::setName(const QString &name)
{
    m_name = name;
}

double Axis::length() const
{
    return m_length;
}

void Axis::setLength(double length)
{
    m_length = length;
}

double Axis::step() const
{
    return m_step;
}

void Axis::setStep(double step)
{
    m_step = step;
}

double Axis::currentPosition() const
{
    return m_currentPosition;
}

void Axis::setCurrentPosition(double currentPosition)
{
    m_currentPosition = currentPosition;
}

bool Axis::invertDirection() const
{
    return m_invertDirection;
}

void Axis::setInvertDirection(bool invertDirection)
{
    m_invertDirection = invertDirection;
}

double Axis::currentVelocity() const
{
    return m_currentVelocity;
}

void Axis::setCurrentVelocity(double currentVelocity)
{
    m_currentVelocity = currentVelocity;
}

double Axis::basingVelocity() const
{
    return m_basingVelocity;
}

void Axis::setBasingVelocity(double basingVelocity)
{
    m_basingVelocity = basingVelocity;
}
