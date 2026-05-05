// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

//Do not include set in this file

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
  CardBST alice_hand;
  CardBST bob_hand;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    char suit = line[0];
    string val = line.substr(2);
    if (!val.empty() && val[val.size() - 1] == '/r') {
      val.erase(val.size() - 1);
    }
    alice_hand.insert(Card(suit, val));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    char suit = line[0];
    string val = line.substr(2);
    if (!val.empty() && val[val.size() - 1] == '/r') {
      val.erase(val.size() - 1);
    }
    bob_hand.insert(Card(suit, val));
  }
  cardFile2.close();
  
  playGame(alice_hand, bob_hand);
  cout << endl << "Alice's cards:" << endl;
  alice_hand.printInOrder();

  cout << endl << "Bob's cards:" << endl;
  bob_hand.printInOrder();
  
  return 0;
}
