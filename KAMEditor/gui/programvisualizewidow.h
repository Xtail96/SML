#ifndef PROGRAMVISUALIZEWIDOW_H
#define PROGRAMVISUALIZEWIDOW_H

#include <QDialog>

namespace Ui {
class ProgramVisualizeWidow;
}

class ProgramVisualizeWidow : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramVisualizeWidow(QWidget *parent = 0);
    ~ProgramVisualizeWidow();

private:
    Ui::ProgramVisualizeWidow *ui;
};

#endif // PROGRAMVISUALIZEWIDOW_H
