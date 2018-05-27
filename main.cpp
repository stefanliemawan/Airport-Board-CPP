#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include "Flight.h"

using namespace std;

int menu = 0;
bool run = true;

Flight flight;

void gotoxy(short x, short y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

void input() {

	if(_kbhit()) {
		switch(_getch()) {
			case '1' :
				menu = 0;
				break;
			case '2' :
				menu = 1;
				break;
			case '3' :
				menu = 2;
				break;
			case 'x' :
				run = false;
				break;
		}
	}
}

void menu1() {
	flight.clearQueue();
	flight.printData(); //cout << //"print ";
	flight.checkData(); //cout << //"check ";

	cout<<"Press 2 to search for flight..."<<endl;
	cout<<"Press 3 to see the announcement..."<<endl;
	flight.update(); //cout << "update "<< endl;

	gotoxy(0,0);

}

void menu2() {
	string flightnum;

	system("cls");
	cout<<"Flight Number : ";
	getline (std::cin,flightnum);
	flight.checkNum(flightnum);

	cout<<"press 1 to exit search"<<endl;
	system("cls");

}

void menu3() {
	system("cls");
	flight.announcement();
	system("cls");
}

int main() {
	srand(time(NULL));

	flight.declareData();

	while (run) {
		input();
		if(menu == 0) {
			menu1();
		} else if (menu == 1) {
			menu2();
		} else if(menu == 2) {
			menu3();
		}
		input();
	}

	cin.ignore();
	return 0;
}