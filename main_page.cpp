#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <fstream>
#include <vector>
#include "instruction.h"
#include "rank.h"

using namespace std;

#define BOMB "\xE2\x98\xA0"
#define FLAG "\xE2\x9A\x91"
const int size_easy = 10;
const int size_medium = 16;
const int size_hard = 20;
const int highest_score = 2000;

// input: computer's board, coordinates and size of board
// assign numbers to each grid according the number of mines in 3X3 neighbouring
// output: numbers of each grid without bomb
int numbering(int **b, int x, int y, int size) {
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
			if (x >= 0 && x < size && y >= 0 && y < size) {
				if (b[y][x] == 0){
					cnt++;
				}
			}
		}
	}
	return cnt;
}

// input: computer's and player's boards, vector of flag, size of board
// output: player's board
void printBoard(int **b, int **p_b, vector < vector <int> > &flag, int size) {
	cout << "   ";											// first line formatting
	for (int i = 0; i < size; i++) {
		cout << left << setw(3) << i;
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << left << setw(3) << i;
		for (int j = 0; j < size; j++) {
			if (p_b[i][j] == 1)							// the grid is chosen

				if (b[i][j] == 0) {
					if (flag[i][j] == 1)				// print a flag
						cout << left << setw(3) << FLAG << "  ";
					else												// print a bomb
						cout << left << setw(3) << BOMB << "  ";
				}
				else {												// print bomb numbers
					int bombnum = numbering(b, j, i, size);
					cout << left << setw(3) << bombnum;
				}
			else														// the grid is not chosen
				cout << "_  ";
		}
		cout << endl;
	}
}

// input: computer's and player's boards, coordinates, size of board
// output: scan nearby tiles and reveal if there is no bomb
void scan(int **b, int **p_b, int x, int y, int size) {
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
			if (x >= 0 && x < size && y >= 0 && y < size) {	// setting numbers on tiles
				if (p_b[y][x] != 1 && b[y][x] == 0){
					return;
				}
			}
		}
	}
	for (int i = -1; i < 2; i++) {

		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			x = tempx;
			y = tempy;

			x += j;
			y += i;
			if (x >= 0 && x < size && y >= 0 && y < size) {	// setting numbers on tiles
				if (p_b[y][x] != 1){
					p_b[y][x] = 1;
					scan(b, p_b, x, y, size);
				}
			}
		}
	}
}

// input: computer's and player's boards, size of board
// check winning conditions
// output: true if all non-mine grids are chosen, false otherwise
bool winning(int **b, int **p_b, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (b[i][j] == 1 && p_b[i][j] != 1) {	// computer's grid has no mine
																						// and player has not chosen this grid
				return false;
			}
		}
	}
	return true;
}

void main_page(){
	int option = 1;
	vector < ranking > record; // for saving record
  cout << "--------------------Welcome to Minesweeper!--------------------" << endl;
	cout << " ___________________________________ " << endl;
  cout << "|  " << BOMB << "          " << BOMB << "                    |" << endl;
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

		int size; // board size e.g. 10 means 10x10
		int difficulty = 0;

		// setting difficulty
		cout << "1. Easy" << endl;
		cout << "2. Medium" << endl;
		cout << "3. Hard" << endl;
		cout << "Please input 1, 2 or 3 to select difficulty: ";
		cin >> difficulty;

		while(difficulty > 3 || difficulty < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(INT8_MAX, '\n'); // ignore last input
			cout << "Invalid input, please input 1, 2 or 3: ";
			cin >> difficulty;
		}

		int minmines = 13;
		int min, max; // setting minimum and maximum number of mines in each row
		switch (difficulty) {
			case 1:
				size = size_easy;
				minmines = 13;	// setting minimum number of mines
				min = 1;
				max = 2;
				break;
			case 2:
				size = size_medium;
				minmines = 64;	// setting minimum number of mines
				min = 3;
				max = 6;
				break;
			case 3:
				size = size_hard;
				minmines = 190;	// setting minimum number of mines
				min = 9;
				max = 18;
				break;
		}

		int mines = rand() % 14 + minmines; // setting number of mines

		int** board = new int*[size];	// using dynamic 2d array to store mines
		int** player_board = new int*[size];
		for (int i = 0; i < size; ++i) {
    	board[i] = new int[size];
			player_board[i] = new int[size];
		}

		// random seeds for setting mines in the board
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis1(1, 2);
		uniform_int_distribution<> dis2(min, max); // limiting mine numbers in a row

		// creating the board, random seeds for setting number of mines

		ofstream fout("Cheatboard.txt");

		// setting mines in the board
		for (int i = 0; i < size; i++) {
			int lim = dis2(gen); // generating random number between 1 and 2
			for (int j = 0; j < size; j++) {
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

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				player_board[i][j] = 0;

		vector < vector <int> > flag;		// 2d vector to indicate if
		for (int i = 0; i < size; i++){	// a flag was placed
			vector <int> temp (size, 0);
			flag.push_back(temp);
		}

		printBoard(board, player_board, flag, size);

		// gameplay (input)
		int x = 0, y = 0, win = 0;
		time_t t1 = time(NULL);	// define initial time before gameplay
		cout << "Your input has to be separated by a space" << endl;
		cout << "Type your input(x,y): ";
		cin >> x >> y;
		while (x >= size || x < 0 || y >= size || y < 0) {
			cout << "Invalid input, try it again: ";
			cin >> x >> y;
		}
		cout << endl;
		srand(time(NULL));
		while (board[y][x]!= 0 && !win) {
			int revealOneMine = rand() % 5;	// probability of having special events
			if (revealOneMine == 0) {					// to reveal one mine = 1/5
				int draw = rand() % 10;					// count the nth bomb location to be revealed
				int count = 0, i = 0, j = 0;
				for (i = 0; i < size && count < draw; ++i)
					for (j = 0; j < size && count < draw; ++j)
						if (board[i][j] == 0) {
							++count;
							if (count == draw) {
								i--;
								j--;
							}
						}

				player_board[i][j] = 1;
				flag[i][j] = 1;
				cout << "Lucky! The grid (" << j << " " << i << ") has been revealed for you!" << endl;

			}
			cout << endl;
			player_board[y][x] = 1;
			scan(board, player_board, x, y, size);
			if (winning(board, player_board, size)) {
				time_t t2 = time(NULL); // define time after winning game
				int score = highest_score - (t2 - t1);	// formula for score
				if (score < 10)	// minimum score = 10
					score = 10;
				string name;
				player_board[y][x] = 1;
				printBoard(board, player_board, flag, size);
				cout << "You won! Congratulations!!!" << endl;
				cout << "Your score is " << score << "." << endl;
				cout << "Please input your name to save your record: ";
				cin >> name;
				cout << "Thanks for playing!" << endl;
				string diff;
				if (difficulty == 1)
					diff = "Easy";
				else if (difficulty == 2)
					diff = "Medium";
				else if (difficulty == 3)
					diff = "Hard";
				ranking new_record = {name, score, diff}; // create a new record
														// to be stored in record vector
				retrieveRecord(record, option);
				for (int i = 0; i < 10; i++)
					if (score > record[i].score) {	// insert record in descending order of score
						record.insert(record.begin() + i, new_record);
						break;
					}
				saveRecord(record);
				win = 1;
				break;
			};
			printBoard(board, player_board, flag, size);
			cout << "Type your input(x,y): ";
			cin >> x >> y;
			while (player_board[y][x] == 1) {
				cout << "The chosen tile is opened already, choose another: ";
				cin >> x >> y;
			}
			while (x >= size || x < 0 || y >= size || y < 0) {
				cout << "Invalid input, try it again: ";
				cin >> x >> y;
			}

			cout << endl;

		}

		if (!win) {
			player_board[y][x] = 1;
			printBoard(board, player_board, flag, size);
			cout << "You lose!" << endl;
		}

		delete[] board;
		delete[] player_board;
	}

	else if (option == 2){
    // display instructions
		printInstructions();
  }

	else if (option == 3){
		// load rank info from rank.txt
		retrieveRecord(record, option);
	}
}

int main(){

	main_page();

	cout << endl << "Bye!" << endl;

	return 0;
}
