#include "sensors_display_widget.h"

SensorsDisplayWidget::SensorsDisplayWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(0, 0, 0, 5);

    QWidget* container = new QWidget(this);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setSpacing(0);
    container->layout()->setContentsMargins(0, 0, 0, 0);

    m_sensorsTable = new QTableWidget(container);
#ifdef Q_OS_MACOS
    m_sensorsTable->setFixedWidth(110);
#endif
#ifdef Q_OS_LINUX
    m_sensorsTable->setFixedWidth(150);
#endif
#ifdef Q_OS_WIN
    m_sensorsTable->setFixedWidth(150);
#endif

    m_sensorsTable->setLayoutDirection(Qt::RightToLeft);
    m_sensorsTable->setShowGrid(true);

    container->layout()->addWidget(m_sensorsTable);

    this->layout()->addWidget(container);
}

void SensorsDisplayWidget::update()
{
    m_sensorsTable->clear();

    QStringList labels;
    QList<QTableWidgetItem*> items;
    for(auto sensor : m_sensors)
    {
        labels.push_back(sensor->label);
        QTableWidgetItem *item = new QTableWidgetItem();
        (sensor->state) ? item->setBackgroundColor(sensor->activeStateLedColor)
                        : item->setBackgroundColor(sensor->inactiveStateLedColor);
        item->setFlags(Qt::ItemIsEnabled);
        items.push_back(item);
    }

    m_sensorsTable->setColumnCount(1);
    m_sensorsTable->setRowCount(labels.size());
    m_sensorsTable->setVerticalHeaderLabels(labels);

    QHeaderView*horizontalHeader = m_sensorsTable->horizontalHeader();
    horizontalHeader->setVisible(false);
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);

    QHeaderView* verticalHeader = m_sensorsTable->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(25);

    for(int i = 0; i < items.size(); i++)
    {
        m_sensorsTable->setItem(i, 0, items[i]);
    }
}

void SensorsDisplayWidget::addSensor(QString uid, QString label, bool state, QColor activeStateLedColor)
{
    m_sensors.push_back(QSharedPointer<SensorWidget>(new SensorWidget(uid, label, state, activeStateLedColor)));
    this->update();
}

void SensorsDisplayWidget::removeSensor(QString uid)
{
    try
    {
        m_sensors.removeAll(findSensor(uid));
        this->update();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "SensorDisplayWidget error", e.what());
    }
}

void SensorsDisplayWidget::updateSensorData(QString uid, QString label, bool state, QColor activeStateLedColor)
{
    try
    {
        QSharedPointer<SensorWidget> sensor = this->findSensor(uid);
        sensor->label = label;
        sensor->state = state;
        sensor->activeStateLedColor = activeStateLedColor;
        this->update();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "SensorDisplayWidget error", e.what());
    }
}

void SensorsDisplayWidget::updateSensorState(QString uid, bool state)
{
    try
    {
        this->findSensor(uid)->state = state;
        this->update();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "SensorDisplayWidget error", e.what());
    }
}

QSharedPointer<SensorsDisplayWidget::SensorWidget> SensorsDisplayWidget::findSensor(QString uid)
{
    for(auto sensor : m_sensors)
    {
        if(sensor->uid == uid)
        {
            return sensor;
        }
    }

    throw std::invalid_argument("can not find sensor with name" + uid.toStdString());
}
