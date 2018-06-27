#ifndef GAMECONTROLLERPROXY_H
#define GAMECONTROLLERPROXY_H

#include "card.h"
#include "playername.h"

class GameController;
/**
 * @brief The GameControllerProxy class is connection class for players to call gamecontroller methods
 */
class GameControllerProxy {
private:
    GameController* gameContr;
    PLAYER::Name pName;

public:
    /**
     * @brief GameControllerProxy
     * @param _gameContr the gamecontroller this class is a proxy for
     * @param _pName the name of the player the object is given to.
     */
    explicit GameControllerProxy(GameController* _gameContr, PLAYER::Name _pName);
    /**
     * @brief playCard calls play card on the gamecontroller
     * @param card the played card
     * @param whishedSuit the wished suit or Card::NONE
     */
    void playCard(const Card& card, CardSuit whishedSuit, CardValue whishedValue);
    /**
     * @brief drawCard calls draw card on the gamecontroller
     */
    void drawCard();

};

#endif // GAMECONTROLLERPROXY_H
