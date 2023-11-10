#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int is_seat(int date, string code, string BUS_NUMBER,int n) {
    ifstream inputFile(code + ".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return 1;
    }
    vector<vector<string>> data; 
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
    int numRows = data.size();
    int numCols = data[0].size(); // Assuming all rows have the same number of columns
    for (int row = (1 + 8 * (date - 1)); row <= (6 + 8 * (date - 1)) && row < numRows; ++row) {
        // Assuming the seat information is in the 4th column (index 3)
        if (data[row][0] == BUS_NUMBER) {
                if(data[row][5+n] == to_string(n)) 
                     return 1;
            
           
        }
    }
    return 0;
}