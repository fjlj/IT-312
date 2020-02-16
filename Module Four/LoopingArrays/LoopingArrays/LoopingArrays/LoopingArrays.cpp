// LoopingArrays.cpp : This program loops through to create an array based on user input and then 
// sorts the array in order of smallest integer to largest.  Format the code following the code
// styling document.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void main()
{

	//variable declarations
	int array[10]    = { 0 };
	int temp         =   0;
	bool bSortAgain  = true;
	char cAgainInput = 'y';


	//put program in loop to allow multiple runs.
	while (bSortAgain)
	{

		//prompt for 10 number entries
		for (int x = 0; x < 10; x++)
		{
			cout << "Enter Integer No. " << (x + 1) << ":";
			cin >> array[x];
		}


		//linear sort array elements smallest to largest using temp as a carrier
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (array[j] > array[j + 1])
				{
					temp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = temp;
				}
			}
		}

		//print sorted array via iteration.
		cout << "Array in ascending order is : " << endl;
		for (int& x : array)
			cout << x << endl;

		
		//Ask user if they would like to do it again
		cout << "Would you like to sort again? [Y/n]";
		cin >> cAgainInput;

		//set sort again boolean to false only if the user inputs n or N otherwise maintain true.
		bSortAgain = (cAgainInput == 'n' || cAgainInput == 'N' ? false : true);

	}
	//end program
	return;
}