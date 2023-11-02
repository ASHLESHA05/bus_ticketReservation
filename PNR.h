#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
// Function to generate a random alphanumeric character
char getRandomCharacter() {
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int randomIndex = rand() % characters.length();
    return characters[randomIndex];
}
// Function to generate a PNR number
string generatePNR(int length) {
    string pnr;
    for (int i = 0; i < length; i++) {
        pnr += getRandomCharacter();
    }
    return pnr;
}

string getNewPnr() {
	srand((unsigned) time(NULL));
    return generatePNR(6);
}
