#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
using namespace std;

#define BOMB "\xE2\x98\xA0"
#define FLAG "\xE2\x9A\x91"

int bombnum(vector < vector < int > > b, int x, int y) {		// count bombs nearby (not finished)
	int tempx = x;
	int tempy = y;
	int cnt = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			x = tempx;
			y = tempy;

			x += j;
			y += i;
			if (b[y][x] == 0) {
				cnt++;
			}
		}
	}
	return cnt;
}

int numbering(vector < vector < int > > b, int x, int y) {
	int tempx = x;
	int tempy = y;
	int cnt = 0;
	for (int i = -1; i < 2; i++) {

		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			x = tempx;
			y = tempy;

			x += j;
			y += i;
			if (x >= 0 && x < b.size() && y >= 0 && y < b[0].size()) {
				if (b[y][x] == 0){
					cnt++;
				}
			}
		}
	}
	return cnt;


}

void printBoard(vector < vector < int > > b, vector < vector < int > > p_b) {		// print board
	cout << "   ";
	for (int i = 0; i < b.size(); i++)
		cout << left << setw(3) << i;
	cout << endl;
  for (int i = 0; i < b.size(); i++) {
  	cout << left << setw(3) << i;
    for (int j = 0; j < b[i].size(); j++) {
    	if (p_b[i][j] == 1)

				if (b[i][j] == 0) {
					cout << left << setw(3) << BOMB;
				}
				else {
					// print bomb numbers
					int bombnum = numbering(b, j, i);
					cout << left << setw(3) << bombnum;
				}
      else
      	cout << "_  ";
    }
    cout << endl;
  }
}

void scan(vector < vector < int > > b, vector < vector < int > > p_b, int x, int y) {	// scan nearby tiles and reveal if there is no bomb
	int tempx = x;
	int tempy = y;

	for (int i = -1; i < 2; i++) {

		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			x = tempx;
			y = tempy;

			x += j;
			y += i;
			if (x >= 0 && x < b.size() && y >= 0 && y < b[i].size()) {	// setting numbers on tiles
				if (p_b[y][x] != 1 && b[y][x] != 0){
					p_b[y][x] = 1;
					scan(b, p_b, x, y);
				}
				else {
					return;
				}
			}
		}
	}
}

// check winning conditions
// return true if won the game and false if not yet won the game
bool winning(vector < vector < int > > b, vector < vector < int > > p_b) {

	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b[i].size(); j++) {
			if (b[i][j] == 1 && p_b[i][j] != 1) {
				return false;
			}
		}
	}
	return true;

}

void main_page(){
	int option = 1;

	// display main page
	cout << "--------------------Welcome to Minesweeper!--------------------" << endl;
  cout << " ___________________________________ " << endl;
  cout << "|  " << BOMB << "          " << BOMB << "                     |" << endl;
  cout << "|                  " << BOMB << "                |" << endl;
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

		// rank-related
		int score = 0;
		string name;
		time_t t1, t2;
		t1 = time(NULL);

		// random seeds for setting mines in the board
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis1(0, 1);
		uniform_int_distribution<> dis2(1, 2); // limiting mine numbers in a row

		// creating the board, random seeds for setting number of mines
		int size = 9; // board size e.g. 10 means 10x10
		vector < vector < int > > board;
		vector < vector < int > > player_board;
		int minmines = 13;		// setting minimum number of mines
		int mines = rand() % 14 + minmines; // setting number of mines
		ofstream fout("Cheatboard.txt");

		// setting board size according to difficulties
		int difficulty;
		cout << "1. Easy" << endl;
		cout << "2. Medium" << endl;
		cout << "3. Hard" << endl;
		cout << "Please input 1, 2 or 3 to select difficulty: ";
		cin >> difficulty;
		if (difficulty == 1) {
			size = 10;
			board.resize(size);
			player_board.resize(size);
			for (int i = 0; i < size; i++) {
				board[i].resize(size);
				player_board[i].resize(size);
			}
		}
		else if (difficulty == 2) {
			size = 16;
			board.resize(size);
			player_board.resize(size);
			for (int i = 0; i < size; i++) {
				board[i].resize(size);
				player_board[i].resize(size);
			}
		}
		else if (difficulty == 3) {
			size = 20;
			board.resize(size);
			player_board.resize(size);
			for (int i = 0; i < size; i++) {
				board[i].resize(size);
				player_board[i].resize(size);
			}
		}

		// setting mines in the board
		for (int i = 0; i < board.size(); i++) {
			int lim = dis2(gen); // generating random number between 1 and 2
			for (int j = 0; j < board[i].size(); j++) {
				int ran = dis1(gen);	// generating random number between 0 and 1
				if (ran == 1 && mines > 0 && lim > 0) {
					board[i][j] = 0;	// 0 = mine
					fout << 0 << " ";
					mines -= 1;
					lim--;
				}
				else {
					board[i][j] = 1;	// 1 = no mine
					fout << 1 << " ";
				}
			}
			fout << "\n";

		}
		fout.close();

		for (int i = 0; i < board.size(); i++)
			for (int j = 0; j < board[i].size(); j++)
				player_board[i][j] = 0;

		printBoard(board, player_board);



		// gameplay (input)
		int x = 0,	y = 0;

		cout << "your input has to be separated by a space" << endl;
		cout << "Type your input(x,y): ";
		cin >> x >> y;
		while (x > board.size() || x < 0 || y > board[0].size() || y < 0) {
			cout << "Invalid input, try it again: ";
			cin >> x >> y;
		}
		cout << endl;
		while (board[y][x]!= 0) {

			player_board[y][x] = 1;
			scan(board, player_board, x, y);
			if (winning(board,player_board)) {
				cout << "You won! Congratulations!!!" << endl;

				// score display and rank creation (more to be added)
				t2 = time(NULL);
				score = 1000 - (t2 - t1);
				if (score < 10)
					score = 10;
				cout << "Your score is " << score << "!" << endl;
				cout << "Input your nickname to store your record (one word): ";
				cin >> name;

				break;
			};
			printBoard(board, player_board);
			cout << "Type your input(x,y): ";
			cin >> x >> y;
			while (player_board[y][x] == 1) {
				cout << "The chosen tile is opened already, choose another: ";
				cin >> x >> y;
			}
			while (x > board.size() || x < 0 || y > board[0].size() || y < 0) {
				cout << "Invalid input, try it again: ";
				cin >> x >> y;
			}



			cout << endl;

		}

		player_board[y][x] = 1;
		printBoard(board,player_board);

	}

  	else if (option == 2){
    	// display instructions
    	cout << "Each Minesweeper game starts out with a grid of unmarked squares." << endl;
  		cout << "After clicking one of these squares, some of the squares will disappear," << endl;
      cout << "some will remain blank, and some will have numbers on them." << endl;
			cout << "It's your job to use the numbers to figure out which of the blank squares have mines and which are safe to click." << endl << endl;
			cout << "When inputting the coordinates, you must put the row index first and then column index (row index, column index)" << endl;
			cout << "For instance, if user input is 1 1(separated by a space), it means starting from (0,0) moving by row index 1 and column index 1 "<< endl;
  	}

		else if (option == 3) {
    	// load ranking from rank.txt
  	}
}

int main(){

  main_page();

	cout << endl << "Bye!" << endl;

	return 0;
}
