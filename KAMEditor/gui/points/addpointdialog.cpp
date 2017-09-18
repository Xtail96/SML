#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(MainWindowController *_controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    controller(_controller),
    isEdit(false)
{
    connect(this, SIGNAL(newPoint(Point*)), controller, SLOT(addPoint(Point*)));
    setupFields();
}

AddPointDialog::AddPointDialog(MainWindowController *_controller, unsigned int _pointNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog),
    controller(_controller),
    isEdit(true),
    pointNumber(_pointNumber)
{
    setupFields();
    setWindowTitle("Редактировать точку");
    ui->addPointTitleLabel->setText("Точка №" + QString::fromStdString(std::to_string(_pointNumber+1)));
    connect(this, SIGNAL(updatePointsCoordinates(Point*,uint)), controller, SLOT(updatePoint(Point*,uint)));
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
        emit newPoint(p);
    }
    else
    {
        emit updatePointsCoordinates(p, pointNumber);
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
    if(!isEdit)
    {
        for(int i = 0; i < ui->addPointArgumentsTableWidget->columnCount(); i++)
        {
            ui->addPointArgumentsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            for(int j = 0; j < ui->addPointArgumentsTableWidget->rowCount(); j++)
            {
                ui->addPointArgumentsTableWidget->setItem(i, j, new QTableWidgetItem("0"));
            }
        }
    }
    else
    {
        QStringList pointCoordinates = controller->getPoint(pointNumber);
        for(int i = 0; i < ui->addPointArgumentsTableWidget->columnCount(); i++)
        {
            ui->addPointArgumentsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            for(int j = 0; j < ui->addPointArgumentsTableWidget->rowCount(); j++)
            {
                // j - номер оси
                ui->addPointArgumentsTableWidget->setItem(i, j, new QTableWidgetItem(pointCoordinates[j]));
            }
        }
    }
}
