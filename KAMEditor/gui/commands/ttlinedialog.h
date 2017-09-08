#ifndef TTLINEDIALOG_H
#define TTLINEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/ttline.h"

namespace Ui {
class TTLineDialog;
}

class TTLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TTLineDialog(CommandsManager* _commandsManager, PointsManager* _pointsManager, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~TTLineDialog();

private slots:
    void on_buttonBox_accepted();
    void on_airPassageCheckBox_clicked();

private:
    Ui::TTLineDialog *ui;

    CommandsManager* commandsManager;
    PointsManager* pointsManager;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // TTLINEDIALOG_H
