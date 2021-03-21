#include <iostream>
using namespace std;

#define BOMB "\xF0\x9F\x92\xA3"
#define BLANK
void main_page(){
  int option = 1;

  cout << "--------------------Welcome to Minesweeper!--------------------" << endl;
  cout << " ___________________________________ " << endl;
  cout << "|  " << BOMB << "          " << BOMB << "                   |" << endl;
  cout << "|                  " << BOMB << "               |" << endl;
  cout << endl;
  cout << "1. Play Game" << endl;
  cout << "2. Instructions" << endl;
  cout << "3. View Top 10 Players" << endl;
  cout << "4. Exit Game" << endl << endl;

  cout << "Input 1-4 to continue: ";
  cin >> option;

  if (option == 1){
    // init game
  }
  else if (option == 2){
    // display instructions
  }
  else if (option == 3){
    // load ranking from rank.txt
  }
}

int main(){

  main_page();

  cout << endl << "Bye!" << endl;

  return 0;
}
