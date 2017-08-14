#include "programvisualizewidow.h"
#include "ui_programvisualizewidow.h"

ProgramVisualizeWidow::ProgramVisualizeWidow(CommandsManager *_commandsManager, PointsManager *_pointsManager, QWidget *parent, bool _run) :
    QDialog(parent),
    ui(new Ui::ProgramVisualizeWidow),
    commandsManager(_commandsManager),
    run(_run)
{
    ui->setupUi(this);
    ui->rotatePushButton->setEnabled(false);
    ui->programOpenGLWidget->setCommandsManager(commandsManager);
    ui->programOpenGLWidget->setPointsManager(_pointsManager);
    showCommands();
}

ProgramVisualizeWidow::~ProgramVisualizeWidow()
{
    delete ui;
}

void ProgramVisualizeWidow::on_zoomInPushButton_clicked()
{
    ui->programOpenGLWidget->scaling(1);
}

void ProgramVisualizeWidow::on_zoomOutPushButton_clicked()
{
    ui->programOpenGLWidget->scaling(-1);
}

void ProgramVisualizeWidow::on_topPushButton_clicked()
{
    // поворот в плоскость X0Y
    ui->programOpenGLWidget->setXAngle(180);
    ui->programOpenGLWidget->setYAngle(0);
    ui->programOpenGLWidget->setZAngle(0);
    ui->programOpenGLWidget->rotate();
}

void ProgramVisualizeWidow::on_sidePushButton_clicked()
{
    // поворот в плоскость Y0Z
    ui->programOpenGLWidget->setXAngle(-90);
    ui->programOpenGLWidget->setYAngle(0);
    ui->programOpenGLWidget->setZAngle(90);
    ui->programOpenGLWidget->rotate();
}

void ProgramVisualizeWidow::on_frontPushButton_clicked()
{
    // поворот в плоскость X0Z
    ui->programOpenGLWidget->setXAngle(90);
    ui->programOpenGLWidget->setYAngle(180);
    ui->programOpenGLWidget->setZAngle(180);
    ui->programOpenGLWidget->rotate();
}

void ProgramVisualizeWidow::on_centerPushButton_clicked()
{
    ui->programOpenGLWidget->setScale(0.1);
    ui->programOpenGLWidget->update();
}

void ProgramVisualizeWidow::on_rotatePushButton_clicked()
{
    ui->movePushButton->setEnabled(true);
    ui->rotatePushButton->setEnabled(false);
    ui->programOpenGLWidget->setMouseMoveAction(1);
}

void ProgramVisualizeWidow::on_movePushButton_clicked()
{
    ui->rotatePushButton->setEnabled(true);
    ui->movePushButton->setEnabled(false);
    ui->programOpenGLWidget->setMouseMoveAction(0);
}

void ProgramVisualizeWidow::on_pointsCheckBox_clicked()
{
    ui->programOpenGLWidget->setPointsVisible(!(ui->programOpenGLWidget->getPointsVisible()));
}

void ProgramVisualizeWidow::showCommands()
{
    QStringList columnsHeaders =
    {
        "Команда",
        "Аргументы"
    };
    ui->commandsTableWidget->setColumnCount(columnsHeaders.size());
    ui->commandsTableWidget->setHorizontalHeaderLabels(columnsHeaders);

    QStringList rowsHeaders;
    for(unsigned int i = 0; i < commandsManager->getCommandsCount(); i++)
    {
        rowsHeaders.push_back(QString::number(i+1));
    }
    ui->commandsTableWidget->setRowCount(rowsHeaders.size());
    ui->commandsTableWidget->setVerticalHeaderLabels(rowsHeaders);

    for (int i = 0; i < ui->commandsTableWidget->horizontalHeader()->count(); i++)
    {
        ui->commandsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->commandsTableWidget->verticalHeader()->count(); j++)
        {
            QTableWidgetItem *item = fillCommandsTable(j, i);
            ui->commandsTableWidget->setItem(j, i, item);
        }
    }
}

QTableWidgetItem *ProgramVisualizeWidow::fillCommandsTable(unsigned int row, unsigned int column)
{
    QString text = "Здесь должна быть команда";
    switch (column) {
    case 0:
    {
        text = QString::fromStdString(commandsManager->operator [](row)->getName());
        break;
    }
    case 1:
    {
        text = "";
        QStringList argumentsTmp = commandsManager->operator [](row)->getArguments();
        for(auto argument : argumentsTmp)
        {
            text += argument + ", ";
        }
        break;
    }
    default:
    {
        text = "Unknown parametr";
        break;
    }
    }
    return new QTableWidgetItem(text);
}
