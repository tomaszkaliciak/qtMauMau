#ifndef CARD_H_
#define CARD_H_


enum class CardSuit {
    HEARTS = 1,
    DIAMONDS,
    CLUBS,
    SPADES,
    NONE,
};

enum class CardValue {
    NONE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
};

class Card {
private:
    CardSuit suit;
    CardValue value;

public:
    Card(CardSuit cSuit, CardValue cValue);
    Card(const Card& card);
    Card();
    CardSuit getSuit() const;
    CardValue getValue() const;

    bool isFunctional() const;
    bool operator==(const Card& card) const;
};



#endif /* CARD_H_ */
