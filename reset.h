#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void disp_Avai_Seats(int date, string code) {
    ifstream inputFile(code + ".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return;
    }
    ofstream outFile(code + ".csv");
    if (!outFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return ;
    }

    vector<vector<string>> data; // 2D vector to hold CSV data

    // Read and parse the CSV file
    string line;
    while (getline(inputFile, line)) {
        vector<string> row;
        stringstream lineStream(line);
        string cell;

        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    inputFile.close();

    // Print the desired rows and columns (Bus Number and Available Seats)
    int numRows = data.size();
    int numCols = data[0].size(); // Assuming all rows have the same number of columns
    for (int row = (1 + 8 * (date - 1)); row <= (6 + 8 * (date - 1)) && row < numRows; ++row) {
        // Assuming the seat information is in the 4th column (index 3)
            for (int i = 6; i < 36; i++) {
                //chang
                outFile << data[row][i] << "   ";
            }
            cout << "\n";
            return;
        }
    }
