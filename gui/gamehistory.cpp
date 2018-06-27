#include "gamehistory.h"


GameHistory::GameHistory()
{
    file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Append);
    if (file->size() > 5000) {
        file->remove();
        delete file;
        file = new QFile(filename);
        file->open(QIODevice::WriteOnly | QIODevice::Append);
    }
}

/**
 * Write a Text in the History Doc
 * @brief GameHistory::write
 * @param text
 */
void GameHistory::write(QString text)
{
    QTextStream out(file);
    out.setAutoDetectUnicode(true);
    out << text << "\n";
}

/**
 * writes a Text + the Card suites + values in the History Doc
 * @brief GameHistory::write
 * @param text
 * @param cards
 */
void GameHistory::write(QString text, QVector<CardItem*>* cards)
{
    QString hand;
    for (int i = 0; i < cards->size(); ++i) {
        hand += cardToString(*(cards->at(i)));
        hand += " ";
    }
    QString full(text + " - "+ hand);
    QTextStream out(file);
    out.setAutoDetectUnicode(true);
    out << full << "\n";
}

/**
 * writes a Text + the Card suit and value in the History Doc
 * @brief GameHistory::write
 * @param text
 * @param card
 */
void GameHistory::write(QString text, CardItem &card)
{
    QString hand;
    hand += cardToString(card);
    QString full(text + " - "+ hand);
    QTextStream out(file);
    out.setAutoDetectUnicode(true);
    out << full << "\n";
}

/**
 * writes a Text + the Card suit and value in the History doc
 * @brief GameHistory::write
 * @param text
 * @param suit
 * @param value
 */
void GameHistory::write(QString text, CardSuit suit, CardValue value)
{
    QString hand;
    Card c = Card(suit,value);
    CardItem item = CardItem(c);
    hand += cardToString(item);
    QString full(text + " - "+ hand);
    QTextStream out(file);
    out.setAutoDetectUnicode(true);
    out << full << "\n";
}

QString GameHistory::cardToString(CardItem item){
        QString hand;
        switch (item.getCard().getValue()) {
        case CardValue::TWO: hand += "2 "; break;
        case CardValue::THREE: hand += "3 "; break;
        case CardValue::FOUR: hand += "4 "; break;
        case CardValue::FIVE: hand += "5 "; break;
        case CardValue::SIX: hand += "6 "; break;
        case CardValue::SEVEN: hand += "7 "; break;
        case CardValue::EIGHT: hand += "8 "; break;
        case CardValue::NINE: hand += "9 "; break;
        case CardValue::TEN: hand += "10 "; break;
        case CardValue::JACK: hand += "Jack "; break;
        case CardValue::QUEEN: hand += "Queen "; break;
        case CardValue::KING: hand += "King "; break;
        case CardValue::ACE: hand += "Ace "; break;
        case CardValue::NONE: hand += "NONEE "; break;
        }

        switch (item.getCard().getSuit()) {
        case CardSuit::HEARTS: hand += "Hearts"; break;
        case CardSuit::SPADES: hand += "Spades"; break;
        case CardSuit::DIAMONDS: hand += "Diamonds"; break;
        case CardSuit::CLUBS: hand += "Clubs"; break;
        default: break;
        }
        return hand;
}
GameHistory::~GameHistory(){
    delete file;
}
