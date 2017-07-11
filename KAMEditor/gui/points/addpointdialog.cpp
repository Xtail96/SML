#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(MachineTool *_machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    isEdit(false),
    machineTool(_machineTool)
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

    for(int i = 0; i < ui->addPointArgumentsTableWidget->columnCount(); i++)
    {
        ui->addPointArgumentsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->addPointArgumentsTableWidget->rowCount(); j++)
        {
            ui->addPointArgumentsTableWidget->setItem(i, j, new QTableWidgetItem("0"));
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
        }
        qArguments.push_back(qArgument);
    }

    Point *p = new Point(qArguments.size());
    /*for(int i = 0; i < qArguments.size(); i++)
    {
        std::string argument = qArguments[i].toStdString();
        p[i] = std::stod(argument);
    }*/
    machineTool->getPointsManager().addPoint(p);
}
