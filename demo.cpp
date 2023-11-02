/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
int Av_bus_display(int date,string code) {
    //This displays the available bus for the route code
    ifstream inputFile("C:\\Users\\Ashlesha\\ENGINEERING projects\\"+code+".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return 1;
    }
    vector<vector<string>> data;

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

    // Print the desired rows and columns
    int numRows = data.size();
    int numCols = data[0].size(); // Assuming all rows have the same number of columns

    printf("The available busses are\n");
    printf("Bus Number\tPickup\tDrop\tSeats\tCost\tType\n\n");
    for (int row = (1+8*(date-1)); row <=(6+8*(date-1)) && row < numRows; ++row) {
        for (int col = 0; col < 6 && col < numCols; ++col) {
            cout << data[row][col] << "\t";
        }
        cout << endl;
    }

    return 0;
}


int main(){
    //Av_bus_display(2,"BUS1");
}
*/
#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void load() {
    int r, q;
    gotoxy(36, 14);
    printf("loading...");
    gotoxy(30, 15);
    for (r = 1; r <= 20; r++) {
        for (q = 0; q <= 100000000; q++); // to display the character slowly
        printf("%c", 177);
    }
    getchar();  // Use _getch() instead of getch()
    system("cls");
}

