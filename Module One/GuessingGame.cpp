#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	//Seed the random number generator
	srand(time(0));
	int selectedNumber = rand() % 20 + 1;
	int numberOfTries = 0;
	int inputtedGuess;
	
	cout << "Guess My Number Game\n\n";

	//Ask the user for a value until the correct number is entered
	do {
		cout << "Enter a guess between 1 and 20:";
		cin >> inputtedGuess;
		++numberOfTries;
		if(inputtedGuess > 20 || inputtedGuess < 1) 
		{ 
			cout << "Your guess is out of range. \n\n"; 
		}
		else if(inputtedGuess > selectedNumber) 
		{ 
			cout << "Too high!\n\n"; 
		}
		else if(inputtedGuess < selectedNumber) 
		{
			cout << "Too low!\n\n"; 
		}
	} while(inputtedGuess != selectedNumber);
	//Congratulate the user and end the program

	cout << "\nCongratulations! You solved it in " << numberOfTries << " tries!\n";
	return 0;
}