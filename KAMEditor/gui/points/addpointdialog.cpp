#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(MachineTool *_machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    isEdit(false),
    machineTool(_machineTool),
    pointNumber(-1)
{
    initializeFields();
    for(int i = 0; i < ui->addPointArgumentsTableWidget->columnCount(); i++)
    {
        ui->addPointArgumentsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->addPointArgumentsTableWidget->rowCount(); j++)
        {
            ui->addPointArgumentsTableWidget->setItem(i, j, new QTableWidgetItem("0"));
        }
    }
}

AddPointDialog::AddPointDialog(MachineTool *_machineTool, std::shared_ptr<Point> pointForEdit, unsigned int _pointNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    isEdit(true),
    machineTool(_machineTool),
    pointNumber(_pointNumber)
{
    initializeFields();
    ui->add_point_title_label->setText("Точка №" + QString::fromStdString(std::to_string(_pointNumber+1)));

    for(int i = 0; i < ui->addPointArgumentsTableWidget->columnCount(); i++)
    {
        ui->addPointArgumentsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->addPointArgumentsTableWidget->rowCount(); j++)
        {
            // j - номер оси
            ui->addPointArgumentsTableWidget->setItem(i, j, new QTableWidgetItem(QString::fromStdString(std::to_string(pointForEdit->get(j)))));
        }
    }
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

    Point* p = new Point(qArguments.size());
    for(int i = 0; i < qArguments.size(); i++)
    {
        p->get(i) = std::stod(qArguments[i].toStdString());
    }

    if(!isEdit)
    {
        machineTool->getPointsManager().addPoint(p);
    }
    else
    {
        machineTool->getPointsManager().operator [](pointNumber) = std::shared_ptr<Point>(p);
    }
}

void AddPointDialog::initializeFields()
{
    ui->setupUi(this);
    axises = machineTool->getMovementController().getAxises();
    QStringList qColumnsHeaders =
    {
        "Значение"
    };
    ui->addPointArgumentsTableWidget->setColumnCount(qColumnsHeaders.size());
    ui->addPointArgumentsTableWidget->setHorizontalHeaderLabels(qColumnsHeaders);

    QStringList qRowHeaders;
    for(auto axis : axises)
    {
        QString header = QString("По оси " + QString::fromStdString(axis->getName()));
        qRowHeaders.append(header);
    }
    ui->addPointArgumentsTableWidget->setRowCount(qRowHeaders.size());
    ui->addPointArgumentsTableWidget->setVerticalHeaderLabels(qRowHeaders);

}
