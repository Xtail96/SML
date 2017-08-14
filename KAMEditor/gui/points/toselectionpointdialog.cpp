#include "toselectionpointdialog.h"
#include "ui_toselectionpointdialog.h"

ToSelectionPointDialog::ToSelectionPointDialog(MovementsHandler *_movementsHandler, PointsManager *_pointsManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToSelectionPointDialog),
    movementsHandler(_movementsHandler),
    pointsManager(_pointsManager)
{
    ui->setupUi(this);
}

ToSelectionPointDialog::~ToSelectionPointDialog()
{
    delete ui;
}

void ToSelectionPointDialog::on_buttonBox_accepted()
{
    unsigned int pointNumber = ui->toPointNumberLineEdit->text().toUInt() - 1;
    try
    {
        std::shared_ptr<Point> point = pointsManager->operator [](pointNumber);
        AddPointDialog(movementsHandler, pointsManager, point, pointNumber, this).exec();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }

    /*QString point_number_str = ui->mouse_to_point_lineEdit->text();
    unsigned int point_number = point_number_str.toUInt() - 1;

    if (!PointsManager::Instance().setSelectedPoint(point_number))
    {
        QMessageBox(QMessageBox::Information, "Сообщение", QString("Точка с таким номером отстутсвует в таблице")).exec();
    }*/
}
