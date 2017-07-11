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

void AIPlayer::doTurn(Card topCard, Card::cardSuit wishedSuit, Card::cardValue whishedValue, bool& is4played, int drawCount, int toSkipCounter)
{
    std::vector<Card> playableCards = getPlayableCards(topCard, wishedSuit, whishedValue, is4played,drawCount,toSkipCounter);
    if (playableCards.size() > 0) {
        //TODO ai choose better card
        Card playCard = getPlayCard(playableCards);
        Card::cardSuit aiWhischedSuit;
        Card::cardValue aiWhischedValue;

        if (playCard.getValue() == Card::ACE) {
            aiWhischedSuit = getWhishedCardSuit();
            aiWhischedValue = Card::NONEE;
        }
        else if(playCard.getValue() == Card::JACK) {
            aiWhischedValue = getWhishedCardValue();
            aiWhischedSuit = Card::NONE;
        }
        else {
            aiWhischedSuit = Card::NONE;
            aiWhischedValue = Card::NONEE;
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

Card::cardSuit AIPlayer::getWhishedCardSuit()
{
    int suitsCount[4] = { 0 };
    for (unsigned i = 0; i < hand.size(); ++i) {
        if (hand[i].getValue() != Card::ACE) {
            suitsCount[hand[i].getSuit()]++;
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
    return Card::cardSuit(maxIndex);
}

Card::cardValue AIPlayer::getWhishedCardValue()
{
    // TODO AI choose card
    return Card::cardValue(4);
}
