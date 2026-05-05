#include "card.h"
#include <string>
#include <iostream>

Card::Card(char s, std::string v) : suit(s), val(v) {}

int Card::suitToInt() const {
    if (suit == 'c') return 1;
    if (suit == 'd') return 2;
    if (suit == 's') return 3;
    if (suit == 'h') return 4;
    return 0;
}

int Card::rankToInt() const {
    if (val == "a") return 1;
    if (val == "j") return 11;
    if (val == "q") return 12;
    if (val == "k") return 13;
    return std::stoi(val);
}

bool Card::operator<(const Card& other) const {
    if (this->suitToInt() != other.suitToInt()) {
        return this->suitToInt() < other.suitToInt();
    }
    return this->rankToInt() < other.rankToInt();
}

bool Card::operator>(const Card& other) const {
    return other < *this;
}

bool Card::operator==(const Card& other) const {
    return (suit == other.suit && val == other.val);
}

char Card::getSuit() const { return suit; }
std::string Card::getVal() const { return val; }

