#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>
#include "models/machinetool/machinetool.h"
#include "models/machinetool/pointsmanager/pointsmanager.h"
#include "models/machinetool/pointsmanager/point/point.h"

namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointDialog(MovementsHandler *_movementsHandler, PointsManager *_pointsManager, QWidget *parent = 0);
    explicit AddPointDialog(MovementsHandler *_movementsHandler, PointsManager *_pointsManager, std::shared_ptr<Point> pointForEdit, unsigned int _pointNumber, QWidget *parent = 0);
    ~AddPointDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPointDialog *ui;
    void initializeFields();

    bool isEdit;
    MovementsHandler* movementsHandler;
    PointsManager* pointsManager;
    unsigned int pointNumber;
    std::vector< std::shared_ptr<Axis> > axises;
};

#endif // ADDPOINTDIALOG_H
