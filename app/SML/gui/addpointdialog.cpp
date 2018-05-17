#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(MachineTool &machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    m_machineTool(machineTool),
    m_Edit(false)
{
    setupFields();
    connect(this, SIGNAL(newPoint(QStringList)), &m_machineTool, SLOT(addPoint(QStringList)));
}

AddPointDialog::AddPointDialog(MachineTool &machineTool, unsigned int _pointNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    m_machineTool(machineTool),
    m_Edit(true),
    m_pointNumber(_pointNumber)
{
    setupFields();
    setWindowTitle("Редактировать точку");
    ui->addPointTitleLabel->setText("Точка №" + QString::fromStdString(std::to_string(_pointNumber+1)));
    connect(this, SIGNAL(updatePointsCoordinates(QStringList,uint)), &m_machineTool, SLOT(updatePoint(QStringList,uint)));
}

AddPointDialog::~AddPointDialog()
{
    delete ui;
}

void AddPointDialog::on_buttonBox_accepted()
{
    QStringList qArguments;
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
        qArguments.push_back(qArgument);
    }

    if(!m_Edit)
    {
        emit newPoint(qArguments);
    }
    else
    {
        emit updatePointsCoordinates(qArguments, m_pointNumber);
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

    QStringList qRowHeaders = m_machineTool.getAxisesNames();
    ui->addPointArgumentsTableWidget->setRowCount(qRowHeaders.size());
    ui->addPointArgumentsTableWidget->setVerticalHeaderLabels(qRowHeaders);

    QStringList pointCoordinates;
    if(m_Edit)
    {
        pointCoordinates = m_machineTool.getPoint(m_pointNumber);
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
