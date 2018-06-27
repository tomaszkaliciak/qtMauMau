#include "gamecontrollerproxy.h"
#include "gamecontroller.h"

GameControllerProxy::GameControllerProxy(GameController* _gameContr, PLAYER::Name _pName)
    : gameContr(_gameContr)
    , pName(_pName)
{
}

void GameControllerProxy::playCard(const Card& card, CardSuit whishedSuit, CardValue whishedValue )
{
    gameContr->playCard(pName, card, whishedSuit, whishedValue);
}

void GameControllerProxy::drawCard()
{
    gameContr->drawCard(pName);
}


