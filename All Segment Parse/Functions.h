#pragma once
#include "Block.h"

void readFile(int i, string& path, ifstream& inFile);

bool printFile(int i, string& path, vector<Block*>& blocks);

void printKey(int i,string& path, vector<string>& fileNs);

inline string getFolderPath(const string& path) {
	size_t lastSlash = path.find_last_of("\\/");
	if (lastSlash == string::npos) return "";
	return path.substr(0, lastSlash + 1);
}

