#include "Functions.h"

bool printFile(int i, string& path, vector<Block*>& blocks) {
	cout << "Printing Output File...\n\n";

	string outN = path + "Output_File_" + to_string(i) + ".csv";
	ofstream out(outN);

	if (!out.good()) { return false; }

	for (Block* block : blocks) {
		vector<string> tokens = block->getData();
		if (tokens.empty()) continue;

		vector<string> outputRow;
		outputRow.push_back(block->getPolicy());

		if (tokens[0] == "0" && (tokens.size() < 2 || tokens[1] != "AUX")) {
			tokens.insert(tokens.begin() + 1, "");
		}

		for (size_t j = 0; j < tokens.size(); ++j) {
			outputRow.push_back(tokens[j]);
		}

		for (size_t j = 0; j < outputRow.size(); ++j) {
			out << "'" << outputRow[j];
			if (j != outputRow.size() - 1) out << ",";
		}
		out << "\n";
	}

	out.close();
	cout << "Printing Complete...\nFile Name: " << outN << "\n\n";
	return true;
}

void printKey(int i,string& path, vector<string>& fileNs) {
	cout << "Printing File Key...\n\n";
	string keyN = path + "Output_User_Key.txt";
	ofstream key(keyN);

	if (!key.good()) { cout << "ERROR - Key File No Good:" << keyN; }

	key << left << setw(15) << "File Index"
		<< setw(30) << "Input File"
		<< setw(30) << "Output File"
		<< setw(80) << "Input File Path"
		<< setw(80) << "Output File Path" << endl;
	key << left << setw(1) << string(231, '-') << endl;

	for (int k = 0; k < fileNs.size(); k++) {
		string tempN = fileNs[k];
		if (tempN.find(path) == 0) { 
			fileNs[k] = tempN.substr(path.length());
		}
	}

	for (int j = 0; j < i-1 ; j++) {
		key << left << setw(15) << j+1
			<< setw(30) << fileNs[j]
			<< setw(30) << "Output_File_" + to_string(j+1) + ".csv"
			<< setw(80) << path + fileNs[j]
			<< setw(80) << path + "Output_File_" + to_string(j+1) + ".csv";
		key << endl;
	}
	cout << "File Key Printed...\nFile Name: " << keyN << "\n\n";
}


void readFile(int i, string& path, ifstream& inFile) {
	cout << "Reading File...\n\n";
	string line, token;
	vector<string> tokens;
	vector<Block*> blocks;
	string policyNumber, po1Num, p0Num;

	while (getline(inFile, line)) {


		if (line.empty()) { continue; }

		if (line[0] == '1' && (line.length() == 1 || line[1] != ' ')) {
			line = "1 " + line.substr(1);
		}

		tokens.clear();
		stringstream ss(line);

		while (ss >> token) {
			tokens.push_back(token);
		}

		if (tokens.empty()) { continue; }
		try {
			char firstChar = line[0];
			if (firstChar == '1' || firstChar == '0') {
				int id = (firstChar == '1') ? 1 : 0;
				// If line starts with 1 (header)
				if (id == 1) {
					po1Num = tokens[4];
					policyNumber = po1Num;
					Block* newBlock = new Block(id, policyNumber, tokens);
					blocks.push_back(newBlock);
				}
				// If line is 0# (policy marker)
				else if (tokens[0] == "0#") {
					if (tokens.size() > 6) {
						p0Num = tokens[6];
						policyNumber = p0Num;
						Block* newBlock = new Block(id, policyNumber, tokens);
						blocks.push_back(newBlock);
					}
					else {
						cerr << "Malformed 0# block: " << line << endl;
					}
				}
				// Segment blocks
				else {
					if (po1Num == p0Num) {
						Block* newBlock = new Block(id, policyNumber, tokens);
						blocks.push_back(newBlock);
					}
					else { throw runtime_error("Policy mismatch: Skipping line -> " + line); }
				}
			}
			else if (firstChar == ' ') {
				Block* lastBlock = blocks.back();
				vector<string> tempData = lastBlock->getData();
				tempData.insert(tempData.end(), tokens.begin(), tokens.end());
				lastBlock->setData(tempData);
			}
			else {
				throw runtime_error("First char Incorrect: " + line);
			}
		}
		catch (const runtime_error& e) {
			cout << "ERROR - " << e.what() << endl;
		}
	}
	cout << "Read File Complete...\n\n";
	if (!printFile(i, path, blocks)) { cout << "ERROR - Issue Printing File\n\n"; }

	for (Block* block : blocks) {
		delete block;
	}
	blocks.clear();

	
}