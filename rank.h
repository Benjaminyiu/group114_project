#include <string>
#include <iostream>

#ifndef RANK_H
#define RANK_H


struct ranking {
	string name;
	int score;
	string difficulty;
};

void retrieveRecord(vector < struct ranking > &record, int option);

void saveRecord(vector < struct ranking > &record);

#endif
