#include <iostream>
#include <cassert>
#include <sstream>
#include "card.h"
#include "card_list.h"

using namespace std;

void pass(const string& name) { cout << "[PASS] " << name << endl; }

void test_card_ordering() {
    Card ca('c', "a"), ck('c', "k"), d3('d', "3"), s3('s', "3"), h9('h', "9"), hj('h', "j");

    assert(ca < ck);    pass("clubs ace < clubs king");
    assert(ck < d3);    pass("clubs king < diamonds 3");
    assert(d3 < s3);    pass("diamonds 3 < spades 3");
    assert(s3 < h9);    pass("spades 3 < hearts 9");
    assert(h9 < hj);    pass("hearts 9 < hearts jack");
    assert(!(hj < ca)); pass("hearts jack not < clubs ace");
    assert(ca == Card('c',"a")); pass("card equality");
}

void test_insert_contains() {
    CardBST bst;

    assert(!bst.contains(Card('c',"a"))); pass("empty tree: contains false");

    bst.insert(Card('c',"a"));
    assert(bst.contains(Card('c',"a"))); pass("single node: contains true");

    bst.insert(Card('h',"k"));
    bst.insert(Card('d',"5"));
    assert(bst.contains(Card('h',"k"))); pass("multi: contains h k");
    assert(bst.contains(Card('d',"5"))); pass("multi: contains d 5");
    assert(!bst.contains(Card('s',"2"))); pass("multi: missing card false");

    bst.insert(Card('c',"a"));
    assert(bst.contains(Card('c',"a"))); pass("duplicate insert: no crash");
}

void test_remove() {
    CardBST bst;

    bst.remove(Card('c',"a")); pass("remove from empty: no crash");

    bst.insert(Card('c',"a"));
    bst.remove(Card('c',"a"));
    assert(!bst.contains(Card('c',"a"))); pass("remove only node");

    bst.insert(Card('h',"3"));
    bst.remove(Card('d',"9"));
    assert(bst.contains(Card('h',"3"))); pass("remove non-existent: tree intact");

    bst.insert(Card('c',"2"));
    bst.remove(Card('c',"2"));
    assert(!bst.contains(Card('c',"2"))); pass("remove leaf");

    CardBST bst2;
    bst2.insert(Card('d',"5"));
    bst2.insert(Card('c',"3"));
    bst2.insert(Card('h',"9"));
    bst2.remove(Card('d',"5"));
    assert(!bst2.contains(Card('d',"5"))); pass("remove two-child node: gone");
    assert(bst2.contains(Card('c',"3")));  pass("remove two-child node: left child remains");
    assert(bst2.contains(Card('h',"9")));  pass("remove two-child node: right child remains");
}

void test_print_in_order() {
    // empty tree - no output, no crash
    CardBST bst;
    streambuf* orig = cout.rdbuf();
    ostringstream oss;
    cout.rdbuf(oss.rdbuf());
    bst.printInOrder();
    cout.rdbuf(orig);
    assert(oss.str() == ""); pass("printInOrder empty: no output");

    // single node
    bst.insert(Card('c',"a"));
    oss.str("");
    cout.rdbuf(oss.rdbuf());
    bst.printInOrder();
    cout.rdbuf(orig);
    assert(oss.str() == "c a\n"); pass("printInOrder single node");

    // multiple nodes in order
    CardBST bst2;
    bst2.insert(Card('h',"9"));
    bst2.insert(Card('c',"a"));
    bst2.insert(Card('d',"3"));
    oss.str("");
    cout.rdbuf(oss.rdbuf());
    bst2.printInOrder();
    cout.rdbuf(orig);
    assert(oss.str() == "c a\nd 3\nh 9\n"); pass("printInOrder multiple nodes correct order");

    // after removal
    bst2.remove(Card('d',"3"));
    oss.str("");
    cout.rdbuf(oss.rdbuf());
    bst2.printInOrder();
    cout.rdbuf(orig);
    assert(oss.str() == "c a\nh 9\n"); pass("printInOrder after removal");

    CardBST bst3;
    bst3.insert(Card('s',"10"));
    bst3.insert(Card('s',"9"));
    oss.str("");
    cout.rdbuf(oss.rdbuf());
    bst3.printInOrder();
    cout.rdbuf(orig);
    assert(oss.str() == "s 9\ns 10\n"); pass("printInOrder 10 ordered correctly");
}

void test_iterator_forward() {
    CardBST bst;

    assert(bst.begin() == bst.end()); pass("empty: begin==end");

    bst.insert(Card('c',"5"));
    auto it = bst.begin();
    assert(*it == Card('c',"5")); pass("single: begin deref correct");
    ++it;
    assert(it == bst.end()); pass("single: ++begin == end");

    CardBST bst2;
    bst2.insert(Card('h',"9"));
    bst2.insert(Card('c',"a"));
    bst2.insert(Card('d',"3"));

    Card expected[] = { Card('c',"a"), Card('d',"3"), Card('h',"9") };
    int i = 0;
    for (auto it2 = bst2.begin(); it2 != bst2.end(); ++it2, ++i)
        assert(*it2 == expected[i]);
    pass("forward inorder sequence correct");

    // iterator != check
    auto it3 = bst2.begin();
    auto it4 = bst2.end();
    assert(it3 != it4); pass("iterator != works");
}

void test_iterator_reverse() {
    CardBST bst;

    assert(bst.rbegin() == bst.rend()); pass("empty: rbegin==rend");

    bst.insert(Card('s',"7"));
    auto it = bst.rbegin();
    assert(*it == Card('s',"7")); pass("single: rbegin deref correct");
    --it;
    assert(it == bst.rend()); pass("single: --rbegin == rend");

    CardBST bst2;
    bst2.insert(Card('h',"9"));
    bst2.insert(Card('c',"a"));
    bst2.insert(Card('d',"3"));

    Card expected[] = { Card('h',"9"), Card('d',"3"), Card('c',"a") };
    int i = 0;
    for (auto it2 = bst2.rbegin(); it2 != bst2.rend(); --it2, ++i)
        assert(*it2 == expected[i]);
    pass("reverse inorder sequence correct");

    // iterator == check
    auto it3 = bst2.rbegin();
    auto it4 = bst2.rbegin();
    assert(it3 == it4); pass("iterator == works");
}

void test_play_game_common_cards() {
    CardBST alice, bob;
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

    cout << "--- playGame with one empty hand ---" << endl;
    playGame(alice, bob);
    assert(alice.contains(Card('d',"5"))); pass("one empty: alice hand unchanged");
}

int main() {
    cout << "=== Card ordering ===" << endl;
    test_card_ordering();

    cout << "\n=== BST insert/contains ===" << endl;
    test_insert_contains();

    cout << "\n=== BST remove ===" << endl;
    test_remove();

    cout << "\n=== BST printInOrder ===" << endl;
    test_print_in_order();

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