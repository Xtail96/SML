#include "kabriolwidget.h"
#include "ui_kabriolwidget.h"

kabriolWidget::kabriolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::kabriolWidget)
{
    ui->setupUi(this);
}

kabriolWidget::~kabriolWidget()
{
    delete ui;
}
