#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>
#include "models/pointsmanager/pointsmanager.h"

#include "models/machinetool.h"

namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointDialog(MachineTool *machineTool, QWidget *parent = 0);
    explicit AddPointDialog(MachineTool *machineTool, unsigned int _pointNumber, QWidget *parent);
    ~AddPointDialog();
signals:
    void newPoint(QStringList coordinates);
    void updatePointsCoordinates(QStringList coordinates, unsigned int number);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPointDialog *ui;
    void setupFields();

    MachineTool* m_machineTool;

    bool m_Edit;
    unsigned int m_pointNumber;
};

#endif // ADDPOINTDIALOG_H
