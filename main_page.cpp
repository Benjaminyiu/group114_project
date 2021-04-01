#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
using namespace std;

#define BOMB "\xF0\x9F\x92\xA3"
#define BLANK
const int size_easy = 10;
const int size_medium = 16;
const int size_hard_height = 20;
const int size_hard_width = 24;

int bombnum(int b[][size_easy], int x, int y) {		// count bombs nearby (not finished)
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
void printBoard(int b[][size_easy], int p_b[][size_easy]) {
    cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
        for (int i = 0; i < size_easy; i++) {
            cout << i << " ";
            for (int j = 0; j < size_easy; j++) {
                if (p_b[i][j] == 1)
                    
					if (b[i][j] == 0) {
						cout << BOMB << " ";
					}
					else {
								// print bomb numbers
						cout << b[i][j] << " ";
					}
                else
                    cout << "_ ";
            }
            cout << endl;
        }
}

void scan(int b[][size_easy], int p_b[][size_easy], int x, int y) {	// scan nearby tiles and reveal if there is no bomb
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
			if (x >= 0 && x < size_easy && y >= 0 && y < size_easy) {
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

bool winning(int b[][size_easy], int p_b[][size_easy]) {	// check winning conditions
	
	for (int i = 0; i < size_easy; i++) {
		for (int j = 0; j < size_easy; j++) {
			if (b[i][j] == 1 && p_b[i][j] != 1) {
				return false;
			}
		}
	}
	return true;

}

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

			int difficulty = size_easy;

		    // random seeds for setting mines in the board
		    random_device rd;
		    mt19937 gen(rd());
		    uniform_int_distribution<> dis1(0, 1);
		    uniform_int_distribution<> dis2(1, 2); // limiting mine numbers in a row

		    // creating the board, random seeds for setting number of mines
		    int size = 9; // board size e.g. 10 means 10x10
		    int board[size_easy][size_easy];
        	int player_board[size_easy][size_easy];
		    int minmines = 13;	// setting minimum number of mines
		    int mines = rand() % 14 + minmines; // setting number of mines
		    ofstream fout("Cheatboard.txt");


		    // setting mines in the board
		    for (int i = 0; i < size_easy; i++) {
			      int lim = dis2(gen); // generating random number between 1 and 2
			      for (int j = 0; j < size_easy; j++) {
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

        for (int i = 0; i < size_easy; i++)
          	for (int j = 0; j < size_easy; j++)
            	player_board[i][j] = 0;
        
        printBoard(board, player_board);






		// gameplay (input)
		int x = 0,	y = 0;
		cout << "your input has to be separated by a space" << endl;
		cout << "Type your input(x,y): ";
		cin >> x >> y;
		while (x > size_easy || x < 0 || y > size_easy || y < 0) {
			cout << "Invalid input, try it again: ";
			cin >> x >> y;
		}
		cout << endl;
		while (board[y][x]!= 0) {
			
			player_board[y][x] = 1;
			scan(board, player_board, x, y);
			if (winning(board,player_board)) {
				cout << "You won! Congratulations!!!" << endl;
				break;
			};
			printBoard(board, player_board);
			cout << "Type your input(x,y): ";
			cin >> x >> y;
			while (player_board[y][x] == 1) {
				cout << "The chosen tile is opened already, choose another: ";
				cin >> x >> y;
			}
			while (x > size_easy || x < 0 || y > size_easy || y < 0) {
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
