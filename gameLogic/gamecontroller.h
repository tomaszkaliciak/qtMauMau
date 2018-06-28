#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <stdexcept>
#include <vector>
#include "deck.h"

#include "player.h"
#include "playername.h"
#include "card.h"


class GameController {
private:
    std::vector<Player*> players;
    Deck cardStack;
    Deck cardDepot;
    std::vector<PLAYER::Name> playerOrder;
    bool playerPlayed = false;
    bool aPlayerWon = false;
    bool changedDirection = false;
    CardSuit wishedSuit = CardSuit::NONE;
    CardValue wishedValue = CardValue::NONE;
    int drawCount = 0;
    int toSkipCounter = 0;
    bool is4played = false;

    //special cards
    CardValue draw2xCard = CardValue::TWO;
    CardValue draw3xCard = CardValue::THREE;
    CardValue wishSuitCard = CardValue::ACE;
    CardValue skipNextCard = CardValue::FOUR;
    CardValue changeDirectCard = CardValue::NONE;

public:
    explicit GameController();
    ~GameController();
    void setPlayers(std::vector<Player*> _players);
    void gameInit();
    void playCard(PLAYER::Name pName, const Card& card, CardSuit wishedSuit, CardValue wishedValue);
    void drawCard(PLAYER::Name pName);


private:
    void nextTurn();
    void setNextPlayer();
    void playerDrawCard(PLAYER::Name pName);
    void handleMultiDraw();
    void setFlags(const Card& card);
    void playerWon(PLAYER::Name playerName);
    std::vector<std::string> getPlayerNames();
};

#endif // GAMECONTROLLER_H
