#include "toselectionpointdialog.h"
#include "ui_toselectionpointdialog.h"

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
