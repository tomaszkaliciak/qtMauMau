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

void HumanPlayer::doTurn(Card topCard, Card::cardSuit wishedSuit, Card::cardValue whishedValue, bool& is4played, int drawCount,int toSkipCounter)
{
    emit UIdoTurn(this->getPlayableCards(topCard, wishedSuit, whishedValue, is4played,drawCount,toSkipCounter), wishedSuit, whishedValue);
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

void HumanPlayer::UIplaysCard(const Card& card, Card::cardSuit whishedSuit, Card::cardValue whishedValue)
{
    dropCard(card);
    gameController.playCard(card, whishedSuit, whishedValue);
}

void HumanPlayer::UIdrawsCard()
{
    gameController.drawCard();
}
