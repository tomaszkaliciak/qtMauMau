#ifndef GAMECONTROLLERPROXY_H
#define GAMECONTROLLERPROXY_H

#include "card.h"
#include "playername.h"

class GameController;

class GameControllerProxy {
private:
    GameController* gameContr;
    PLAYER::Name pName;

public:
    explicit GameControllerProxy(GameController* _gameContr, PLAYER::Name _pName);
    void playCard(const Card& card, CardSuit whishedSuit, CardValue whishedValue);
    void drawCard();

};

#endif // GAMECONTROLLERPROXY_H
