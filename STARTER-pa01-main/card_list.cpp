#include "card_list.h"
#include <iostream>

CardBST::CardBST() : root(nullptr) {}

CardBST::~CardBST() {
    clear(root);
}

void CardBST::clear(Node* n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

void CardBST::insert(const Card& c) {
    if (!root) {
        root = new Node(c);
        return;
    }
    Node* curr = root;
    Node* prev = nullptr;
    while (curr) {
        prev = curr;
        if (c < curr->card) curr = curr->left;
        else if (curr->card < c) curr = curr->right;
        else return; 
    }
    Node* newNode = new Node(c);
    newNode->parent = prev;
    if (c < prev->card) prev->left = newNode;
    else prev->right = newNode;
}

void CardBST::remove(const Card& c) {
    Node* curr = root;
    while (curr && !(curr->card == c)) {
        if (c < curr->card) curr = curr->left;
        else curr = curr->right;
    }
    if (!curr) return;

    if (curr->left && curr->right) {
        Node* successor = curr->right;
        while (successor->left) successor = successor->left;
        Card successorCard = successor->card;
        remove(successorCard);
        curr->card = successorCard;
    } else {
        Node* child = curr->left ? curr->left : curr->right;
        if (!curr->parent) root = child;
        else if (curr == curr->parent->left) curr->parent->left = child;
        else curr->parent->right = child;
        if (child) child->parent = curr->parent;
        delete curr;
    }
}

bool CardBST::contains(const Card& c) const {
    Node* curr = root;
    while (curr) {
        if (c == curr->card) return true;
        curr = (c < curr->card) ? curr->left : curr->right;
    }
    return false;
}

void CardBST::printInOrder() const {
    for (Iterator it = begin(); it != end(); ++it) {
        std::cout << (*it).getSuit() << " " << (*it).getVal() << std::endl;
    }
}

CardBST::Iterator& CardBST::Iterator::operator++() {
    if (!curr) return *this;
    if (curr->right) {
        curr = curr->right;
        while (curr->left) curr = curr->left;
    } else {
        Node* p = curr->parent;
        while (p && curr == p->right) {
            curr = p;
            p = p->parent;
        }
        curr = p;
    }
    return *this;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
    if (!curr) return *this;
    if (curr->left) {
        curr = curr->left;
        while (curr->right) curr = curr->right;
    } else {
        Node* p = curr->parent;
        while (p && curr == p->left) {
            curr = p;
            p = p->parent;
        }
        curr = p;
    }
    return *this;
}

CardBST::Iterator CardBST::begin() const {
    Node* n = root;
    if (n) while (n->left) n = n->left;
    return Iterator(n);
}

CardBST::Iterator CardBST::end() const { return Iterator(nullptr); }

CardBST::Iterator CardBST::rbegin() const {
    Node* n = root;
    if (n) while (n->right) n = n->right;
    return Iterator(n);
}

CardBST::Iterator CardBST::rend() const { return Iterator(nullptr); }