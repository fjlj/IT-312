// FiveChests.cpp
// Frank Lewis
// IT-312 1-26-2020
// 
// This program demonstrates the use of an array
// A "player" will be prompted to input the number of the chest they have just found 1-5
// the input number will be used to demonstrate updating a specific element within the array.
// the player will then be notified if the "leveled up" based on the 5th element of the array.
// 
// NOTE: The prompt provided states both "only the fifth chest contains the token required to level up"
//       As well as "based on the Boolean of the fifth chest", as this reads one would soon realize
//       that entering 5 will result in a level up each time.. This could be written in a loop that allows
//       the "player" to try another input if they were to put in a number that is outside the array bounds.

#include "pch.h"
#include <iostream>

using namespace std;

int main()
{

	//declare variables to be used
	
	bool bChests[5] = { false,false,false,false,false };  //declare array that holds 5 values and initialize them to false
	int  nChestFound = -1;								  //integer variable to accept user input.

	
    //Prompt user for chest they have found.
    
	cout << "Which chest did you find! (1-5)? ";          //display prompt
	cin >> nChestFound;									  //wait for input and store

	
	//Update chest token in array and display level up message if chest 5 is true after update

	if (nChestFound - 1 < 0 || nChestFound - 1 > 4) {                //Array bounds checking
		cout << "That is not a valid chest. Value should be 1-5.";   //display message if input is outside array bounds
		return 1;													 //exit program with return code ERROR(1)
	}
	
	bChests[nChestFound-1] = true;									 //update the chest that was found to true
	cout << "Leveled Up? " << boolalpha << bChests[4];               //print leveled up based on status of 5th chest (4th array element)   

	return 0;														 //exit program with return code SUCCESS (0)
}