/*
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "layout.h" 
#include "load.h"
#include "Avai_seats.h"
#include "PNR.h"
#include "filestore.h"
#include "timecmp.h"
#include "updateCSV.h"
#include <typeinfo>
#include<unistd.h>
using namespace std;

void PERSONAL(int date,string code,string num,int n,int a[]){
  system("cls");
  string name,phn;
  string start="puttur";
  string desti="ben";
  vector<string> data;
  for(int i=0;i<n;i++){
  cout<<" ENTER passenger "<<i<<" NAME :   ";
  cin>>name;
  data.emplace_back("Name:  "+name);
  
  cout<<"\n\nphone number : ";
  cin>>phn;
  data.emplace_back("phone Number: "+phn);
  }
 
  string PNR=getNewPnr();
  while(isexist(PNR)){
      cout<<PNR<<endl;
      PNR=getNewPnr();
  }
  // PUSH TO PNR TO FILE PNR'S 
  pushpnr(PNR);  

   string seats;
    for(int i=0;i<n;i++)
       seats+=to_string(a[i])+"  ";

  cout<<"\n\nseats: "<<seats;     

  data.emplace_back("Date of Travel: "+to_string(date));

  data.emplace_back("From : "+start+"\tdeparture time:"+gettime(code,date,num,1)); 
  //ERROR IN GET TIME
  data.emplace_back("To: "+desti+"\t Reaching time:"+gettime(code,date,num,2));
  data.emplace_back("Number of seats: "+to_string(n));
  data.emplace_back("Seats: "+seats);

  cout<<"\n\ntype: "<<data[6]<<endl;

  string price=gettime(code,date,num,-1);  //e-1  means get pricd
  int p=stoi(price);
  p=p*n;
  data.emplace_back("TOTAL COST :"+to_string(p));
  data.emplace_back("exit");
  cout<<"Make Payment Now: (type any key)";
  char dummy;
  cin>>dummy;
  system("cls");
  load1();
  cout<<"\n\n\t\tTICKET HAS BEEN BOOKED...ENJOY YOUR JOURNEY";
  sleep(3);
  system("cls");

 // pushdetails(data,PNR); // HERE IT CREATES A NEW FILE CALLED PNR
  cout<<num<<endl;
 // MakeChangesInCSV(date,num,code,n,a);   //decrease the number of seats



 
    //The emplace_back method is similar to push_back, but it allows you to construct elements directly in the vector without the need for explicit temporary objects. 
   //store every details in  a file

}

*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "layout.h" 
#include "load.h"
#include "Avai_seats.h"
#include "PNR.h"
#include "filestore.h"
#include "timecmp.h"
#include "updateCSV.h"
#include <typeinfo>
#include<unistd.h>
using namespace std;
void A_bus_list(int date,string code){  // this displays available bus
    //readCSV(date,key);
    //read from file of respective destination code and print...
    //read from csv file.....
    cout<<code<<endl;
    ifstream inputFile(code+".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return;
    }

    vector<vector<string>> data;   //this is a double vector

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
    system("cls");
    printf("The available busses are\n");
    printf("Bus Number\tPickup\tDrop\tSeats\tCost\tType\n");
    for (int row = (1+8*(date-1)); row <=(6+8*(date-1)) && row < numRows; ++row) {
        for (int col = 0; col < 6 && col < numCols; ++col) {
            cout << data[row][col] << "\t";
        }
        cout << endl;
    }


}
int main(){
  A_bus_list(2,"putben");

}