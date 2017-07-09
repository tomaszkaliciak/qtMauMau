#include "gamecontroller.h"
#include "gamecontrollerproxy.h"
#include <iostream>

GameController::GameController()
    : cardStack(Deck::FULL)
{
}

GameController::~GameController()
{
    for (unsigned i = 0; i < players.size(); ++i) {
        if (players.at(i) != NULL)
            delete players.at(i);
    }
}

void GameController::setPlayers(std::vector<Player*> _players)
{
    for (unsigned i = 0; i < _players.size(); ++i) {
        players.push_back(_players.at(i));
        playerOrder.push_back(PLAYER::Name(i));
    }
}

void GameController::gameInit()
{

    cardStack.shuffleManager();

    cardDepot.pushCard(cardStack.getLast(cardDepot));

    std::vector<std::vector<Card> > playerCards;
    for (unsigned i = 0; i < players.size(); i++) {
        playerCards.push_back(std::vector<Card>());
        for (int j = 0; j < 5; j++) {
            playerCards.at(i).push_back(cardStack.getLast(cardDepot));
        }
    }

    std::map<PLAYER::Name, int> otherPlayerCardCount;
    for (unsigned int i = 0; i < players.size(); ++i) {
        otherPlayerCardCount.insert(std::pair<PLAYER::Name, int>(PLAYER::Name(i), playerCards.at(i).size()));
    }
    for (unsigned i = 0; i < players.size(); ++i) {

        players[i]->gameInit(playerCards.at(i), cardDepot.back(), otherPlayerCardCount, getPlayerNames());
    }
    players[playerOrder[0]]->doTurn(cardDepot.back(), Card::NONE, Card::NONEE, is4played, drawCount, toSkipCounter);
}

void GameController::playCard(PLAYER::Name pName, const Card& card, Card::cardSuit whishedSuit, Card::cardValue whishedValue)
{
    if (playerOrder[0] == pName && !playerPlayed) {

        playerPlayed = true;
        this->wishedSuit = whishedSuit;
        this->wishedValue = whishedValue;
        cardDepot.pushCard(card);

        for (unsigned i = 0; i < players.size(); ++i) {
            if (players.at(i)->getPName() != pName) {
                players.at(i)->otherPlaysCard(pName, cardDepot.back());
            }
        }
        setFlags(card);
        if (!players[playerOrder[0]]->getCardCount()) {
            playerWon(playerOrder[0]);
        }
        if (players[playerOrder[1]]->skipPlayer()) {
        //    players[playerOrder[1]]->setNextPlayer();
        }
        nextTurn();
    }
}

void GameController::drawCard(PLAYER::Name pName)
{
    if (playerOrder[0] == pName && !playerPlayed) {
        playerPlayed = true;
        playerDrawCard(pName);
        handleMultiDraw();
        nextTurn();
    }
}

void GameController::nextTurn()
{
    if (!aPlayerWon) {
        playerPlayed = false;
        setNextPlayer();

        players[playerOrder[0]]->doTurn(cardDepot.back(), wishedSuit, wishedValue, is4played, drawCount, toSkipCounter);
    } else {
        // na razie gra toczy sie az ktos nie wygra, (ktos wygra -> koniec gry)
    }
}

void GameController::setFlags(const Card& card)
{

    if(cardDepot.back().getValue() == Card::FOUR) {
            ++toSkipCounter;
    }

    if (card.getValue() == changeDirectCard) {
        if (changedDirection) {
            changedDirection = false;
        } else {
            changedDirection = true;
        }
    }

    if (card.getValue() == Card::TWO || card.getValue() == Card::THREE ) {
        if (card.getValue() == Card::TWO && drawCount) {
            drawCount += 2;
        }
        else if(card.getValue() == Card::THREE && drawCount) {
            drawCount += 3;
        }
        else {
            if(card.getValue() == Card::TWO) {
                drawCount = 1;
            }
            else {
                drawCount = 2;
            }
        }
    }
    else {
        handleMultiDraw();
    }
}

void GameController::handleMultiDraw()
{
    if (drawCount) {
        for (int i = 0; i < drawCount; ++i) {
            playerDrawCard(playerOrder[0]);
        }
        drawCount = 0;
    }
}

void GameController::playerWon(PLAYER::Name playerName)
{
    for (unsigned i = 0; i < players.size(); ++i) {
        players[i]->playerWon(players.at(playerName)->getTitle());
    }
    aPlayerWon = true;
}

std::vector<std::string> GameController::getPlayerNames()
{
    std::vector<std::string> playerNames;
    for (unsigned i = 0; i < players.size(); ++i) {
        playerNames.push_back(players[i]->getTitle());
    }
    return playerNames;
}

void GameController::setNextPlayer()
{
    if (!changedDirection) {
        std::rotate(playerOrder.begin(), playerOrder.begin() + 1, playerOrder.end());
    } else {
        std::rotate(playerOrder.begin(), playerOrder.end() - 1, playerOrder.end());
    }
}

void GameController::playerDrawCard(PLAYER::Name pName)
{
    players[pName]->reciveCard(cardStack.getLast(cardDepot));
    for (unsigned i = 0; i < players.size(); ++i) {
        if (players.at(i)->getPName() != pName) {
            players.at(i)->otherDrawsCard(pName);
        }
    }
}
