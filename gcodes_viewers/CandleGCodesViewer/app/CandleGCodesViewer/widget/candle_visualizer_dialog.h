#ifndef CANDLEVISUALIZERDIALOG_H
#define CANDLEVISUALIZERDIALOG_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QProgressDialog>
#include <QCloseEvent>
#include <QDebug>

#include "gcodes_visualizer.h"

namespace Ui {
class CandleVisualizerDialog;
}

class CandleVisualizerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CandleVisualizerDialog(QStringList program, QWidget *parent = nullptr);
    ~CandleVisualizerDialog();

    void loadFile(QStringList data);

private slots:
    void on_topToolButton_clicked();

    void on_frontToolButton_clicked();

    void on_sideToolButton_clicked();

    void on_isometricToolButton_clicked();

private:
    Ui::CandleVisualizerDialog *ui;

    GCodesVisualizer* m_gcodesVisualizer;

    void closeEvent(QCloseEvent *e);
};

#endif // CANDLEVISUALIZERDIALOG_H
