#include "remoteplayer.h"

RemotePlayer::RemotePlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name)
    : Player(playerName, _gameController, name)
{
}

void RemotePlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    emit RemotePlayerPlaysCard(playerName, pName, playedCard);
}

void RemotePlayer::otherDrawsCard(PLAYER::Name pName)
{
    emit RemotePlayerDrawsCard(playerName, pName);
}

void RemotePlayer::doTurn(Card topCard, CardSuit wishedSuit, CardValue wishedValue, bool is4played, int drawCount)
{
    emit RemoteDoTurn(playerName, this->getPlayableCards(topCard, wishedSuit, wishedValue, is4played, drawCount), wishedSuit, wishedValue);
}

void RemotePlayer::gameInit(const std::vector<Card> hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, std::vector<std::string> playerNames)
{
    this->hand = hand;
    emit RemoteInitPlayground(playerName, hand, otherPlayerCardCount, topCard, playerNames);
}

void RemotePlayer::reciveCard(const Card& card)
{
    this->hand.push_back(card);
    emit RemoteAddPlayerCard(playerName, card);
}

void RemotePlayer::playerWon(std::string _title)
{
    emit RemotePlayerWon(playerName, _title);
}

void RemotePlayer::RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card, CardSuit wishedSuit, CardValue wishedValue)
{
    if (playerName == remotePlayerName) {
        dropCard(card);
        gameController.playCard(card, wishedSuit, wishedValue);
    }
}
void RemotePlayer::RemoteDrawsCard(PLAYER::Name remotePlayerName)
{
    if (playerName == remotePlayerName) {
        gameController.drawCard();
    }
}
