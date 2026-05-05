#include "card.h"

Card::Card(char s, std::string v) : suit(s), val(v) {}

int Card::suitToInt() const {
    switch (suit) {
        case 'c': return 1;
        case 'd': return 2;
        case 's': return 3;
        case 'h': return 4;
        default:  return 0;
    }
}

int Card::rankToInt() const {
    if (val == "a") return 1;
    if (val == "j") return 11;
    if (val == "q") return 12;
    if (val == "k") return 13;
    try {
        return std::stoi(val);
    } catch (...) {
        return 0;
    }
}

bool Card::operator<(const Card& other) const {
    if (this->suitToInt() != other.suitToInt())
        return this->suitToInt() < other.suitToInt();
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

std::ostream& operator<<(std::ostream& os, const Card& c) {
    os << c.suit << " " << c.val;
    return os;
}