#include "humanplayer.h"

HumanPlayer::HumanPlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name)
    : Player(playerName, _gameController, name)
{
}

void HumanPlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    emit UIplayerPlaysCard(pName, playedCard);
}

void HumanPlayer::otherDrawsCard(PLAYER::Name pName)
{
    emit UIplayerDrawsCard(pName);
}

void HumanPlayer::doTurn(Card topCard, CardSuit wishedSuit, CardValue wishedValue, bool is4played, int drawCount)
{
    emit UIdoTurn(this->getPlayableCards(topCard, wishedSuit, wishedValue, is4played,drawCount), wishedSuit, wishedValue);
}

void HumanPlayer::gameInit(const std::vector<Card> hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, std::vector<std::string> playerNames)
{
    this->hand = hand;
    emit UIinitPlayground(hand, otherPlayerCardCount, topCard, playerNames);
}

void HumanPlayer::reciveCard(const Card& card)
{
    hand.push_back(card);
    emit UIaddPlayerCard(card);
}

void HumanPlayer::playerWon(std::string _title)
{
    emit UIPlayerWon(_title);
}

void HumanPlayer::UIplaysCard(const Card& card, CardSuit wishedSuit, CardValue wishedValue)
{
    dropCard(card);
    gameController.playCard(card, wishedSuit, wishedValue);
}

void HumanPlayer::UIdrawsCard()
{
    gameController.drawCard();
}
