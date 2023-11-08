#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int MakeChangesInCSV(int date,string code, string bus_no ,int n,int a[] ) {
    ifstream inputFile(code+".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return 1;
    }

    vector<vector<string>> data;
    string line;
    while (getline(inputFile, line)) {
        vector<string> row = split(line, ',');
        data.push_back(row);
    }

    inputFile.close();

    
    int numRows = data.size();
    int numCols = data[0].size(); // Assuming all rows have the same number of columns

    int seat_no;
    // seat numbers are stored in array a[n]
 

    bool found = false;
    int row = -1; // Initialize row to an invalid value

    for (int i = 1 + 8 * (date - 1); i <= 6 + 8 * (date - 1) && i < numRows; ++i) {
        if (data[i][0] == bus_no) {
            found = true;
            row = i;
            break;
        }
    }

    if (found) {
        for(int j=0;j<n;j++)
        for (int col = 6; col < 36 && col < numCols; ++col) {
            if (stoi(data[row][col]) == a[j]) {
                // Delete the found data entry
                data[row][col] = "";
                break;
            }
        }

        // Update the CSV file with the modified data
        ofstream outputFile(code+".csv");
        if (outputFile.is_open()) {
            for (const vector<string>& row : data) {
                for (int col = 0;col < numCols; ++col) {
                    outputFile << row[col];
                    if (col < numCols - 1) {
                        outputFile << ",";
                    }
                }
                outputFile << endl;
            }
            outputFile.close();
        } else {
            cerr << "Failed to open the CSV file for writing." << endl;
            return 1;
        }
    } else {
        cout << "Bus not found in the specified date range." << endl;
    }

    return 0;
}