#ifndef CANDLEVISUALIZERDIALOG_H
#define CANDLEVISUALIZERDIALOG_H

#include <QDialog>

namespace Ui {
class CandleVisualizerDialog;
}

class CandleVisualizerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CandleVisualizerDialog(QWidget *parent = 0);
    ~CandleVisualizerDialog();

private:
    Ui::CandleVisualizerDialog *ui;
};

#endif // CANDLEVISUALIZERDIALOG_H
