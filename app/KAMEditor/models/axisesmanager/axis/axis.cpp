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
