#include "add_point_dialog.h"
#include "ui_add_point_dialog.h"

AddPointDialog::AddPointDialog(Repository &repository, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    m_repository(repository),
    m_Edit(false)
{
    setupFields();
}

AddPointDialog::AddPointDialog(Repository &repository, unsigned int pointNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    m_repository(repository),
    m_Edit(true),
    m_pointNumber(pointNumber)
{
    setupFields();
    setWindowTitle("Редактировать точку");
    ui->addPointTitleLabel->setText("Точка №" + QString::number(m_pointNumber+1));
}

AddPointDialog::~AddPointDialog()
{
    delete ui;
}

void AddPointDialog::on_buttonBox_accepted()
{
    QMap<QString, double> qArguments;
    for(int i = 0; i < ui->addPointArgumentsTableWidget->rowCount(); i++)
    {
        QString qArgument;
        for(int j = 0; j < ui->addPointArgumentsTableWidget->columnCount(); j++)
        {
            qArgument = ui->addPointArgumentsTableWidget->item(i, j)->text();
            if(qArgument == "")
            {
                qArgument = "0";
            }
        }
        qArguments.insert(ui->addPointArgumentsTableWidget->verticalHeaderItem(i)->text(),
                          qArgument.toDouble());
    }

    if(!m_Edit)
    {
        m_repository.addPoint(qArguments);
    }
    else
    {
        m_repository.updatePoint(qArguments, m_pointNumber);
    }
}

void AddPointDialog::setupFields()
{
    ui->setupUi(this);
    QStringList qColumnsHeaders =
    {
        "Значение"
    };
    ui->addPointArgumentsTableWidget->setColumnCount(qColumnsHeaders.size());
    ui->addPointArgumentsTableWidget->setHorizontalHeaderLabels(qColumnsHeaders);

    QStringList qRowHeaders = m_repository.getAxisesNames();
    ui->addPointArgumentsTableWidget->setRowCount(qRowHeaders.size());
    ui->addPointArgumentsTableWidget->setVerticalHeaderLabels(qRowHeaders);

    QStringList pointCoordinates;
    if(m_Edit)
    {
        Point p = m_repository.getPoint(m_pointNumber);
        for(auto axisUid : qRowHeaders)
        {
           pointCoordinates.append(QString::number(p.get(axisUid)));
        }
    }

    for(int i = 0; i < ui->addPointArgumentsTableWidget->columnCount(); i++)
    {
        ui->addPointArgumentsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->addPointArgumentsTableWidget->rowCount(); j++)
        {
            if(!m_Edit)
            {
                ui->addPointArgumentsTableWidget->setItem(i, j, new QTableWidgetItem("0"));
            }
            else
            {
                // j - номер оси
                ui->addPointArgumentsTableWidget->setItem(i, j, new QTableWidgetItem(pointCoordinates[j]));
            }
        }
    }
}
