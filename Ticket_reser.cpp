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

// Class definition
class mainClass{
public:
    // Member variables
    string key, bus_num, ftime, dtime, DATE;
    int A[32], date;
    string start, desti, name, phn;
    int booked = 0;

    // Member functions
    void A_bus_list(int, string);
    void display_Avai(string, string);
    int check_avilabe(string);
    void FillDetails();
    void PERSONAL(int, string, string, int, int[]);
    void mainpage();
    void displayTicket(string, string);
    string getnearestloc(const string&, const vector<string>&);
};

// Function to display available seats and book tickets
void mainClass::display_Avai(string code, string num){
    system("cls");
    cout << "\n\n Seat layout: \n\n";

    // Function from "layout.h" to print seat layout
    printseat();
    
   int value;

    // Function from "Avai_seats.h" to display available seats
    value=disp_Avai_Seats(date, code, num);
    if(value==0)
     {
      system("cls");
      A_bus_list(date,code);
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
                    system("cls");
                    cout<<"\n THIS  SEAT  HAS  ALREADY  BEEN  BOOKED   !!";
                    sleep(2);
                    system("cls");
                    display_Avai(code,num);

                   }
                if(A[i]>30 && A[i]<1){
                   cout<<"\n\nPlease Enter Seat Number  1-30 \n ";
                   sleep(2);
                   display_Avai(code,num);
                }
            } 
            booked = 1;
        }
        else{
        cout << "you cannot select more than 4 seats";
        sleep(2);
        display_Avai(code, num);
    }


        // Function to collect personal information and book tickets
        PERSONAL(date, num, code, n, A);
    }
    else
        A_bus_list(date, code);

}

// Function to display available buses
void mainClass::A_bus_list(int date, string code){
    cout << code << endl;
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
    system("cls");
    printf("The available buses are\n");
    printf("Bus Number\tPickup\tDrop\tSeats\tCost\tType\n");
    for (int row = (1 + 8 * (date - 1)); row <= (6 + 8 * (date - 1)) && row < numRows; ++row) {
        for (int col = 0; col < 6 && col < numCols; ++col) {
            cout << data[row][col] << "\t";
        }
        cout << endl;
    }

    cout << "1. Continue    2.back" << endl;
    int temp;
    cin >> temp;
    if (temp == 2)
        FillDetails();
    else{
        cout << "\n\nEnter Bus Number: ";
        cin >> bus_num;
        display_Avai(code, bus_num);
    }    
}

// Function to check if the given city is available
int mainClass::check_avilabe(string desti){
    ifstream fin;
    string favi;
    fin.open("cities.txt");
    while (getline(fin, favi)){
        if (desti == favi){
            return 1;
        }
    }
  
    return 0;
}

// Function to get the nearest location
string mainClass::getnearestloc(const string& reference, const vector<string>& strings){
    string HMS;
    int maxmatch = 0, count = 0;
    for (const string& str : strings){
        count = 0;
        for (int i = 0; i < min(str.length(), reference.length()); i++){
            if (reference[i] == str[i]){
                count++;
            }
            else 
                break;
        }
        if (maxmatch < count){
            maxmatch = count;
            HMS = str;
        }
    }
    return HMS;
}

// Function to fill in the travel details
void mainClass::FillDetails(){
    vector <string> cities;
    cout << "enter starting point ";
    cin >> start;
    cout << "Checking for availability.....";
    sleep(2);
    system("cls");
    cout << "Checking for availability.....";
    sleep(2);
    system("cls");

    ifstream fin("cities.txt");
    if (!fin.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return;
    }
    string var;
    while (getline(fin, var)){
        cities.push_back(var);
    }

    if (!check_avilabe(start)){
        cout << "No Bus for this loc\nDid u mean ";
        for (char& c : start) 
            c = tolower(c);
      
        char c;
        string city = getnearestloc(start, cities);
        cout << "\n\n " << city << "  ??  [ Y/N ]\n press Y if yes else press N\n\t";
        cin >> c;
        system("cls");
        if (c != 'Y' || c!='y'){
            FillDetails();
        }
        start = city;
    }

    cout << "\n\nENTER destination: ";
    cin >> desti;
    if (!check_avilabe(desti)){
        cout << "No Bus for this loc\nDid u mean ";
        for (char& c : start) 
            c = tolower(c);  
        char c;
        string city = getnearestloc(desti, cities);
        cout << "\n " << city << "  ??\n\n  [ Y/N ]\n press Y if yes else press N\n\t";
        cin >> c;
        system("cls");
        if (c != 'Y' || c != 'y'){
            FillDetails();
        }
        desti = city;
    }

    if (desti == start){
        cout << "start and destination cannot be same please re-enter....";
        getchar();
        system("cls");
        FillDetails();
    }      

    cout << "ENTER date of travel date dd/mm/yyyy ";
    cin >> DATE;  
    regex pattern(R"(\d{2}/\d{2}/\d{4})");
    if (!regex_match(DATE, pattern)){
        cout << "enter a correct format" << endl;
        cout << "re-enter details" << endl;
        sleep(2);
        system("cls");
        FillDetails();
    }

    if (!datecmp(DATE)){
        cout << "enter a date greater than today's date" << endl;
        cout << "re-enter details" << endl;
        sleep(2);
        system("cls");
        FillDetails();
    }

    string p = "";
    p += DATE.substr(0, 2);
    date = stoi(p);

    string a = "", b = "";
    a += start.substr(0, 3);
    b += desti.substr(0, 3);
    key = a + b;
    A_bus_list(date, key); 
}

// Function to handle personal details and book tickets
void mainClass::PERSONAL(int date, string num, string code, int n, int a[]){
    system("cls");
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
    system("cls");
    load1();
    cout << "\n\n\t\tTICKET HAS BEEN BOOKED...ENJOY YOUR JOURNEY";
    sleep(3);
    system("cls");

    pushdetails(data, PNR);
    MakeChangesInCSV(date, num, code, n, a);

    cout << "Redirecting to main page in 3 seconds....";
    sleep(3);
    system("cls");
    mainpage();
}

// Function to display the ticket based on PNR and phone number
void mainClass::displayTicket(string PNR, string phn){
    system("cls");
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
    cout << "\n\nENTER exit to redirect";
    cin >> dem;
    mainpage();
}

// Function to display the main page with options
void mainClass::mainpage(){
    system("cls");
    int choice=0;
    string phn, PNR;
    cout << setw(25) << "WELCOME" << endl;
    cout << "\n\n\t1. Book Ticket\n\t2. View Your Ticket\n\t3. EXIT\n\t";
    cin >> choice;
    switch (choice){
        case 0:
            mainpage();
            break;
        case 1:
            FillDetails();
            break;
        case 2:
            cout << "Enter your PNR and phone number:";
            cin >> PNR >> phn;
            displayTicket(PNR, phn);
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
            mainpage();
            break;
    }
}

// Main function
int main(){
    mainClass C;
    load();
    C.mainpage();
}
