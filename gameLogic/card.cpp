#include "card.h"
Card::Card(const CardSuit cSuit, const CardValue cValue)
    : suit(cSuit)
    , value(cValue)
{
}

Card::Card(const Card& card)
    : suit(card.getSuit())
    , value(card.getValue())
{
}

Card::Card()
    : suit(CardSuit(1))
    , value(CardValue(1))
{
}

CardSuit Card::getSuit() const
{
    return suit;
}

CardValue Card::getValue() const
{
    return value;
}

bool Card::operator==(const Card& card) const
{
    return ((card.getSuit() == suit)) && (card.getValue() == value);
}

bool Card::isFunctional()const {
    if (value == CardValue::TWO   ||
        value == CardValue::THREE ||
        value == CardValue::FOUR  ||
        value == CardValue::JACK  ||
        value == CardValue::QUEEN ||
        value == CardValue::KING  ||
        value == CardValue::ACE) {

        return true;
    }
    else {
        return false;
    }
}
