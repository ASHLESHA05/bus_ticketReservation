#include <ctime>
#include <iostream>
#include <string>


using namespace std;

int datecmp(string enteredDate) {
    // Get the current date and time
    time_t now = time(0);
    tm* today = localtime(&now);



    // Parse the entered date
    tm enteredTm = {};
    if (sscanf(enteredDate.c_str(), "%d/%d/%d", &enteredTm.tm_mday, &enteredTm.tm_mon, &enteredTm.tm_year) == 3) {
        enteredTm.tm_mon--; // Adjust the month to be 0-based (0 = January)
        enteredTm.tm_year -= 1900; // Adjust the year (years since 1900)
    } else {
        cout << "Invalid date format." << endl;
        return 1;
    }

    // Compare the entered date with today's date
     if (enteredTm.tm_year > today->tm_year)
          return 1;
        if (enteredTm.tm_year == today->tm_year)  
            if(enteredTm.tm_mon > today->tm_mon)
                return 1;
            if(enteredTm.tm_mon == today->tm_mon)
               if(enteredTm.tm_mday >= today->tm_mday)
                return 1;
return 0;  
   
  
}
  //  if (enteredTm.tm_year >= today->tm_year)   || enteredTm.tm_mday >= today->tm_mday)) {
//
