#ifndef PROGRAMVISUALIZEWIDOW_H
#define PROGRAMVISUALIZEWIDOW_H

#include <QDialog>

#include "gui/oglwidget.h"
#include "models/machinetool/machinetool.h"

namespace Ui {
class ProgramVisualizeWidow;
}

class ProgramVisualizeWidow : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramVisualizeWidow(QWidget *parent = 0, bool _run = false);
    ~ProgramVisualizeWidow();

private:
    Ui::ProgramVisualizeWidow *ui;

    bool run;
};

#endif // PROGRAMVISUALIZEWIDOW_H
