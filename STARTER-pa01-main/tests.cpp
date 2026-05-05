#include <iostream>
#include <cassert>
#include "card.h"
#include "card_list.h"

using namespace std;

// ─── Helpers ─────────────────────────────────────────────────────────────────
void pass(const string& name) { cout << "[PASS] " << name << endl; }

// ─── Card ordering tests ──────────────────────────────────────────────────────
void test_card_ordering() {
    Card ca('c', "a"), ck('c', "k"), d3('d', "3"), s3('s', "3"), h9('h', "9"), hj('h', "j");

    assert(ca < ck);   pass("clubs ace < clubs king");
    assert(ck < d3);   pass("clubs king < diamonds 3");
    assert(d3 < s3);   pass("diamonds 3 < spades 3");
    assert(s3 < h9);   pass("spades 3 < hearts 9");
    assert(h9 < hj);   pass("hearts 9 < hearts jack");
    assert(!(hj < ca)); pass("hearts jack not < clubs ace");
    assert(ca == Card('c',"a")); pass("card equality");
}

// ─── BST insert / contains ────────────────────────────────────────────────────
void test_insert_contains() {
    CardBST bst;

    // empty tree
    assert(!bst.contains(Card('c',"a"))); pass("empty tree: contains false");

    // single node
    bst.insert(Card('c',"a"));
    assert(bst.contains(Card('c',"a"))); pass("single node: contains true");

    // multiple nodes
    bst.insert(Card('h',"k"));
    bst.insert(Card('d',"5"));
    assert(bst.contains(Card('h',"k"))); pass("multi: contains h k");
    assert(bst.contains(Card('d',"5"))); pass("multi: contains d 5");
    assert(!bst.contains(Card('s',"2"))); pass("multi: missing card false");

    // duplicate insert – size should not change (no crash)
    bst.insert(Card('c',"a"));
    assert(bst.contains(Card('c',"a"))); pass("duplicate insert: no crash");
}

// ─── BST remove ───────────────────────────────────────────────────────────────
void test_remove() {
    CardBST bst;

    // remove from empty – no crash
    bst.remove(Card('c',"a")); pass("remove from empty: no crash");

    // remove only node
    bst.insert(Card('c',"a"));
    bst.remove(Card('c',"a"));
    assert(!bst.contains(Card('c',"a"))); pass("remove only node");

    // remove non-existent
    bst.insert(Card('h',"3"));
    bst.remove(Card('d',"9"));
    assert(bst.contains(Card('h',"3"))); pass("remove non-existent: tree intact");

    // remove leaf
    bst.insert(Card('c',"2"));
    bst.remove(Card('c',"2"));
    assert(!bst.contains(Card('c',"2"))); pass("remove leaf");

    // remove node with two children
    CardBST bst2;
    bst2.insert(Card('d',"5"));
    bst2.insert(Card('c',"3"));
    bst2.insert(Card('h',"9"));
    bst2.remove(Card('d',"5"));
    assert(!bst2.contains(Card('d',"5"))); pass("remove two-child node: gone");
    assert(bst2.contains(Card('c',"3")));  pass("remove two-child node: left child remains");
    assert(bst2.contains(Card('h',"9")));  pass("remove two-child node: right child remains");
}

// ─── Iterator forward ─────────────────────────────────────────────────────────
void test_iterator_forward() {
    CardBST bst;

    // empty tree
    assert(bst.begin() == bst.end()); pass("empty: begin==end");

    // single node
    bst.insert(Card('c',"5"));
    auto it = bst.begin();
    assert(*it == Card('c',"5")); pass("single: begin deref correct");
    ++it;
    assert(it == bst.end()); pass("single: ++begin == end");

    // multiple nodes – check inorder sequence
    CardBST bst2;
    bst2.insert(Card('h',"9"));
    bst2.insert(Card('c',"a"));
    bst2.insert(Card('d',"3"));

    Card expected[] = { Card('c',"a"), Card('d',"3"), Card('h',"9") };
    int i = 0;
    for (auto it2 = bst2.begin(); it2 != bst2.end(); ++it2, ++i)
        assert(*it2 == expected[i]);
    pass("forward inorder sequence correct");
}

// ─── Iterator reverse ─────────────────────────────────────────────────────────
void test_iterator_reverse() {
    CardBST bst;

    // empty tree
    assert(bst.rbegin() == bst.rend()); pass("empty: rbegin==rend");

    // single node
    bst.insert(Card('s',"7"));
    auto it = bst.rbegin();
    assert(*it == Card('s',"7")); pass("single: rbegin deref correct");
    --it;
    assert(it == bst.rend()); pass("single: --rbegin == rend");

    // multiple nodes – check reverse order
    CardBST bst2;
    bst2.insert(Card('h',"9"));
    bst2.insert(Card('c',"a"));
    bst2.insert(Card('d',"3"));

    Card expected[] = { Card('h',"9"), Card('d',"3"), Card('c',"a") };
    int i = 0;
    for (auto it2 = bst2.rbegin(); it2 != bst2.rend(); --it2, ++i)
        assert(*it2 == expected[i]);
    pass("reverse inorder sequence correct");
}

// ─── playGame tests ───────────────────────────────────────────────────────────
void test_play_game_common_cards() {
    CardBST alice, bob;
    // shared: c 3, h 10
    alice.insert(Card('c',"a")); alice.insert(Card('c',"3")); alice.insert(Card('h',"10"));
    bob.insert(Card('c',"3")); bob.insert(Card('h',"10")); bob.insert(Card('d',"j"));

    cout << "--- playGame with common cards ---" << endl;
    playGame(alice, bob);
    assert(!alice.contains(Card('c',"3")));  pass("playGame: c 3 removed from alice");
    assert(!bob.contains(Card('c',"3")));    pass("playGame: c 3 removed from bob");
    assert(!alice.contains(Card('h',"10"))); pass("playGame: h 10 removed from alice");
    assert(!bob.contains(Card('h',"10")));   pass("playGame: h 10 removed from bob");
    assert(alice.contains(Card('c',"a")));   pass("playGame: alice's unique card remains");
    assert(bob.contains(Card('d',"j")));     pass("playGame: bob's unique card remains");
}

void test_play_game_no_common_cards() {
    CardBST alice, bob;
    alice.insert(Card('c',"a"));
    bob.insert(Card('h',"k"));

    cout << "--- playGame with no common cards ---" << endl;
    playGame(alice, bob);
    assert(alice.contains(Card('c',"a"))); pass("no common: alice hand unchanged");
    assert(bob.contains(Card('h',"k")));   pass("no common: bob hand unchanged");
}

void test_play_game_one_empty() {
    CardBST alice, bob;
    alice.insert(Card('d',"5"));
    // bob is empty

    cout << "--- playGame with one empty hand ---" << endl;
    playGame(alice, bob);
    assert(alice.contains(Card('d',"5"))); pass("one empty: alice hand unchanged");
}

// ─── main ─────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== Card ordering ===" << endl;
    test_card_ordering();

    cout << "\n=== BST insert/contains ===" << endl;
    test_insert_contains();

    cout << "\n=== BST remove ===" << endl;
    test_remove();

    cout << "\n=== Iterator forward ===" << endl;
    test_iterator_forward();

    cout << "\n=== Iterator reverse ===" << endl;
    test_iterator_reverse();

    cout << "\n=== playGame ===" << endl;
    test_play_game_common_cards();
    test_play_game_no_common_cards();
    test_play_game_one_empty();

    cout << "\nAll tests passed!" << endl;
    return 0;
}