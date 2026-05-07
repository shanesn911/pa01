#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

void playGame(set<Card>& alice, set<Card>& bob) {
    bool anyMatch = true;
    while (anyMatch) {
        anyMatch = false;

        // Alice forward (smallest to largest)
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.count(*it)) {
                cout << "Alice picked matching card " << *it << endl;
                Card matched = *it;
                alice.erase(matched);
                bob.erase(matched);
                anyMatch = true;
                break;
            }
        }

        // Bob reverse (largest to smallest)
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            if (alice.count(*it)) {
                cout << "Bob picked matching card " << *it << endl;
                Card matched = *it;
                alice.erase(matched);
                bob.erase(matched);
                anyMatch = true;
                break;
            }
        }
    }
}

int main(int argv, char** argc) {
    if (argv < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argc[1]);
    ifstream cardFile2(argc[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file" << endl;
        return 1;
    }

    set<Card> alice, bob;

    while (getline(cardFile1, line) && line.length() > 0)
        alice.insert(Card(line[0], line.substr(2)));
    cardFile1.close();

    while (getline(cardFile2, line) && line.length() > 0)
        bob.insert(Card(line[0], line.substr(2)));
    cardFile2.close();

    playGame(alice, bob);

    cout << endl << "Alice's cards:" << endl;
    for (const Card& c : alice) cout << c << endl;
    cout << endl << "Bob's cards:" << endl;
    for (const Card& c : bob) cout << c << endl;

    return 0;
}