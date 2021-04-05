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
const int size_hard = 20;


int bombnum(int **b, int x, int y) {		// count bombs nearby (not finished)
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

void printBoard(int **b, int **p_b, int size) {		// print board
    cout << "   ";
	for (int i = 0; i < size; i++) {
		cout << left << setw(3) << i;
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << left << setw(3) << i;
		for (int j = 0; j < size; j++) {
			if (p_b[i][j] == 1)
				
				if (b[i][j] == 0) {
					cout << left << setw(3) << BOMB << " ";
				}
				else {
							// print bomb numbers
					int bombnum = numbering(b, j, i, size);
					cout << left << setw(3) << bombnum;
				}
			else
				cout << "_  ";
		}
		cout << endl;
	}
}

void scan(int **b, int **p_b, int x, int y, int size) {	// scan nearby tiles and reveal if there is no bomb
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


bool winning(int **b, int **p_b, int size) {	// check winning conditions
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
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

			int size; // board size e.g. 10 means 10x10
			int difficulty = 0;
			// setting difficulty
			cout << "1. Easy" << endl;
			cout << "2. Medium" << endl;
			cout << "3. Hard" << endl;
			cout << "Please input 1, 2 or 3 to select difficulty: ";
			cin >> difficulty;
			
			while(difficulty > 3 || difficulty < 1 || cin.fail())  {
				cin.clear();
				cin.ignore(INT_MAX, '\n'); // ignore last input
				cout << "Invalid input, please input 1, 2 or 3: ";
				cin >> difficulty;
			}
			int minmines = 13;



			
			int min, max; // setting minimum and maximum number of mines in each row
			switch(difficulty) {
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
			for(int i = 0; i < size; ++i) {
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
        
        printBoard(board, player_board, size);






		// gameplay (input)
		int x = 0,	y = 0;
		cout << "your input has to be separated by a space" << endl;
		cout << "Type your input(x,y): ";
		cin >> x >> y;
		while (x > size || x < 0 || y > size || y < 0) {
			cout << "Invalid input, try it again: ";
			cin >> x >> y;
		}
		cout << endl;
		while (board[y][x]!= 0) {
			
			player_board[y][x] = 1;
			scan(board, player_board, x, y, size);
			if (winning(board,player_board, size)) {
				cout << "You won! Congratulations!!!" << endl;
				break;
			};
			printBoard(board, player_board, size);
			cout << "Type your input(x,y): ";
			cin >> x >> y;
			while (player_board[y][x] == 1) {
				cout << "The chosen tile is opened already, choose another: ";
				cin >> x >> y;
			}
			while (x > size || x < 0 || y > size || y < 0) {
				cout << "Invalid input, try it again: ";
				cin >> x >> y;
			}

			
			
			cout << endl;
			
		}
		player_board[y][x] = 1;
		printBoard(board, player_board, size);
		delete[] board;	
		delete[] player_board;
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
  	else if (option == 3){
    	// load ranking from rank.txt
  	}
}

int main(){

  main_page();

	cout << endl << "Bye!" << endl;

	return 0;
}
