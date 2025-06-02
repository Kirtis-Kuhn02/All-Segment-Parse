// All Segment Parse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Functions.h"



int main() {
	cout << "Welcome to the Data Parser for the TSO reports!!\n\n";



	int choice = 0, i = 1;
	cout << "How many files are you parsing today? (Please enter an integer)\n> ";
	cin >> choice;
	cin.ignore(); // flush leftover newline



	string inFileN;
	string examplePath = R"("C:\Users\kc00109\source\repos\All Segment Parse\debug_output.txt")";
	cout << "Please enter the full path to each file.\n";
	cout << "Example: " << examplePath << "\n\n";

	string path;
	vector<string> fileNs;

	while (i <= choice) {
		try {
			cout << i << ".) > ";
			getline(cin, inFileN);
			cout << endl;

			if (inFileN == "q" || inFileN == "Q") { break; }

			// Remove quotes from copied path
			if (!inFileN.empty() && inFileN.front() == '"' && inFileN.back() == '"') {
				inFileN = inFileN.substr(1, inFileN.size() - 2);
			}
			fileNs.push_back(inFileN);

			path = getFolderPath(inFileN);
			ifstream inFile(inFileN);
			if (!inFile.good()) {
				throw runtime_error("File not accessible: " + inFileN);
			}

			readFile(i, path,  inFile);
			inFile.close();
			i++;
		}
		catch (runtime_error& e) {
			cout << "ERROR - " << e.what() << endl;
			cout << "Enter q to quit\n\n";
		}
		
	}

	printKey( i, path, fileNs);


	cout << "Goodbye!";
	return 0;
}


