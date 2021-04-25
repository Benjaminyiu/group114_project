#ifndef RANK_H
#define RANK_H

#include <string>
#include <iostream>

using namespace std;

struct ranking {
	string name;
	int score;
	string difficulty;
};

void retrieveRecord(vector < ranking > &record, int option);

void saveRecord(vector < ranking > &record);

#endif
