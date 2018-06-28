#include "gamecontrollerproxy.h"
#include "gamecontroller.h"

GameControllerProxy::GameControllerProxy(GameController* _gameContr, PLAYER::Name _pName)
    : gameContr(_gameContr)
    , pName(_pName)
{
}

void GameControllerProxy::playCard(const Card& card, CardSuit wishedSuit, CardValue wishedValue )
{
    gameContr->playCard(pName, card, wishedSuit, wishedValue);
}

void GameControllerProxy::drawCard()
{
    gameContr->drawCard(pName);
}


