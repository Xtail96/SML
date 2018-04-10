#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(MachineTool *_controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    controller(_controller),
    isEdit(false)
{
    setupFields();
    connect(this, SIGNAL(newPoint(QStringList)), controller, SLOT(addPoint(QStringList)));
}

AddPointDialog::AddPointDialog(MachineTool *_controller, unsigned int _pointNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    controller(_controller),
    isEdit(true),
    pointNumber(_pointNumber)
{
    setupFields();
    setWindowTitle("Редактировать точку");
    ui->addPointTitleLabel->setText("Точка №" + QString::fromStdString(std::to_string(_pointNumber+1)));
    connect(this, SIGNAL(updatePointsCoordinates(QStringList,uint)), controller, SLOT(updatePoint(QStringList,uint)));
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

    if(!isEdit)
    {
        emit newPoint(qArguments);
    }
    else
    {
        emit updatePointsCoordinates(qArguments, pointNumber);
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

    QStringList qRowHeaders = controller->getAxisesNames();
    ui->addPointArgumentsTableWidget->setRowCount(qRowHeaders.size());
    ui->addPointArgumentsTableWidget->setVerticalHeaderLabels(qRowHeaders);

    QStringList pointCoordinates;
    if(isEdit)
    {
        pointCoordinates = controller->getPoint(pointNumber);
    }

    for(int i = 0; i < ui->addPointArgumentsTableWidget->columnCount(); i++)
    {
        ui->addPointArgumentsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->addPointArgumentsTableWidget->rowCount(); j++)
        {
            if(!isEdit)
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
