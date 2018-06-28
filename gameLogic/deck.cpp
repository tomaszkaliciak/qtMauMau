#include "deck.h"

Deck::Deck(Deck::InitStatus status)
{
    if (status == Deck::FULL) {
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 13; j++) {
                cards.push_back(Card(CardSuit(i), CardValue(j)));
            }
        }
        shuffleManager();
    }
}

void Deck::shuffleManager()
{
    shuffle();
    while(cards.back().isFunctional()) {
        shuffle();
    }
}

void Deck::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(cards.begin(), cards.end(), g);
}

void Deck::pushCard(const Card card)
{
    cards.push_back(card);
}

Card Deck::getLast(Deck& cardDepot)
{
    if (empty()) {
        if (cardDepot.empty()) {
            throw std::invalid_argument("cardDepot contains too few cards");
        } else {
            addCards(cardDepot.getUnderlyingCards());
        }
    }
    Card returned_card = cards.back();
    cards.pop_back();
    return returned_card;
}

Card Deck::back() const
{
    return cards.back();
}

bool Deck::empty() const
{
    return cards.empty();
}
Card Deck::getCard(int index) const
{
    return cards.at(index);
}

std::vector<Card> Deck::getUnderlyingCards()
{
    std::vector<Card> underlyingCards;
    underlyingCards = cards;
    underlyingCards.pop_back();
    cards.erase(cards.begin(), cards.end() - 1);
    return underlyingCards;
}

void Deck::addCards(std::vector<Card> newCards)
{
    cards.insert(cards.end(), newCards.begin(), newCards.end());
    shuffleManager();
}
