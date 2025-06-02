#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

class Block {
protected:
		int charBlock;
		string policyNum;
		vector<string> data;

public:
	Block(int ID, string policyN, const vector<string>& raw) {
		charBlock = ID;
		policyNum = policyN;
		data = raw;
	}

	int getType() const { return charBlock; }
	string getPolicy() const { return policyNum; }
	vector<string>& getData() { return data; }

	string getDataSum() const {
		string out = "[";
		for (const string& s : data) out += s + ", ";
		return out + "]";
	}

	void setType(const int& type) { charBlock = type; }
	void setPolicy(const string& poly) { policyNum = poly; }
	void setData(const vector<string>& newData) { data = newData; }

};