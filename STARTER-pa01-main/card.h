#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    Card(char s = ' ', std::string v = "");

    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;

    char getSuit() const;
    std::string getVal() const;

private:
    char suit;
    std::string val;

    int suitToInt() const;
    int rankToInt() const;
};

#endif