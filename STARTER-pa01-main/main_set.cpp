// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"
#include "card_list.h"


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
    cout << "Could not open file" << endl;
    return 1;
  }

  CardBST alice, bob;
  while (getline (cardFile1, line) && (line.length() > 0)){
    alice.insert(Card(line[0], line.substr(2)));
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    bob.insert(Card(line[0], line.substr(2)));
  }
  cardFile2.close();

  playGame(alice, bob);

  cout << endl << "Alice's cards:" << endl;
  alice.printInOrder();
  cout << endl << "Bob's cards:" << endl;
  bob.printInOrder();
  
  return 0;
}