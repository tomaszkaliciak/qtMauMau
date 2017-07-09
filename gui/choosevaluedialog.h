#ifndef CHOOSEVALUEDIALOG_H
#define CHOOSEVALUEDIALOG_H

#include <QDialog>
#include <gameLogic/card.h>

namespace Ui {
class ChooseValueDialog;
}

class ChooseValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseValueDialog(QWidget *parent = 0);
    ~ChooseValueDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChooseValueDialog *ui;
};

#endif // CHOOSEVALUEDIALOG_H
