#include "to_selection_point_dialog.h"
#include "ui_to_selection_point_dialog.h"

ToSelectionPointDialog::ToSelectionPointDialog(QTableWidget *_currentTableWidget, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToSelectionPointDialog),
    currentTableWidget(_currentTableWidget)
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
    currentTableWidget->selectRow(pointNumber);
}
