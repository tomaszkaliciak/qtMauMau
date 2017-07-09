#include "choosevaluedialog.h"
#include "ui_choosevaluedialog.h"

ChooseValueDialog::ChooseValueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseValueDialog)
{
    ui->setupUi(this);
}

ChooseValueDialog::~ChooseValueDialog()
{
    delete ui;
}

void ChooseValueDialog::on_pushButton_clicked()
{
    int cardValue = 0;
    int index = ui->comboBox->currentIndex();
    if(index >= 0 && index <= 5) {
        cardValue = index + 4;
    }
    else if (index == 6) {
        cardValue = 11;
    }
    this->done(cardValue);
}
