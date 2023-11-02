#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void load() {
    int r, q;
    gotoxy(36, 14);
    printf("loading...");
    gotoxy(30, 15);
    for (r = 1; r <= 20; r++) {
        for (q = 0; q <= 100000000; q++); // to display the character slowly
        printf("%c", 177);
    }
    getchar();  // Use _getch() instead of getch()
    system("cls");
}
void load1() {
    int r, q;
    gotoxy(36, 14);
    printf("processing payment...");
    gotoxy(30, 15);
    for (r = 1; r <= 20; r++) {
        for (q = 0; q <= 100000000; q++); // to display the character slowly
        printf("%c", 177);
    }
    getchar();  // Use _getch() instead of getch()
    system("cls");
}
