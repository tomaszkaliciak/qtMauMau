#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include <QObject>
#include "player.h"


class RemotePlayer : public QObject, public Player {
    Q_OBJECT
public:

    explicit RemotePlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name);

    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name pName);
    void doTurn(Card topCard, CardSuit wishedSuit, CardValue whishedValue, bool is4played, int drawCount);
    void gameInit(const std::vector<Card> hand,
                  const Card& topCard,
                  std::map<PLAYER::Name, int> otherPlayerCardCount,
                  std::vector<std::string> playerNames);
    void reciveCard(const Card& card);
    void playerWon(std::string _title);

signals:
    void RemoteInitPlayground(PLAYER::Name remotePlayerName,
                              const std::vector<Card>& remotePlayerCards,
                              std::map<PLAYER::Name, int> otherPlayerCardCount,
                              const Card& topDepotCard,
                              std::vector<std::string> playerNames);

    void RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, CardSuit wishedSuit, CardValue whishedValue);

    void RemotePlayerPlaysCard(PLAYER::Name remotePlayerName, PLAYER::Name pName, const Card& playedCard);

    void RemotePlayerDrawsCard(PLAYER::Name remotePlayerName, PLAYER::Name pName);

    void RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card& card);

    void RemotePlayerWon(PLAYER::Name remotePlayerName, std::string _title);

public
slots:

    void RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card, CardSuit wishedSuit, CardValue whishedValue);

    void RemoteDrawsCard(PLAYER::Name remotePlayerName);
};

#endif // REMOTEPLAYER_H
