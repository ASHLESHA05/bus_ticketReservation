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
#include "layout.h"
// This header file contains declarations for all of the functions in the Windows API, 
using namespace std;
class mainClass{
    public:
      string key ,bus_num;//this is a keycode for different bus places...
      int A[32],date,booked=0;
      char start[15],desti[15],name[15],phn[10];
      void changeInFileW();
      void readFile();
      void display_Abus(string);  
      void display_Avai(string);  //done  displays available seats
      int check_avilabe(char[]);
      void FillDetails();
      void PERSONAL();
      void displayTicket(string,char[],char[]);
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
int mainClass::check_avilabe(char desti[]){
    //check for the availablle bus from the file 
    /*
      if(desti==favi){
        return 1;
      }
      else{
    return 0;
          
        //clear the display
        cout<<"Not available"
        //redirect to some of the nearest bus station. or ask for re enter
        // CALL START AND DESTINATION  AVAILABILITIES:

      }
    */
}
void mainClass::FillDetails(){
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
            //and display it
            getchar();
            system("cls");
            FillDetails();
        }
        else{  
               char temp[5];
               cout<<"ENTER date of trave dd/mm  ";
               cin.getline(temp,5);
               //use regx to match date formatt.. its its wrog ask to reenter
        }    
    }
}
void mainClass::PERSONAL(){
  system("cls");
  cout<<" ENTER YOUR NAME : ";
  cin.getline(name,15);
  cout<<"\n\nphone number : ";
  cin.getline(phn,10);
}
void mainClass::displayTicket(string bnm,char name_[],char phn_[]){
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
  
}
int main(){
  mainClass C;
  // C.FillDetails();
  // C.PERSONAL();
  // C.display_Abus(C.key);
  // C.display_Avai(C.bus_num);
  // if(C.booked)
  //    C.displayTicket(C.bus_num,C.name,C.phn);
  C.display_Avai("231");

}


//use another .h file to get design...use file with bus number as file name