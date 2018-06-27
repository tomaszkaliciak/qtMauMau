#include "choosecolordialog.h"
#include "ui_choosecolordialog.h"
#include "settings.h"

ChooseColorDialog::ChooseColorDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ChooseColorDialog)
{
    ui->setupUi(this);

    QString deckNumber = Settings::getInstance()->getProperty("common/card_deck");
    QString imgExtension = Settings::getInstance()->getProperty("common/card_img_extension");

    ui->btnHearts->setIcon(QIcon(QPixmap(":/img/deck_" + deckNumber + "/hearts" + imgExtension)));
    ui->btnHearts->installEventFilter(this);

    ui->btnDiamonds->setIcon(QIcon(QPixmap(":/img/deck_" + deckNumber + "/diamonds" + imgExtension)));
    ui->btnDiamonds->installEventFilter(this);

    ui->btnClubs->setIcon(QIcon(QPixmap(":/img/deck_" + deckNumber + "/clubs" + imgExtension)));
    ui->btnClubs->installEventFilter(this);

    ui->btnSpades->setIcon(QIcon(QPixmap(":/img/deck_" + deckNumber + "/spades" + imgExtension)));
    ui->btnSpades->installEventFilter(this);
}

/**
 * mouseButtonPress event
 * @brief ChooseColorDialog::eventFilter
 * @param obj
 * @param event
 * @return
 */
bool ChooseColorDialog::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        mousePressed(obj);
        break;
    default:
        break;
    }
    // pass the event on to the parent class
    return QDialog::eventFilter(obj, event);
}

/**
 * User clicked on one of the Card Buttons
 * @brief ChooseColorDialog::mousePressed
 * @param pressedButton
 */
void ChooseColorDialog::mousePressed(QObject* pressedButton)
{

    CardSuit cardSuit = CardSuit::HEARTS;

    if (pressedButton == ui->btnHearts) {
        cardSuit = CardSuit::HEARTS;
    } else if (pressedButton == ui->btnDiamonds) {
        cardSuit = CardSuit::DIAMONDS;
    } else if (pressedButton == ui->btnClubs) {
        cardSuit = CardSuit::CLUBS;
    } else if (pressedButton == ui->btnSpades) {
        cardSuit = CardSuit::SPADES;
    }
    this->done(static_cast<int>(cardSuit));
}

ChooseColorDialog::~ChooseColorDialog()
{
    delete ui;
}
