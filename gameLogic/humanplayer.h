#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include "playername.h"
#include <QObject>

class HumanPlayer : public QObject, public Player {
    Q_OBJECT
public:
    explicit HumanPlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name);
    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name pName);
    void doTurn(Card topCard, CardSuit wishedSuit, CardValue wishedValue, bool is4played, int drawCount);
    void gameInit(const std::vector<Card> hand,
                  const Card& topCard,
                  std::map<PLAYER::Name, int> otherPlayerCardCount,
                  std::vector<std::string> playerNames);
    void reciveCard(const Card& card);
    void playerWon(std::string _title);

signals:
    void UIinitPlayground(const std::vector<Card>& humanPlayerCards,
                          std::map<PLAYER::Name, int> otherPlayerCardCount,
                          const Card& topDepotCard,
                          std::vector<std::string> playerNames);

    void UIdoTurn(std::vector<Card> playableCards, CardSuit wishedSuit, CardValue wishedValue);

    void UIplayerPlaysCard(PLAYER::Name pName, const Card& playedCard);

    void UIplayerDrawsCard(PLAYER::Name pName);

    void UIaddPlayerCard(const Card& card);

    void UIPlayerWon(std::string _title);

public
slots:

    void UIplaysCard(const Card& card, CardSuit wishedSuit, CardValue wishedValue);

    void UIdrawsCard();
};
#endif // HUMANPLAYER_H
