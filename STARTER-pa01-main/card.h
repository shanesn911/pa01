#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {
public:
    Card(char s = ' ', std::string v = "");

    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Card& c);

    char getSuit() const;
    std::string getVal() const;

private:
    char suit;
    std::string val;

    int suitToInt() const;
    int rankToInt() const;
};

#endif