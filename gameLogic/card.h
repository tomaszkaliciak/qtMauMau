#ifndef CARD_H_
#define CARD_H_
/**
 * @brief The Card class represents a card with a card suit and a card value
 */
class Card {
public:
    enum cardSuit {
        HEARTS = 0,
        DIAMONDS = 1,
        CLUBS = 2,
        SPADES = 3,
        NONE = -1
    };

    enum cardValue {
        TWO = 1,
        THREE = 2,
        FOUR = 3,
        FIVE = 4,
        SIX = 5,
        SEVEN = 6,
        EIGHT = 7,
        NINE = 8,
        TEN = 9,
        JACK = 10,
        QUEEN = 11,
        KING = 12,
        ACE = 13,
        NONEE = 14
    };

private:
    Card::cardSuit suit;
    Card::cardValue value;

public:
    Card(cardSuit cSuit, cardValue cValue);
    Card(const Card& card);
    Card();
    cardSuit getSuit() const;
    cardValue getValue() const;

    bool isFunctional() const;
    /**
     * @brief operator == checks if the values of the two cards are equal
     * @param card
     * @return
     */
    bool operator==(const Card& card) const;
};



#endif /* CARD_H_ */
