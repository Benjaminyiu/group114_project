#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

#define BOMB "\xF0\x9F\x92\xA3"
#define BLANK
const int size_easy = 10;
const int size_medium = 16;
const int size_hard_height = 20;
const int size_hard_width = 24;
const int bomb_easy = 10;
const int bomb_medium = 40;
const int bomb_hard = 99;

void main_page(){
    int option = 1;

  	cout << "--------------------Welcome to Minesweeper!--------------------" << endl;
  	cout << " ___________________________________ " << endl;
  	cout << "|  " << BOMB << "          " << BOMB << "                   |" << endl;
  	cout << "|                  " << BOMB << "               |" << endl;
    cout << " ___________________________________ " << endl;
    cout << endl;
  	cout << "1. Play Game" << endl;
  	cout << "2. Instructions" << endl;
  	cout << "3. View Top 10 Players" << endl;
  	cout << "4. Exit Game" << endl << endl;

  	cout << "Input 1-4 to continue: ";
  	cin >> option;

  	if (option == 1){
		// init game
		cout << "\n";
		srand((unsigned) time(0));

		// random seeds for setting mines in the board
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis1(0, 1);
		uniform_int_distribution<> dis2(1, 2); // limiting mine numbers in a row

		// creating the board, random seeds for setting number of mines
		int size = 9; // board size e.g. 10 means 10x10
		int board[size][size];
		int mines = rand() % 14 + 1;

		// setting mines in the board
		for (int i = 0; i < size; i++) {
			int lim = dis2(gen); // generating random number between 1 and 2
			for (int j = 0; j < size; j++) {
				int ran = dis1(gen);	// generating random number between 0 and 1
				if (ran == 1 && mines > 0 and lim > 0) {
					board[i][j] = 0;	// 0 = mine
					cout << board[i][j] << " ";
					mines -= 1;
					lim--;
				}
				else {
					board[i][j] = 1;	// 1 = no mine
					cout << board[i][j] << " ";
				}
			}
			cout << "\n";
		}
  	}

  	else if (option == 2){
    	// display instructions
    	cout << "Each Minesweeper game starts out with a grid of unmarked squares." << endl;
      cout << "After clicking one of these squares, some of the squares will disappear," << endl;
      cout << "some will remain blank, and some will have numbers on them." << endl;
      cout << "It's your job to use the numbers to figure out which of the blank squares have mines and which are safe to click." << endl << endl;
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
