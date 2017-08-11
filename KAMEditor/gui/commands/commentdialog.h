#ifndef COMMENTDIALOG_H
#define COMMENTDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/comment.h"

namespace Ui {
class CommentDialog;
}

class CommentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommentDialog(CommandsManager* _commandsManager, size_t _position, QWidget *parent = 0);
    ~CommentDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CommentDialog *ui;
    CommandsManager* commandsManager;
    size_t position;
};

#endif // COMMENTDIALOG_H
