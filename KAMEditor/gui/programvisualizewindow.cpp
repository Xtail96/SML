#include "programvisualizewindow.h"
#include "ui_programvisualizewindow.h"

ProgramVisualizeWindow::ProgramVisualizeWindow(MainWindowController *_controller, QWidget *parent, bool _run) :
    QDialog(parent),
    ui(new Ui::ProgramVisualizeWindow),
    run(_run)
{
    ui->setupUi(this);
    setupProgramVisualizeController(_controller);
    setupWidgets();
}

ProgramVisualizeWindow::~ProgramVisualizeWindow()
{
    delete ui;
    delete programVisualizeController;
}

void ProgramVisualizeWindow::on_zoomInPushButton_clicked()
{
    ui->programOpenGLWidget->scaling(1);
}

void ProgramVisualizeWindow::on_zoomOutPushButton_clicked()
{
    ui->programOpenGLWidget->scaling(-1);
}

void ProgramVisualizeWindow::on_topPushButton_clicked()
{
    // поворот в плоскость X0Y
    ui->programOpenGLWidget->setXAngle(0);
    ui->programOpenGLWidget->setZAngle(0);
    ui->programOpenGLWidget->updateField();
}

void ProgramVisualizeWindow::on_sidePushButton_clicked()
{
    // поворот в плоскость Y0Z
    ui->programOpenGLWidget->setXAngle(90);
    ui->programOpenGLWidget->setZAngle(90);
    ui->programOpenGLWidget->updateField();
}

void ProgramVisualizeWindow::on_frontPushButton_clicked()
{
    // поворот в плоскость X0Z
    ui->programOpenGLWidget->setXAngle(90);
    ui->programOpenGLWidget->setZAngle(0);
    ui->programOpenGLWidget->updateField();
}

void ProgramVisualizeWindow::on_centerPushButton_clicked()
{
    ui->programOpenGLWidget->setPositionX(0);
    ui->programOpenGLWidget->setPositionY(0);
    ui->programOpenGLWidget->updateField();
}

void ProgramVisualizeWindow::showCommands()
{
    QStringList columnsHeaders = programVisualizeController->getCommandsHeaders();
    ui->commandsTableWidget->setColumnCount(columnsHeaders.size());
    ui->commandsTableWidget->setHorizontalHeaderLabels(columnsHeaders);

    QStringList rowsHeaders = programVisualizeController->getCommandsNumbers();
    ui->commandsTableWidget->setRowCount(rowsHeaders.size());
    ui->commandsTableWidget->setVerticalHeaderLabels(rowsHeaders);


    QList<QTableWidgetItem*> commandsNames = programVisualizeController->getCommandsNames();
    QList<QTableWidgetItem*> commandsArguments = programVisualizeController->getCommandsArguments();

    for (int i = 0; i < ui->commandsTableWidget->rowCount(); i++)
    {
        ui->commandsTableWidget->setItem(i, 0, commandsNames[i]);
        ui->commandsTableWidget->setItem(i, 1, commandsArguments[i]);
    }


     for (int i = 0; i < ui->commandsTableWidget->columnCount(); i++)
     {
         ui->commandsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
     }
}

void ProgramVisualizeWindow::on_acceptOptionsPushButton_clicked()
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

void ProgramVisualizeWindow::showOffsets()
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

void ProgramVisualizeWindow::on_printPushButton_clicked()
{
    //QPrinter printer;
   // printer.setup(this);

    //QPainter painter(&printer);
    //QRect rect = painter.viewport();
    //int side = std::min(rect.height(), rect.width());
    //painter.setViewport(0, 0, side, side);
    //painter.setWindow(-50, -50, 100, 100);
}

void ProgramVisualizeWindow::setupWidgets()
{
    setupOGLWidget();
    showCommands();
    showOffsets();
}

void ProgramVisualizeWindow::setupOGLWidget()
{
    ui->programOpenGLWidget->setCommands(programVisualizeController->getCommands());
    ui->programOpenGLWidget->setPoints(programVisualizeController->get3DPoints());
    ui->programOpenGLWidget->setGridMaximalAccuracy(programVisualizeController->getGridMaximalAccuracy());
    connect(ui->programOpenGLWidget, SIGNAL(offsetsChanged()), this, SLOT(showOffsets()));
}

void ProgramVisualizeWindow::setupProgramVisualizeController(MainWindowController* controller)
{
    programVisualizeController = new ProgramVisualizeWindowController(controller);
    //connect(programVisualizeController, SIGNAL(ready()), this, SLOT(setupWidgets()));
}
