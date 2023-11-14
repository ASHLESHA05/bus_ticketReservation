// Header files
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<regex>
#include "layout.h" 
#include "load.h"
#include "Avai_seats.h"
#include "PNR.h"
#include "filestore.h"
#include "timecmp.h"
#include "updateCSV.h"
#include "is_seat_exist.h"
 

using namespace std;
class MainPage {
public:
    void mainpage(BOOKING &b, Display &d, DETAILS &de,MainPage &m);
};

class BUS {
public:
    string key, bus_num, ftime, dtime, DATE;
    int A[32], date;
    string start, desti, name, phn;
    int booked = 0;

    int check_available(string desti);
    string get_nearest_loc(const string&, const vector<string>&);
};

int BUS::check_available(string desti) {
    ifstream fin;
    string favi;
    fin.open("cities.txt");
    while (getline(fin, favi)) {
        if (desti == favi) {
            return 1;
        }
    }
    return 0;
}

string BUS::get_nearest_loc(const string& reference, const vector<string>& strings) {
    string HMS;
    int maxmatch = 0, count = 0;
    for (const string& str : strings) {
        count = 0;
        for (int i = 0; i < min(str.length(), reference.length()); i++) {
            if (reference[i] == str[i]) {
                count++;
            } else
                break;
        }
        if (maxmatch < count) {
            maxmatch = count;
            HMS = str;
        }
    }
    return HMS;
}

// Class to represent booking details

class DETAILS : public BUS {
public:
    void FillDetails(BOOKING &b,Display &d,DETAILS &DE,MainPage &m);
    void PERSONAL(int, string, string, int, int[],BOOKING &B,Display &D,DETAILS &DE,MainPage &m);
};

class BOOKING : public BUS {
public:
    void A_bus_list(int, string,BOOKING &b,Display &d, DETAILS &de,MainPage &m);
    void display_Avai(string, string,BOOKING &b, Display &d,DETAILS &de,MainPage &m);
};

void BOOKING::A_bus_list(int date, string code,BOOKING &b,Display &d, DETAILS &de,MainPage &m) {
    ifstream inputFile(code + ".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return;
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
    int numCols = data[0].size();
    std::system("cls");
    printf("The available buses are\n");
    printf("Bus Number\tPickup\tDrop\tSeats\tCost\tType\n");
    for (int row = (1 + 8 * (date - 1)); row <= (6 + 8 * (date - 1)) && row < numRows; ++row) {
        for (int col = 0; col < 6 && col < numCols; ++col) {
            cout << data[row][col] << "\t";
        }
        cout << endl;
    }
 
 
    cout << "1. Continue    2. Back" << endl;
    int temp;
    cin >> temp;
    if (temp == 2)
        de.FillDetails(b,d,de,m);
    else {
        cout << "\n\nEnter Bus Number: ";
        cin >> bus_num;
        display_Avai(code, bus_num,b,d,de,m);
    }
}
void BOOKING::display_Avai(string code, string num,BOOKING &b,Display &d,  DETAILS &de,MainPage &m){
    std::system("cls");
    cout << "\n\n Seat layout: \n\n";

    // Function from "layout.h" to print seat layout
    printseat();
    
   int value;

    // Function from "Avai_seats.h" to display available seats
    value=disp_Avai_Seats(date, code, num);
    if(value==0)
     {
      std::system("cls");
      A_bus_list(date,code,b,d,de,m);
     }
     

    cout << endl;

    ifstream fin;
    fin.open(num + ".txt");
    string ch;
    while (getline(fin, ch)){
        cout << ch << "  ";
    }
    fin.close();
    cout << "\n\n(type '0' to go back)\n\n";
    int n;
    cout << "how many seats : ";
    cin >> n;
    if (n != 0){
        cout << "enter seat number\n";
        if (n <= 4){
            for (int i = 0; i < n; i++){
                cout << "\nseat " << i+1 << ":";
                cin >> A[i];
                if(!is_seat(date,code,num,A[i]))
                   {
                    std::system("cls");
                    cout<<"\n THIS  SEAT  HAS  ALREADY  BEEN  BOOKED   !!";
                    sleep(2);
                    std::system("cls");
                    display_Avai(code,num,b,d,de,m);

                   }
                if(A[i]>30 && A[i]<1){
                   cout<<"\n\nPlease Enter Seat Number  1-30 \n ";
                   sleep(2);
                   display_Avai(code,num,b,d,de,m);
                }
            } 
            booked = 1;
        }
        else{
        cout << "you cannot select more than 4 seats";
        sleep(2);
        display_Avai(code, num,b,d,de,m);
    }

        // Function to collect personal information and book tickets
        de.PERSONAL(date, num, code, n, A,b,d,de,m);
    }
    else
        A_bus_list(date, code,b,d,de,m);

}


// Class to represent ticket details
//**********************************************************************************************************************************

void DETAILS::FillDetails(BOOKING &b,Display &d,DETAILS &DE,MainPage &m) {
    vector<string> cities;
    cout << "Enter starting point: ";
    cin >> start;
    cout << "Checking for availability.....";
    sleep(2);
    std::system("cls");
    cout << "Checking for availability.....";
    sleep(2);
    std::system("cls");

    ifstream fin("cities.txt");
    if (!fin.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return;
    }
    string var;
    while (getline(fin, var)) {
        cities.push_back(var);
    }

    if (!(b.check_available(start))) {
        cout << "No Bus for this location\nDid you mean ";
        for (char& c : start)
            c = tolower(c);

        char c;
        string city = b.get_nearest_loc(start, cities);
        cout << "\n\n " << city << "  ??  [ Y/N ]\n Press Y if yes, else press N\n\t";
        cin >> c;
        std::system("cls");
        if (c != 'Y' && c != 'y') {
            FillDetails(b,d,DE,m);
        }
        start = city;
    }

    cout << "\n\nEnter destination: ";
    cin >> desti;
    if (!check_available(desti)) {
        cout << "No Bus for this location\nDid you mean ";
        for (char& c : desti)
            c = tolower(c);
        char c;
        string city = get_nearest_loc(desti, cities);
        cout << "\n " << city << "  ??\n\n  [ Y/N ]\n Press Y if yes, else press N\n\t";
        cin >> c;
        std::system("cls");
        if (c != 'Y' && c != 'y') {
            FillDetails(b,d,DE,m);
        }
        desti = city;
    }

    if (desti == start) {
        cout << "Start and destination cannot be the same. Please re-enter....";
        getchar();
        std::system("cls");
        FillDetails(b,d,DE,m);
    }

    cout << "Enter date of travel (dd/mm/yyyy): ";
    cin >> DATE;
    regex pattern(R"(\d{2}/\d{2}/\d{4})");
    if (!regex_match(DATE, pattern)) {
        cout << "Enter a correct format" << endl;
        cout << "Re-enter details" << endl;
        sleep(2);
        std::system("cls");
        FillDetails(b,d,DE,m);
    }

    if (!datecmp(DATE)) {
        cout << "Enter a date greater than today's date" << endl;
        cout << "Re-enter details" << endl;
        sleep(2);
        std::system("cls");
        FillDetails(b,d,DE,m);
    }

    string p = "";
    p += DATE.substr(0, 2);
    date = stoi(p);

    string a = "", b1 = "";
    a += start.substr(0, 3);
    b1 += desti.substr(0, 3);
    key = a + b1;
    b.A_bus_list(date, key,b,d,DE,m);
}

void DETAILS::PERSONAL(int date, string num, string code, int n, int a[],BOOKING &B,Display &D,DETAILS &DE,MainPage &m){
       std::system("cls");
    cout << date << endl << code << endl << num << endl;
    vector<string> data;
    for (int i = 0; i < n; i++){
        cout << " ENTER passenger " << i+1 << " NAME :   ";
        cin >> name;
        data.emplace_back("Name:  " + name);
        cout << "\n\nphone number : ";
        cin >> phn;
        data.emplace_back("phone Number: " + phn);
    }
    string PNR = getNewPnr();
    while (isexist(PNR))
        PNR = getNewPnr();
    pushpnr(PNR);   

    string seats;
    for (int i = 0; i < n; i++)
        seats += to_string(a[i]) + "  ";
    data.emplace_back("Date of Travel: " + to_string(date));
    data.emplace_back("From : " + start + "\tdeparture time:" + gettime(code, date, num, 1));
    data.emplace_back("To: " + desti + "\t Reaching time:" + gettime(code, date, num, 2));
    data.emplace_back("Number of seats: " + to_string(n));
    data.emplace_back("Seats: " + seats);
    string price = gettime(code, date, num, -1);
    int p = stoi(price);
    p = p * n;
    data.emplace_back("TOTAL COST :" + to_string(p));
    data.emplace_back("exit");

    cout << "Make Payment Now: (type any key)";
    char dummy;
    cin >> dummy;
    std::system("cls");
    load1();
    cout << "\n\n\t\tTICKET HAS BEEN BOOKED...ENJOY YOUR JOURNEY";
    sleep(3);
    std::system("cls");

    pushdetails(data, PNR);
    MakeChangesInCSV(date, num, code, n, a);

    cout << "Redirecting to main page in 3 seconds....";
    sleep(3);
    std::system("cls");

    m.mainpage(B,D,DE,m); 
}






// Class to represent display functionality
class Display : public BUS {
public:
    void displayTicket(string PNR, string phn,BOOKING &B,Display &D,DETAILS &DE,MainPage &m);
};

void Display::displayTicket(string PNR, string pnr,BOOKING &B,Display &D,DETAILS &DE,MainPage &m) {
    std::system("cls");
    string filename = PNR + ".txt";
    ifstream infile(filename);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    } else {
        cerr << "No Tickets Found!!!" << endl;
    }
    string dem;
    cout << "\n\nEnter 'exit' to redirect";
    cin >> dem;
    m.mainpage(B, D, DE,m);
}









// Class to represent the main page


void MainPage::mainpage(BOOKING &b, Display &d, DETAILS &de,MainPage &m) {
    system("cls");
    int choice = 0;
    string phn, PNR;
    cout << setw(25) << "WELCOME" << endl;
    cout << "\n\n\t1. Book Ticket\n\t2. View Your Ticket\n\t3. EXIT\n\t";
    cin >> choice;
    switch (choice) {
    case 0:
        mainpage(b, d, de,m);
        break;
    case 1:
        de.FillDetails(b,d,de,m);
        break;
    case 2:
        cout << "Enter your PNR and phone number:";
        cin >> PNR >> phn;
        d.displayTicket(PNR, phn,b,d,de,m);
        break;
    case 3:
        cout << "EXITING....IN .";
        sleep(2);
        system("cls");
        sleep(1);
        cout << "\n\n\t\t3 ";
        sleep(1);
        system("cls");
        cout << "\n\n\t\t2 ";
        sleep(1);
        system("cls");
        cout << "\n\n\t\t1 ";
        sleep(1);
        system("cls");

        exit(0);
    default:
        cout << "Enter valid Input [1-3]";
        sleep(2);
        mainpage(b, d, de,m);
        break;
    }
}

// Main function
int main() {
    BOOKING B;
    Display D;
    DETAILS DE;
    load();
    MainPage M;
    M.mainpage(B, D, DE,M);
    return 0;
}