#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int pushdetails(vector<string> info,string PNR) {
    string filename = PNR+".txt";

    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const string& line : info) {
            outfile << line << endl;
        }
        outfile.close();
    } else {
        cerr << "Failed to create the file." << endl;
    }

    return 0;
}
int isexist(string PNR){
        string filename = "PNRs.txt";

    ifstream infile(filename);

    if (infile.is_open()) {
        string line;

        while (getline(infile, line)) {
            if(line==PNR)
               return 1;
        }

        infile.close();
        return 0;
    } else {
        cerr << "Failed to open the file for reading." << endl;
    }
    return 0;

}
int pushpnr(string dataToAppend){
    ofstream outputFile("PRNs.txt", ios::app);
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for appending." << endl;
        return 1;
    }


    // Append the data to the file
    outputFile << dataToAppend << endl;

    // Close the file
    outputFile.close();


    return 0;
}
