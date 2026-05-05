#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

class CardBST {
public:
    struct Node {
        Card card;
        Node *left, *right, *parent;
        Node(Card c) : card(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    class Iterator {
    public:
        Iterator(Node* n = nullptr) : curr(n) {}
        const Card& operator*() const { return curr->card; }
        Iterator& operator++(); // Successor
        Iterator& operator--(); // Predecessor
        bool operator==(const Iterator& other) const { return curr == other.curr; }
        bool operator!=(const Iterator& other) const { return curr != other.curr; }
    private:
        Node* curr;
    };

    CardBST();
    ~CardBST();
    void insert(const Card& c);
    void remove(const Card& c);
    bool contains(const Card& c) const;
    void printInOrder() const;

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;

private:
    Node* root;
    void clear(Node* n);
};

void playGame(CardBST& alice, CardBST& bob);

#endif