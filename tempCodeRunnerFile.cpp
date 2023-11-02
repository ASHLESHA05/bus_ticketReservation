//all bus will be stored in a csv file with destination code as key.csv
//every bus seat availability will be stored in the bus_num.txt  read and write to that file
/*
way of working:
     -->enter the source and destination..
     -->checks for availability on the entered date..
     -->enter personal info
     -->display stet matrix
     -->select seat,payment
     -->booked,send mail, reciept 

*/
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include "layout.h" 
#include "load.h"
// This header file contains declarations for all of the functions in the Windows API, 
using namespace std;
class mainClass{
      
    public:
       string key ,bus_num;//this is a keycode for different bus places...
      int A[32],date;
     // char desti[15],name[15],phn[10];
      string start,desti,name,phn;
       int  booked=0;
      void changeInFileW();
      void readFile();
      void display_Abus(string);  
      void display_Avai(string);  //done  displays available seats
      int check_avilabe(string);
      void FillDetails();
      void PERSONAL();
      void mainpage();
      void displayTicket(string,string);
      string getnearestloc(const string& reference, const vector<string>& strings);
      // CREATE another class to get personal information

};
void mainClass::display_Avai(string num){     //this function is used to display thhe seat matrix of the bus
  //reading  from file the available seat in entered bus

    cout<<"\n\n Available seats: \n\n";
    printseat();
    ifstream fin;
    fin.open(num+".txt");
    string ch;
    while(getline(fin,ch))
    {
      cout<<ch<<"  ";
    }
    fin.close();
    int n;
    cout<<"how many seats : ";
    cin>>n;
    cout<<"enter seat number\n";
    if(n<=4){
    for(int i=1;i<=n;i++){
        cout<<"\nseat "<<i<<":";
        cin>>A[i];
}
    booked=1;
    //make chages in the file i.e decrease the seats according to number


    
    }
    else{
      cout<<"you cannot select more than 4 seat";
      display_Avai(num);
    }
    

}
void mainClass::display_Abus(string key){  // this displays available bus
    //readCSV(date,key);
    //read from file of respective destination code and print...
    //read from csv file.....

}
int mainClass::check_avilabe(string desti){
    //check for the availablle bus from the file 
    ifstream fin;
    string favi;
    fin.open("cities.txt");
     while(getline(fin,favi)){
       
        if(desti==favi){
        return 1;
      }
     }
  
    return 0;
          
        //clear the display
        
        //redirect to some of the nearest bus station. or ask for re enter
        // CALL START AND DESTINATION  AVAILABILITIES:

      }


string mainClass::getnearestloc(const string& reference, const vector<string>& strings){
     string HMS;//HIGHEST MATCHING STRING
     int maxmatch=0,count=0;
     for(const string& str:strings){
      count=0;
      for(int i=0;i<min(str.length(),reference.length());i++){
        if(reference[i]==str[i]){
          count++;
        }
        else 
          break;         //increasing untill we match the string  and assigning str to HMS  else set count=0
      }
      if(maxmatch<count){
        maxmatch=count;   //setting maxmatch as count and then   checking it whether next string matches same charecter or not..
        HMS=str;          //setting HMS to a city name ..it get changes whenever we encounter a city name which is morematching to the enterd city name

      }
    
     }
     return HMS;
}



void mainClass::FillDetails(){
    vector <string> cities;
    cout<<"enter starting point ";
    cin>>start;
    cout<<"Checking for availability.....";
    sleep(2);
    system("cls");
    cout<<"Checking for availability.....";
    sleep(2);
    system("cls");

        ifstream fin("cities.txt");
        if (!fin.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return;}
        string var;
        while(getline(fin,var)){
        cities.push_back(var);}
    //write conditions in checking the destination
    if(!check_avilabe(start)){
       cout<<"No Bus for this loc\nDid u mean ";
       


       //try to extract from another CLASS  INHERITENCE....***#
       //USE THE CLASS TO READ THE ITEMS FROM FILE having  available CITIES
      
      
      char c;
      string city=getnearestloc(start,cities);
       cout<<"\n\n "<<city<<"  ??  [ Y/N ]\n press Y if yes else press N\n\t";
       //write conditions for nearest location..
       //and display it
       cin>>c;
       system("cls");
       if(c!='Y'){
          
          FillDetails();
       }
       start=city;
    }
        cout<<"\n\nENTER destination: ";
        cin>>desti;
        if(!check_avilabe(desti)){
            cout<<"No Bus for this loc\nDid u mean ";
            //write conditions for nearest location..
            
            //and display it
      char c;
      string city=getnearestloc(desti,cities);
       cout<<"\n "<<city<<"  ??\n\n  [ Y/N ]\n press Y if yes else press N\n\t";
       //write conditions for nearest location..
       //and display it
       cin>>c;
       system("cls");
       if(c!='Y'){
          
          FillDetails();
       }
       desti=city;
       }
        else{  
               if(desti==start){
                cout<<"start and destination cannot be same plz re Enter....";
                getchar();
                system("cls");
                FillDetails();
               }
            
               cout<<"ENTER date of trave date  ";
               cin>>date;
               //use regx to match date formatt.. its its wrog ask to reenter
        } 
        key=start[0]+desti[0];   
    }

void mainClass::PERSONAL(){
  system("cls");
  cout<<" ENTER YOUR NAME :   ";
  cin>>name;
  cout<<"\n\nphone number : ";
  cin>>phn;
}
void mainClass::displayTicket(string PNR,string phn){
  //fetch all details of bus bnm from file..
  //in file of bus number bnm  search for person with name name_  ...  get info like source, destinaion
  system("cls");
  // create a drawing for bus ticket
  /*
  cout<<st<<"        ------        "<<ds;
  cout<<"\n        duration: "<<dura;
  cout<<"\n         price "<<Price;
  cout<<"passenger  ";
  cout.write(name,strlen(name));

  */
  cout<<"passenger  ";
  
}

void mainClass::mainpage(){
    int choice;
    string phn,PNR;
    cout<<setw(25)<<"WELCOME"<<endl;
    cout<<"\n\n\t1.Book Ticket\n\t2.view Your Ticket\n\t3.EXIT\n\t";
    cin>>choice;
    switch(choice){
      case 1:FillDetails();
             break;
      case 2:
            cout<<"Enter your PNR and phone number:";
            cin>>PNR>>phn;
            displayTicket(PNR,phn);
            break;
      case 3:
            cout<<"EXITING....IN   .";
            sleep(2);
            system("cls");
            sleep(1);
            cout<<"\n\n\t\t3 ";
            sleep(1);
            system("cls");
            cout<<"\n\n\t\t2 ";
            sleep(1);
            system("cls");
            cout<<"\n\n\t\t1 ";
            sleep(1);
            system("cls");

            exit(0);
      default:
            break;            

                   
    }


}
int readCSV(int date,string code) {
    ifstream inputFile(code+".csv");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return 1;
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

    printf("The available busses are\n");
    printf("Bus Number\tPickup\tDrop\tSeats\tCost\tType\n");
    for (int row = (1+8*(date-1)); row <=(6+8*(date-1)) && row < numRows; ++row) {
        for (int col = 0; col < 6 && col < numCols; ++col) {
            cout << data[row][col] << "\t";
        }
        cout << endl;
    }

    return 0;
}
int main(){
  mainClass C;
  load();
  C.mainpage();
  if(C.booked ==1)
     C.PERSONAL();
  // C.FillDetails();
  // C.PERSONAL();
   //C.display_Abus(C.key);
  // C.display_Avai(C.bus_num);
  // if(C.booked)
  //    C.displayTicket(C.bus_num,C.name,C.phn);
  C.display_Avai("231");

}


//use another .h file to get design...use file with bus number as file name