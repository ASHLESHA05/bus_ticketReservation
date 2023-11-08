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
//main code

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

// This header file contains declarations for all of the functions in the Windows API, 
using namespace std;
class mainClass{
      
    public:
       string key ,bus_num,ftime,dtime,DATE;//this is a keycode for different bus places...
      int A[32],date;
     // char desti[15],name[15],phn[10];
      string start,desti,name,phn;
       int  booked=0;
      void changeInFileW();
      void readFile();
      void A_bus_list(int,string);  //CSV READING
      void display_Avai(string,string);  //done  displays available seats
      int check_avilabe(string);
      void FillDetails();
      void PERSONAL(int,string,string,int,int[]);
      void mainpage();
      void displayTicket(string,string);
      string getnearestloc(const string& reference, const vector<string>& strings);
      // CREATE another class to get personal information

};

void mainClass::display_Avai(string code,string num){     //this function is used to display thhe seat matrix of the bus
  //reading  from file the available seat in entered bus

    cout<<"\n\n Seat layout: \n\n";

    printseat();
    cout<<"\n\nAvailable seats:\n";
    disp_Avai_Seats(date,code,num);
    cout<<endl;

    ifstream fin;
    fin.open(num+".txt");
    string ch;
    while(getline(fin,ch))
    {
      cout<<ch<<"  ";
    }
    fin.close();
    cout<<"\n\n(type '0' to go back)\n\n";
    int n;
    cout<<"how many seats : ";
    cin>>n;
    if(n!=0){
    cout<<"enter seat number\n";
    if(n<=4){
    for(int i=1;i<=n;i++){
        cout<<"\nseat "<<i<<":";
        cin>>A[i];
}
    booked=1;
    }
    else
      A_bus_list(date,code);
    //make chages in the file i.e decrease the seats according to number
    //make_seat_change(date,code,num,n,A);
    PERSONAL(date,num,code,n,A);

    
    }
    else{
      cout<<"you cannot select more than 4 seat";
      display_Avai(code,num);
    }
    

}
void mainClass::A_bus_list(int date,string code){  // this displays available bus
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

    cout<<"1. Continue    2.back"<<endl;
    int temp;
    cin>>temp;
    if(temp==2)
        FillDetails();
    else
        cout<<"\n\nEnter Bus Number: ";
        cin>>bus_num;
        display_Avai(code,bus_num);    
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
        for (char& c : start) 
              c = tolower(c);
      
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
  
               if(desti==start){
                cout<<"start and destination cannot be same plz re Enter....";
                getchar();
                system("cls");
                FillDetails();
               }
            
               cout<<"ENTER date of trave date dd/mm/yyyy ";
               cin>>DATE;
              
               regex pattern(R"(\d{2}/\d{2}/\d{4})");
               if(!regex_match(DATE,pattern)){
                  cout<<"enter a corect formatt"<<endl;
                  cout<<"re-enter details"<<endl;
                  sleep(2);
                  system("cls");
                  FillDetails();
               }
               if(!datecmp(DATE)){
                  cout<<"enter a date greater than todays date"<<endl;
                  cout<<"re-enter details"<<endl;
                  sleep(2);
                  system("cls");
                  FillDetails();
               }
               string p="";
               p+=DATE.substr(0,2);
               date=stoi(p);
               //use regx to match date formatt.. its its wrog ask to reenter
        
      string a="", b="";
      a += start.substr(0, 3); // Take the first three characters of 'start'
      b += desti.substr(0, 3); // Take the first three characters of 'desti'
      key = a + b; // Concatenate 'a' and 'b' to create the 'key' string


        A_bus_list(date,key); 
    }

void mainClass::PERSONAL(int date,string code,string num,int n,int a[]){
  system("cls");
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
  while(isexist(PNR))
      PNR=getNewPnr();
  // PUSH TO PNR TO FILE PNR'S 
  pushpnr(PNR);   
   string seats;
    for(int i=0;i<n;i++)
       seats+=to_string(a[i])+"  ";
  data.emplace_back("Date of Travel: "+to_string(date));
  data.emplace_back("From : "+start+"\tdeparture time:"+gettime(num,date,code,1));   //ERROR IN GET TIME
  data.emplace_back("To: "+desti+"\t Reaching time:"+gettime(num,date,code,2));
  data.emplace_back("Number of seats: "+to_string(n));
  data.emplace_back("Seats: "+seats);

  string price=gettime(num,date,code,-1);  //e-1  means get pricd
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

  pushdetails(data,PNR); // HERE IT CREATES A NEW FILE CALLED PNR

  MakeChangesInCSV(date,code,num,n,a);   //decrease the number of seats

  cout<<"Redirecting to main page in 3 second ....";
  sleep(3);
  system("cls");
  mainpage();
    //The emplace_back method is similar to push_back, but it allows you to construct elements directly in the vector without the need for explicit temporary objects. 
   //store every details in  a file

}
void mainClass::displayTicket(string PNR,string phn){
  //fetch all details of bus bnm from file..
  //in file of bus number bnm  search for person with name name_  ...  get info like source, destinaion
  system("cls");
  // create a drawing for bus ticket
   string filename = PNR+".txt";  // Change to the filename you want to read

    // Create an input file stream (ifstream) and open the file for reading
    ifstream infile(filename);

    if (infile.is_open()) {
        string line;

        // Read and print the content of the file line by line
        while (getline(infile, line)) {
            cout << line << endl;
        }

        // Close the file when you're done
        infile.close();
    } else {
        cerr << "Failed to open the file for reading." << endl;
    }
    string dem;
    cout<<"\n\nENTER exit to redirect";
    cin>>dem;
    mainpage();
  
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

int main(){
  mainClass C;
  load();
  C.mainpage();
  // if(C.booked ==1)
    // C.PERSONAL();
  // C.FillDetails();
  // C.PERSONAL();
   //C.A_bus_list(C.key);
  // C.display_Avai(C.bus_num);
  // if(C.booked)
  //    C.displayTicket(C.bus_num,C.name,C.phn);
  

}
///updared

//use another .h file to get design...use file with bus number as file name