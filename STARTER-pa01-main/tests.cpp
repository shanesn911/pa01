#include <iostream>
#include <vector>
#include <cassert>
#include "card.h"
#include "card_list.h"

using namespace std;

void testCard() {
    cout << "Testing Card comparison..." << endl;
    Card c1('c', "a");
    Card c2('c', "2");
    Card c3('d', "a");
    
    assert(c1 < c2); // Ace < 2
    assert(c2 < c3); // Club < Diamond
    assert(c1 == Card('c', "a"));
    cout << "  - Card tests passed!" << endl;
}

void testBSTBasic() {
    cout << "Testing BST Public Methods..." << endl;
    CardBST tree;
    
    // Case 1: Empty Tree
    assert(tree.contains(Card('s', "5")) == false);
    
    // Case 2: Insertion
    tree.insert(Card('s', "5"));
    assert(tree.contains(Card('s', "5")) == true);
    
    // Case 3: Multiple nodes and ordering
    tree.insert(Card('c', "a"));
    tree.insert(Card('h', "k"));
    
    // Case 4: Removal
    tree.remove(Card('s', "5"));
    assert(tree.contains(Card('s', "5")) == false);
    assert(tree.contains(Card('c', "a")) == true);
    
    cout << "  - BST basic tests passed!" << endl;
}

void testIterator() {
    cout << "Testing Iterator..." << endl;
    CardBST tree;
    tree.insert(Card('d', "5"));
    tree.insert(Card('c', "a"));
    tree.insert(Card('h', "k"));

    // Forward traversal
    auto it = tree.begin();
    assert((*it).getSuit() == 'c'); // Smallest should be Club Ace
    ++it;
    assert((*it).getSuit() == 'd'); // Next is Diamond 5
    ++it;
    assert((*it).getSuit() == 'h'); // Next is Heart King
    ++it;
    assert(it == tree.end()); // Should reach end

    // Backward traversal
    auto rit = tree.rbegin();
    assert((*rit).getSuit() == 'h'); // Largest is Heart King
    --rit;
    assert((*rit).getSuit() == 'd');
    --rit;
    assert((*rit).getSuit() == 'c');

    cout << "  - Iterator tests passed!" << endl;
}

int main() {
    testCard();
    testBSTBasic();
    testIterator();
    
    cout << "\nALL TESTS PASSED!" << endl;
    return 0;
}