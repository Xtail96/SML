#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>

#include "models/repository/repository.h"

namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointDialog(Repository &repository, QWidget *parent = nullptr);
    explicit AddPointDialog(Repository &repository, unsigned int pointNumber, QWidget *parent);
    ~AddPointDialog();
signals:

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPointDialog *ui;
    void setupFields();

    Repository& m_repository;

    bool m_Edit;
    unsigned int m_pointNumber;
};

#endif // ADDPOINTDIALOG_H
