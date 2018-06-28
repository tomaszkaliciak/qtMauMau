#include "aiplayer.h"
#include <cstdlib>
#include <ctime>

AIPlayer::AIPlayer(PLAYER::Name pName, GameControllerProxy _gameController, std::string name)
    : Player(pName, _gameController, name)
{
    srand(time(NULL));
}

void AIPlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    (void)(pName);
    (void)(playedCard);
}

void AIPlayer::otherDrawsCard(PLAYER::Name pName)
{
    (void)(pName);
}

void AIPlayer::doTurn(Card topCard, CardSuit wishedSuit, CardValue wishedValue, bool is4played, int drawCount)
{
    std::vector<Card> playableCards = getPlayableCards(topCard, wishedSuit, wishedValue, is4played,drawCount);
    if (playableCards.size() > 0) {

        Card playCard = getPlayCard(playableCards);
        CardSuit aiWhischedSuit = CardSuit::NONE;
        CardValue aiWhischedValue = CardValue::NONE;

        if (playCard.getValue() == CardValue::ACE) {
            aiWhischedSuit = getwishedCardSuit();
        }
        else if(playCard.getValue() == CardValue::JACK) {
            aiWhischedValue = getwishedCardValue();
        }
        dropCard(playableCards.at(0));
        gameController.playCard(playCard, aiWhischedSuit, aiWhischedValue);
        topCard = playCard;
    } else {
        gameController.drawCard();
    }
}

void AIPlayer::gameInit(const std::vector<Card> hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, std::vector<std::string> playerNames)
{
    this->hand = hand;
    (void)(topCard);
    (void)(otherPlayerCardCount);
    (void)(playerNames);
}

void AIPlayer::reciveCard(const Card& card)
{
    this->hand.push_back(card);
}

void AIPlayer::playerWon(std::string _title)
{
    (void)(_title);
}

Card AIPlayer::getPlayCard(std::vector<Card> playableCards)
{
    return playableCards.at(rand() % playableCards.size());
}

CardSuit AIPlayer::getwishedCardSuit()
{
    int suitsCount[4] = { 0 };
    for (unsigned i = 0; i < hand.size(); ++i) {
        if (hand[i].getValue() != CardValue::ACE) {
            suitsCount[static_cast<int>(hand[i].getSuit())]++;
        }
    }
    int maxIndex = 0;
    int maxCount = 0;
    for (unsigned i = 0; i < 4; ++i) {
        if (suitsCount[i] > maxCount) {
            maxCount = suitsCount[i];
            maxIndex = i;
        }
    }
    return CardSuit(maxIndex);
}

CardValue AIPlayer::getwishedCardValue()
{
    // TODO AI choose card
    return CardValue(4);
}
