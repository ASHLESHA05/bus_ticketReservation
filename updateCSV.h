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

int MakeChangesInCSV(int date,string bus_no,string code ,int n,int a[] ) {
   cout<<code<<endl;
   cout<<"in file: "<<a[0];
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
        for (int j = 0; j < n; ++j) {
            bool seatFound = false;
            for (int col = 6; col < 36 && col < numCols; ++col) {
                try {
                    // Convert to float then to int for comparison
                    int seatValue = static_cast<int>(stof(data[row][col]));
                    if (seatValue == a[j]) {
                        seatFound = true;
                        // Delete the found data entry
                        data[row][col] = "";
                        // Assuming data[row][3] is a count of available seats and is an integer.
                        int availableSeats = stoi(data[row][3]);
                        data[row][3] = to_string(availableSeats - 1);
                        break;
                    }
                } catch (const std::invalid_argument& e) {
                    // Handle non-numeric string or empty string
                    continue; // Skip this column
                } catch (const std::out_of_range& e) {
                    // Handle out of range error
                    cerr << "Number out of range: " << e.what() << endl;
                    continue; // Skip this column
                }
            }
            if (!seatFound) {
                cout << "Seat number " << a[j] << " not found for bus " << bus_no << endl;
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