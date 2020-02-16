// Squash_The_Bugs.cpp : This code contains five errors before it will work as desired.  Find those errors, 
// document a description of the errors and their fix, and fix them.  Try using the debugger to 
// step through the program to find the bugs.  As you step through, take notice of the information
// you can see.  

// This program gets an input of number of gallons of water used from the user.
// It will then calculate a customer's water bill using the following rules:
// A mandatory environmental fee of $15, plus
// $2.35 per 1000 gallons for the first 6000,
// $3.75 per 1000 gallons for over 6000 to 20000,
// $6.00 per 1000 gallons for over 20000.
// The bill is then displayed to the user.

#include "pch.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double gallons, charge, total = 0.0;		//initialize all values to 0.0
	const double fee = 15;						//since we are working in decimals already and dont have space constrains double is neater here and avoids the possibility of truncation.
	double costUpTo6K = 2.35,	                //change int to double... dealing with decimals here.. (float would also work...) technically valid syntax, could be mistaken for assignment.
		costUpTo20K = 3.75,
		costOver20K = 6.00;

	cout << "Enter the total number of gallons used, divided by 1000: ";
	cin >> gallons;

	if (gallons > 20.0) {						//explicitly compare with a float value (just easier to know that gallons was declared double... could alsu use hungarian style naming).
		charge = (gallons - 20) * costOver20K;
		charge += (14 * costUpTo20K);			//I believe there was a missing semi-colon i placed here
		charge += (6 * costUpTo6K);				//also using += rather than re assignment, easier to differentiate from initial assignment.
	}
	else if (gallons > 6 && gallons <= 20) {
		charge = (gallons - 6) * costUpTo20K;	//same here just some formatting fixes.
		charge += (6 * costUpTo6K);
	}
	else {
		charge = gallons * costUpTo6K;			//mis-spelling of variable name
	}


	total = charge + fee;
	cout << "You have used " << gallons << " thousand gallons of water." << endl;
	cout << "Your total water bill is $" << setprecision(2) << fixed << total;   //use total calculation rather than just fee.

	return 0;
}