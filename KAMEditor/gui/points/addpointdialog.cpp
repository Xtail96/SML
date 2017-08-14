#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(MovementsHandler *_movementsHandler, PointsManager *_pointsManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    isEdit(false),
    movementsHandler(_movementsHandler),
    pointsManager(_pointsManager),
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

AddPointDialog::AddPointDialog(MovementsHandler *_movementsHandler, PointsManager *_pointsManager, std::shared_ptr<Point> pointForEdit, unsigned int _pointNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    isEdit(true),
    movementsHandler(_movementsHandler),
    pointsManager(_pointsManager),
    pointNumber(_pointNumber)
{
    initializeFields();
    setWindowTitle("Редактировать точку");
    ui->addPointTitleLabel->setText("Точка №" + QString::fromStdString(std::to_string(_pointNumber+1)));

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
        try
        {
           p->get(i) = std::stod(qArguments[i].toStdString());
        }
        catch(...)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", "Неверный аргумент").exec();
        }
    }

    if(!isEdit)
    {
        pointsManager->addPoint(p);
    }
    else
    {
        pointsManager->operator [](pointNumber) = std::shared_ptr<Point>(p);
    }
}

void AddPointDialog::initializeFields()
{
    ui->setupUi(this);
    axises = movementsHandler->getAxises();
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
