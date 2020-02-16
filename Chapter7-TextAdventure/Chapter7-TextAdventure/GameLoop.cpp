/*
	This Program sets up a basic environment to provide a menu selection to a user while using an object oriented approach to this accomplish this.
	The player originally was only given the option to quit the program with the menu. I have been tasked to add another option to the menu to allow
	the player to be prompted to provide their preferred console (not entirely certain what this means, assuming game console?). and then repeat back
	to the player what console they told us they prefer, and resume execution until they ask to quit.
*/
#include "GameLoop.h"
#include <iostream>

using namespace std;

void Game::WelcomePlayer()
{
	cout << "Welcome to Text Adventure!" << endl << endl;
	cout << "What is your name?" << endl << endl;

	string name;
	cin >> name;
	m_player.SetName(name);

	cout << endl << "Hello " << m_player.GetName() << endl;
}

//Add Game class function to prompt for console preference and display back to the user what they just told us.
void Game::GetPlayerConsolePref() 
{
	cout << "So.. What Console do you Prefer?" << endl << endl;

	string consolePref;						//local variable to accept input (disposed after use)
	cin >> consolePref;						//accept input and store in variable
	m_player.SetConsolePref(consolePref);	//save the given input to the player class object
														
														//directly below, display object value that was saved.
	cout << endl << "Glad to hear you often enjoy the " << m_player.GetConsolePref() << " console!" << endl << endl;  
}

void Game::GivePlayerOptions() const
{
	cout << "What would you like to do? (Enter a corresponding number)" << endl << endl;
	cout << "1: Tell Me Your Preferred Console" << endl;       //add selection to provide preferred console (move quit to the last option as this is customary)
	cout << "2: Quit" << endl << endl;
}

void Game::GetPlayerInput(string& playerInput) const
{
	cin >> playerInput;
}

PlayerOptions Game::EvaluateInput(string& playerInput) const
{
	PlayerOptions chosenOption = PlayerOptions::None;

	//update input evaluation to accept our new menu option while also re-ordering them to match the menu output (provides continuity when reviewing code)
	if (playerInput.compare("1") == 0)
	{
		cout << "You have chosen to Tell Me which console you prefer!" << endl << endl;
		chosenOption = PlayerOptions::Tell;					//use newly added PlayerOption as return value to the Game class to allow tying player class and game class functionality
	}
	else if(playerInput.compare("2") == 0)
	{
		cout << "You have chosen to Quit!" << endl << endl;
		chosenOption = PlayerOptions::Quit;
	} 
	else 
	{
		cout << "I do not recognise that option, try again!" << endl << endl;
	}

	return chosenOption;
}

void Game::RunGame()
{
	WelcomePlayer();

	bool shouldEnd = false;
	while (shouldEnd == false)
	{
		GivePlayerOptions();

		string playerInput;
		GetPlayerInput(playerInput);

		//update if statement for should end to be a switch statement where we can evaluate any number of additional PlayerOptions
		switch (EvaluateInput(playerInput))
		{
			case PlayerOptions::Quit:		//set shouldEnd to true when we receive the Quit Player option
				shouldEnd = true;
				break;						//Don't forget your breaks... or the next case will evaluate also.

			case PlayerOptions::Tell:		//Call Game class function to collect player console preference when we receive the Tell Player Option
				GetPlayerConsolePref();
				break;
		}
		
	}
}