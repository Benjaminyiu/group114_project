#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "rank.h"

using namespace std;

// input: vector record storing the ranking, rank.txt
// and option (gameplay or display ranking)
// obtain record from rank.txt
// output:
void retrieveRecord(vector < ranking > &record, int option) {
	int i = 0;
	string line;
	ifstream fin ("rank.txt");
	record.resize(0);
	while (i < 10) {
		record.push_back(ranking());
		fin >> record[i].name >> record[i].score >> record[i].difficulty;
		i++;
	}
	if (option == 3) {
		cout << left << setw(20) << "Name" << left << setw(6) << "Score" << "Difficulty" << endl;
		for (int j = 0; j < i; j++)
			cout << left << setw(20) << record[j].name << setw(6) << record[j].score << record[j].difficulty << endl;
	}
	fin.close();
}

// input: vector record storing the ranking
// save record to rank.txt
// output: rank.txt to save ranking permenantly
void saveRecord(vector < ranking > &record) {
	ofstream fout ("rank.txt");
	for (int i = 0; i < 10; i++)
		fout << record[i].name << " " << record[i].score << " " << record[i].difficulty << endl;
	fout.close();
}
