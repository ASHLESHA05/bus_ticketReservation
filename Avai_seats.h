#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int disp_Avai_Seats(int date, string code, string BUS_NUMBER) {
    ifstream inputFile(code + ".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return 1;
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

    cout << "Available Buses and Their Seat Numbers" << endl;
    cout << "Bus Number\tSeats" << endl;
    
    for (int row = (1 + 8 * (date - 1)); row <= (6 + 8 * (date - 1)) && row < numRows; ++row) {
        // Assuming the seat information is in the 4th column (index 3)
        if (data[row][0] == BUS_NUMBER) {
            for (int i = 6; i < 36; i++) {
                cout << data[row][i] << "   ";
            }
            cout << "\n";
            return 0;
        }
    }
    return 0;
}
string gettime(string code,int date,string BUS_NUMBER,int n){
       ifstream inputFile(code + ".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return "";
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
        if (data[row][0] == BUS_NUMBER) {
            if(n==-1)
               return data[row][4];
            return data[row][n];
        }
    }

}

