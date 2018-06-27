#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <gui/carditem.h>
#include <vector>
#include <QString>
#include <QGraphicsColorizeEffect>
#include <QGraphicsTextItem>
#include <QColor>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <QString>
#include <QPainter>
#include <QTextCursor>

class PlayerItem : public QObject {
    Q_OBJECT
public:
    enum direction {
        LEFT = 1,
        TOP = 2,
        RIGHT = 3,
        HUMAN = 4
    };

    PlayerItem(direction dir, int cardCount, int xCenter, int yCenter, QString _playername, QObject* parent = 0);
    PlayerItem(direction dir, std::vector<Card> humanCards, int xCenter, int yCenter, QString _playername);
    void createCards(int cardCount);
    void setPlayableCards(std::vector<Card> playableCards);
    void unsetPlayableCards();
    direction getDirection();
    QVector<CardItem*>* getCards();
    void removeCard(const Card& card);
    CardItem* addCard(const Card& card);
    CardItem* findCard(const Card& card, bool returnLastCard = false);
    CardItem::specialCards getSpecialCard();
    QGraphicsTextItem* getPlayername();
    void setActive(CardSuit wishSuitCard = CardSuit::NONE, CardValue wishValueCard = CardValue::NONE);
    void setUnactive();
    void rearrangePlayer(int xCenter, int yCenter);
    ~PlayerItem();

private:
    void measureLayout(int cardCount);
    void createHumanCards(std::vector<Card> humanCards);
    QVector<CardItem*>* cards = new QVector<CardItem*>();
    CardItem::specialCards specialCard;
    PlayerItem::direction playerDirection;
    int xCenter;
    int yCenter;

    QString wish = "";
    QGraphicsTextItem *playername = nullptr;

    int nameX;
    int nameY;
    int x;
    int y;

    //TODO: set in config.ini not in the code
    int cardWidth = 71;
    int cardHeight = 96;
    int cardGap = 20;
    int borderMargin = 50;
    int offsetPlayableCard = 20;

signals:

public
slots:
};

#endif // PLAYERITEM_H
