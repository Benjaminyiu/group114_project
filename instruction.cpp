#include <iostream>
#include "instruction.h"

using namespace std;

void printInstructions() {
  cout << "Each Minesweeper game starts out with a grid of unmarked squares." << endl;
  cout << "After clicking one of these squares, some of the squares will disappear," << endl;
  cout << "some will remain blank, and some will have numbers on them." << endl;
  cout << "It's your job to use the numbers to figure out which of the blank squares have mines and which are safe to click." << endl << endl;
  cout << "When inputting the coordinates, you must put the row index first and then column index (row index, column index)" << endl;
  cout << "For instance, if user input is 1 1(separated by a space), it means starting from (0,0) moving by row index 1 and column index 1 "<< endl;
}
