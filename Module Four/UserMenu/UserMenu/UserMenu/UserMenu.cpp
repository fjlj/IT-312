// UserMenu_Solution.cpp : This code contains five errors before it will work as desired.  Find those errors, 
// document a description of the errors and their fix, and fix them.  Try using the debugger to 
// step through the program to find the bugs.  As you step through, take notice of the information
// you can see.  

//This program builds a menu based on switchcase statements to determine where a user wants to go in the program.
// Program options are then to solve the Tower of Hanoi problem, view the user profile, or exit the program.

#include "pch.h"
#include <cstdlib>
#include <iostream>

using namespace std; //add std namespace to allow calls without explicit inclustion of std:: per line

void Tower(int, char, char, char);

int main()
{
	int choice;
	bool exiting = false;								//bool for main loop
	while (!exiting) {									//define main progam loop
		cout << "1. Solve the Tower of Hanoi" << endl;
		cout << "2. View Your Profile" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice : " << endl;
		cin >> choice;
		switch (choice)										//variable not defined capitaliazed. variables do not begin with capital letters in general.
		{
		case 1:
			system("cls");
			int numDiscs;

			cout << "**Tower of Hanoi**\n";
			cout << "Enter the number of discs :";			//Missing quotes to output text.
			cin >> numDiscs;
			cout << "\n\n";									//nothing wrong with this, however it is inconsistent with the previous use of endl (also not as portable).
			Tower(numDiscs, 'A', 'B', 'C');
			break;
		case 2:												//Missing case label 
			cout << "Username:\t\tPlayer 1" << endl;
			cout << "Gamertag:\t\tImTheBest" << endl;
			cout << "No. Hours Played:\t173" << endl;
			break;
		case 3:
			cout << "Now Exiting." << endl;
			exiting = true;									//add switch  to end loop
			break;
		default:
			cout << "You did not choose anything...so exit this program." << endl;
			exiting = true;									//add switch to end loop
		}
	}
		return 0;
}

void Tower(int numDiscs, char from, char aux, char to) {
	if (numDiscs == 1) {
		cout << "\tMove disc 1 from " << from << " to " << to << endl;	//change single /n to endl as it is more portable
		return;
	}
	else {
		Tower(numDiscs - 1, from, to, aux);					//correct function call, function defined with Capitalization
		cout << "\tMove disc " << numDiscs << " from " << from << " to " << to << endl; //change single /n to endl as it is more portable
		Tower(numDiscs - 1, aux, from, to);
	}
}