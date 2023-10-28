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
// This header file contains declarations for all of the functions in the Windows API, 
using namespace std;
class mainClass{
      string key ,bus_num;//this is a keycode for different bus places...
      int A[32],date,booked=0;
      char start[15],desti[15],name[15],phn[10];
    public:
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
    ifstream fin;
    fin.open(key+".csv");
    //read from file of respective destination code and print...
    //read from csv file.....

}
int mainClass::check_avilabe(string desti){
    //check for the availablle bus from the file 
    ifstream fin;
    string favi;
    fin.open("available_locations.txt");
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
    cin.getline(start,15);
    cout<<"Checking for availability.....";
    sleep(2);
    system("cls");
    cout<<"Checking for availability.....";
    sleep(2);
    system("cls");
    //write conditions in checking the destination
    if(!check_avilabe(start)){
       cout<<"No Bus for this loc\nDid u mean ";
       



       //try to extract from another CLASS  INHERITENCE....***#
       //USE THE CLASS TO READ THE ITEMS FROM FILE having  available CITIES

       cout<<"\n\n "<<getnearestloc(start,cities)<<"  ??";
       //write conditions for nearest location..
       //and display it
       getchar();
       system("cls");
       FillDetails();
    }
    else{
        cout<<"\n\nENTER destination: ";
        cin.getline(desti,15);
        if(!check_avilabe(desti)){
            cout<<"No Bus for this loc\nDid u mean ";
            //write conditions for nearest location..
            cout<<"\n\n "<<getnearestloc(start,cities)<<"  ??";
            //and display it
            getchar();
            system("cls");
            FillDetails();
        }
        else{  
               if(desti==start){
                cout<<"start and destination cannot be same plz re Enter....";
                getchar();
                system("cls");
                FillDetails();
               }
               char temp[5];
               cout<<"ENTER date of trave dd/mm  ";
               cin.getline(temp,5);
               //use regx to match date formatt.. its its wrog ask to reenter
        }    
    }
}
void mainClass::PERSONAL(){
  system("cls");
  cout<<" ENTER YOUR NAME :   ";
  cin.getline(name,15);
  cout<<"\n\nphone number : ";
  cin.getline(phn,10);
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
int main(){
  mainClass C;
  C.mainpage();

  // C.FillDetails();
  // C.PERSONAL();
  // C.display_Abus(C.key);
  // C.display_Avai(C.bus_num);
  // if(C.booked)
  //    C.displayTicket(C.bus_num,C.name,C.phn);
  C.display_Avai("231");

}


//use another .h file to get design...use file with bus number as file name
