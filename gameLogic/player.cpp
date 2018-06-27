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

std::vector<Card> Player::getPlayableCards(const Card& card, CardSuit wishedSuit, CardValue wishedValue, bool is4played, int drawCount)
{
    std::vector<Card> playableCards;
    if(roundsToSkip) {
        return playableCards;
    }
    for (unsigned i = 0; i < hand.size(); ++i) {
        if(card.getValue() == CardValue::FOUR && is4played) { // czwórka na stole
            if(hand[i].getValue() == CardValue::FOUR ||  // czwórka w rece
               (hand[i].getValue() == CardValue::QUEEN && hand[i].getSuit() == CardSuit::SPADES)) {  // dama wino
                playableCards.push_back(hand[i]);
            }
        }
       else if (card.getValue() == CardValue::ACE) {                                              // as na stole
            if(CardValue::ACE == hand[i].getValue()                                     ||        // można zagrać asa
               wishedSuit == hand[i].getSuit()                                     ||        // zadany kolor
               (hand[i].getValue() == CardValue::QUEEN && hand[i].getSuit() == CardSuit::SPADES))  {  // dame wino
                playableCards.push_back(hand[i]);
            }
        }
        else if (card.getValue() == CardValue::JACK) {                                            // jopek na stole
             if(CardValue::JACK == hand[i].getValue()                                   ||        // mozna zagrac jopka
                wishedValue == hand[i].getValue()                                  ||        // zadana karte
                (hand[i].getValue() == CardValue::QUEEN && hand[i].getSuit() == CardSuit::SPADES)) {  // dame wino
                 playableCards.push_back(hand[i]);
             }
         }
        else if(card.getValue() == CardValue::TWO && drawCount) {                                 // dwojka na stole
            if(hand[i].getValue() == CardValue::TWO                                           ||  // moza zagrac dwojke
              (hand[i].getValue() == CardValue::THREE && hand[i].getSuit() == card.getSuit()) ||  //trojke tego samego koloru
              (hand[i].getValue() == CardValue::KING && hand[i].getSuit() == CardSuit::HEARTS && card.getSuit() == CardSuit::HEARTS )  ||   // krola serce jezeli na stosie 2 serce
              (hand[i].getValue() == CardValue::KING && hand[i].getSuit() == CardSuit::SPADES && card.getSuit() == CardSuit::SPADES )  ||    // krola wino jezeli na stosie 2 wino
              (hand[i].getValue() == CardValue::QUEEN && hand[i].getSuit() == CardSuit::SPADES)) {   // dame wino
                    playableCards.push_back(hand[i]);
            }
        }
        else if(card.getValue() == CardValue::THREE && drawCount) {                               // trojka na stole
            if(hand[i].getValue() == CardValue::THREE                                         ||  // mozna zagrac trójke
              (hand[i].getValue() == CardValue::TWO && hand[i].getSuit() == card.getSuit())   ||  //dwojke tego samego koloru
              (hand[i].getValue() == CardValue::KING && hand[i].getSuit() == CardSuit::HEARTS && card.getSuit() == CardSuit::HEARTS )  ||   // krola serce jezeli na stosie 3 serce
              (hand[i].getValue() == CardValue::KING && hand[i].getSuit() == CardSuit::SPADES && card.getSuit() == CardSuit::SPADES )  ||    // krola wino jezeli na stosie 3 wino
              (hand[i].getValue() == CardValue::QUEEN && hand[i].getSuit() == CardSuit::SPADES)) {    // dame wino
                    playableCards.push_back(hand[i]);
            }
        }
        else if(card.getValue() == CardValue::KING &&
               (card.getSuit() == CardSuit::HEARTS || card.getSuit() == CardSuit::SPADES) && // krol wino lub serce
                drawCount) {
            if((hand[i].getValue() == CardValue::TWO && hand[i].getSuit() == card.getSuit())     ||  // dwojke serce
              (hand[i].getValue() == CardValue::THREE && hand[i].getSuit() == card.getSuit())    ||  // trojke serce
              (hand[i].getValue() == CardValue::KING && hand[i].getSuit() == CardSuit::HEARTS)       ||  // krol serce
              (hand[i].getValue() == CardValue::KING && hand[i].getSuit() == CardSuit::SPADES)       ||  // krol wino
              (hand[i].getValue() == CardValue::QUEEN && hand[i].getSuit() == CardSuit::SPADES)) {       // dama wino
                playableCards.push_back(hand[i]);
            }
        }
        else if(card.getValue() == CardValue::QUEEN && card.getSuit() == CardSuit::SPADES) { // dama wino
            playableCards.push_back(hand[i]);                                       // wszystko na dame
        }
        else {
            if (card.getValue() == hand[i].getValue() || card.getSuit() == hand[i].getSuit() ||
                 (hand[i].getValue() == CardValue::QUEEN && hand[i].getSuit() == CardSuit::SPADES)) {
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

