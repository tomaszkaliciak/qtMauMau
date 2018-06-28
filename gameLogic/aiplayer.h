#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player {
#ifdef TEST
    friend class AIPlayer_test;
#endif
public:
    explicit AIPlayer(PLAYER::Name playerName,
                      GameControllerProxy _gameController,
                      std::string name);

    void otherPlaysCard(PLAYER::Name playerName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name playerName);
    void doTurn(Card topCard, CardSuit wishedSuit, CardValue wishedValue, bool is4played, int drawCount);
    void gameInit(const std::vector<Card> hand,
                  const Card& topCard,
                  std::map<PLAYER::Name, int> otherPlayerCardCount,
                  std::vector<std::string> playerNames);
    void reciveCard(const Card& card);
    void playerWon(std::string _title);

private:
    Card getPlayCard(std::vector<Card> playableCards);
    CardSuit getwishedCardSuit();
    CardValue getwishedCardValue();
};

#endif // AIPLAYER_H
