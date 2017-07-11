#include "player.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

PLAYER::Name Player::getPName() const
{
    return playerName;
}

int Player::getCardCount() const
{
    return this->hand.size();
}

std::string Player::getTitle() const
{
    return title;
}

Player::Player(PLAYER::Name pName, GameControllerProxy _gameController, std::string title)
    : playerName(pName)
    , gameController(_gameController)
    , title(title)
{
}

Player::~Player()
{

}

std::vector<Card> Player::getPlayableCards(const Card& card, Card::cardSuit wishedSuit, Card::cardValue wishedValue, bool& is4played, int drawCount, int& toSkipCounter)
{
    std::vector<Card> playableCards;
    for (unsigned i = 0; i < hand.size(); ++i) {
        if(card.getValue() == Card::FOUR && is4played) { // czwórka na stole
            if(hand[i].getValue() == Card::FOUR) {  // czwórka w rece
                playableCards.push_back(hand[i]);
                std::cout << "Nazywam sie " << getTitle() << " wartosc licznika " << toSkipCounter << std::endl;
            }
            else {
                roundsToSkip = toSkipCounter;
                toSkipCounter = 0;
                std::cout << "Nazywam sie " << getTitle() << " i czekam " << roundsToSkip << std::endl;
                is4played = false;
            }
        }
       else if (card.getValue() == Card::ACE) {
            if(Card::ACE == hand[i].getValue() || wishedSuit == hand[i].getSuit()){
                playableCards.push_back(hand[i]);
            }
        }
        else if (card.getValue() == Card::JACK) {
             if(Card::JACK == hand[i].getValue() || wishedValue == hand[i].getValue()){
                 playableCards.push_back(hand[i]);
             }
         }
        else if(card.getValue() == Card::TWO && drawCount) {
            if(hand[i].getValue() == Card::TWO                                           ||  // moza zagrac dwojke
              (hand[i].getValue() == Card::THREE && hand[i].getSuit() == card.getSuit()) || //trojke tego samego koloru
              (hand[i].getValue() == Card::KING && hand[i].getSuit() == Card::HEARTS)) {     // krola serce
                playableCards.push_back(hand[i]);
            }
        }
        else if(card.getValue() == Card::THREE && drawCount) {
            if(hand[i].getValue() == Card::THREE                                         ||  // mozna zagrac trójke
              (hand[i].getValue() == Card::TWO && hand[i].getSuit() == card.getSuit())   ||  //dwojke tego samego koloru
              (hand[i].getValue() == Card::KING && hand[i].getSuit() == Card::HEARTS)) {      // krola serce
                playableCards.push_back(hand[i]);
            }
        }
        else if(card.getValue() == Card::KING && card.getSuit() == Card::HEARTS && drawCount) { // krol serce
            if((hand[i].getValue() == Card::TWO && hand[i].getSuit() == card.getSuit())     ||  // dwojke serce
              (hand[i].getValue() == Card::THREE && hand[i].getSuit() == card.getSuit())) {    // trojke serce
                playableCards.push_back(hand[i]);
            }
        }
        else {
            if (card.getValue() == hand[i].getValue() || card.getSuit() == hand[i].getSuit()) {
                playableCards.push_back(hand[i]);
            }

       }
    }
    return playableCards;
}

void Player::dropCard(const Card& card)
{
    std::vector<Card>::iterator pos = std::find(hand.begin(), hand.end(), card);

    if (pos != hand.end()) {
        hand.erase(pos);
    } else {
        throw std::range_error("Card not found in hand.");
    }
}

bool Player::skipPlayer() {
    if(roundsToSkip) {
        --roundsToSkip;
        return true;
    }
    else {
        return false;
    }
}
