#include "programvisualizewidow.h"
#include "ui_programvisualizewidow.h"

ProgramVisualizeWidow::ProgramVisualizeWidow(CommandsInterpreter *_commandsInterpreter, PointsManager *_pointsManager, QWidget *parent, bool _run) :
    QDialog(parent),
    ui(new Ui::ProgramVisualizeWidow),
    commandsInterpreter(_commandsInterpreter),
    run(_run)
{
    ui->setupUi(this);
    ui->rotatePushButton->setEnabled(false);
    ui->programOpenGLWidget->setCommandsInterpreter(commandsInterpreter);
    ui->programOpenGLWidget->setPointsManager(_pointsManager);

    SettingsManager settingsManager;
    try
    {
        ui->programOpenGLWidget->setGridMaximalAccuracy(settingsManager.get("Visualisation", "Grid Maximal Accuracy").toDouble());
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }

    showCommands();

    connect(ui->programOpenGLWidget, SIGNAL(offsetsChanged()), this, SLOT(showOffsets()));
    showOffsets();
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
    for(unsigned int i = 0; i < commandsInterpreter->commandsCount(); i++)
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
        text = QString::fromStdString(commandsInterpreter->operator [](row)->getName());
        break;
    }
    case 1:
    {
        text = "";
        QStringList argumentsTmp = commandsInterpreter->operator [](row)->getArguments();
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

void ProgramVisualizeWidow::on_acceptOptionsPushButton_clicked()
{
    if(ui->gridCheckBox->isChecked())
    {
        std::string gridPlane = ui->gridPlaneComboBox->currentText().toStdString();

        int gridSize = ui->gridSizeLineEdit->text().toInt();
        if(gridSize < 0)
        {
            gridSize = minimalGridSize;
            ui->gridSizeLineEdit->setText(QString::number(gridSize));
        }

        double gridCellSize = std::max(ui->gridCellSizeLineEdit->text().toDouble(), ui->programOpenGLWidget->getGridMaximalAccuracy());
        ui->gridCellSizeLineEdit->setText(QString::number(gridCellSize));

        ui->programOpenGLWidget->setGridPlane(gridPlane);
        ui->programOpenGLWidget->setGridSize((unsigned int) (gridSize));
        ui->programOpenGLWidget->setGridCellSize(gridCellSize);
        ui->programOpenGLWidget->setGridVisible(true);
    }
    else
    {
        ui->programOpenGLWidget->setGridVisible(false);
    }

    if(ui->pointsCheckBox->isChecked())
    {
        ui->programOpenGLWidget->setPointsVisible(true);
    }
    else
    {
        ui->programOpenGLWidget->setPointsVisible(false);
    }

    ui->programOpenGLWidget->repaint();
}

void ProgramVisualizeWidow::showOffsets()
{
    Point3D generalOffset = ui->programOpenGLWidget->getGeneralOffset();
    Point3D positiveOffset = ui->programOpenGLWidget->getMaxPositiveOffset();
    Point3D negativeOffset = ui->programOpenGLWidget->getMaxNegativeOffset();

    QString qPositiveXOffsetString = "X+: " + QString::number(positiveOffset.x) + " мм"  + '\n';
    QString qPositiveYOffsetString = "Y+: " + QString::number(positiveOffset.y) + " мм"  + '\n';
    QString qPositiveZOffsetString = "Z+: " + QString::number(positiveOffset.z) + " мм"  + '\n';

    QString qNegativeXOffsetString = "X-: " + QString::number(negativeOffset.x) + " мм"  + '\n';
    QString qNegativeYOffsetString = "Y-: " + QString::number(negativeOffset.y) + " мм"  + '\n';
    QString qNegativeZOffsetString = "Z-: " + QString::number(negativeOffset.z) + " мм"  + '\n';

    QString qGeneralXOffsetString = "dX: " + QString::number(generalOffset.x) + " мм"  + '\n';
    QString qGeneralYOffsetString = "dY: " + QString::number(generalOffset.y) + " мм"  + '\n';
    QString qGeneralZOffsetString = "dZ: " + QString::number(generalOffset.z) + " мм"  + '\n';

    QString qDimensionsString = qPositiveXOffsetString + qNegativeXOffsetString + qGeneralXOffsetString + '\n' +
            qPositiveYOffsetString + qNegativeYOffsetString + qGeneralYOffsetString + '\n' +
            qPositiveZOffsetString + qNegativeZOffsetString + qGeneralZOffsetString;

    ui->dimensionsTextEdit->setText(qDimensionsString);
}
