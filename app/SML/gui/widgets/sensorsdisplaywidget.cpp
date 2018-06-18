#include "sensorsdisplaywidget.h"

SensorsDisplayWidget::SensorsDisplayWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(0, 0, 0, 5);

    QFrame* container = new QFrame(this);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setSpacing(0);
    container->layout()->setContentsMargins(0, 0, 0, 0);

    sensorsTable = new QTableWidget(container);
    //sensorsTable->setMaximumWidth();
    sensorsTable->setMinimumWidth(125);
    sensorsTable->setLayoutDirection(Qt::RightToLeft);
    sensorsTable->setShowGrid(true);

    container->layout()->addWidget(sensorsTable);

    this->layout()->addWidget(container);
}

void SensorsDisplayWidget::update()
{
    sensorsTable->clear();

    QStringList labels;
    QList<QTableWidgetItem*> items;
    for(auto sensor : m_sensors)
    {
        labels.push_back(sensor->label);
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackgroundColor(sensor->led);
        item->setFlags(Qt::ItemIsEnabled);
        items.push_back(item);
    }

    sensorsTable->setColumnCount(1);
    sensorsTable->setRowCount(labels.size());
    sensorsTable->setVerticalHeaderLabels(labels);

    QHeaderView*horizontalHeader = sensorsTable->horizontalHeader();
    horizontalHeader->setVisible(false);
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);

    QHeaderView* verticalHeader = sensorsTable->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(25);

    for(int i = 0; i < items.size(); i++)
    {
        sensorsTable->setItem(i, 0, items[i]);
    }
}

void SensorsDisplayWidget::addSensor(QString name, QString label, QColor led)
{
    m_sensors.push_back(QSharedPointer<SensorWidget>(new SensorWidget(name, label, led)));
    update();
}

void SensorsDisplayWidget::removeSensor(QString name)
{
    try
    {
        m_sensors.removeAll(findSensor(name));
        update();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "SensorDisplayWidget error", e.what());
    }
}

void SensorsDisplayWidget::updateSensorState(QString name, QColor led)
{
    try
    {
        findSensor(name)->led = led;
        update();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "SensorDisplayWidget error", e.what());
    }
}

QSharedPointer<SensorsDisplayWidget::SensorWidget> SensorsDisplayWidget::findSensor(QString name)
{
    for(auto sensor : m_sensors)
    {
        if(sensor->name == name)
        {
            return sensor;
        }
    }

    throw std::invalid_argument("can not find sensor with name" + name.toStdString());
}
