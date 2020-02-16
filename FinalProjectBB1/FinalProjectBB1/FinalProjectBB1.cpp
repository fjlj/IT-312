// FinalProjectBB1.cpp : This file Prompts the user to input a number between 2 and 12. 
// It will then complete dice rolls of 2 die until the result matches the users input.
// The program will output each die's value and their combined value per roll.

#include "pch.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>

using namespace std;


//Dice class that will handle rolling and returning dice values

class Dice {
	static int totalIDs;
public:
	int nRollValue  = 0;
	bool bReRolled  = true;
	bool bHeld      = false;
	bool bCounted   = false;
	bool bFarkled   = false;
	const int nID;


public:
	//function to set a new value to a random roll
	int roll(int sides) {
		if (!bHeld) { //dont set a new value if the die is held
			int trv = nRollValue;
			while (nRollValue == trv) {
				nRollValue = (rand() % sides) + 1;
			}
			bCounted = false;
			bReRolled = true;
		}

		return nRollValue;
	}
	int numDice() {
		return totalIDs;
	}


	Dice() :
		nID(totalIDs++) {}

};   
	 
int Dice::totalIDs = 1;

//function to draw the die value to the screen using bitmasking to determine value
void drawDice(int numDice, Dice dice[]) {
	
	//array of strings to collect each die's values to be able to print them next to eachother
	string rows[5];

	//loop through each of the die and add the heading/value placements to each row string
	for (int i = 0; i < numDice; i++) {
		
		//a temporary char array to hold individual row values;
		char temp[512] = { 0 };                               //0 initiailized
		sprintf_s(temp,512, " ---%d---     ", dice[i].nID);   //apply appropriate formatting to the row per die values (repeate this for each row below)
		rows[0].append(temp);
		sprintf_s(temp,512,"| %s  %s|    ", ((dice[i].nRollValue & 2 || dice[i].nRollValue & 4) ? "o " : "  "), ((dice[i].nRollValue & 4) ? "o " : "  "));
		rows[1].append(temp);
		sprintf_s(temp,512,"| %s%s%s|    ",((dice[i].nRollValue & 6) == 6 ? "o " : "  "),(dice[i].nRollValue & 1 ? "o " : "  "),((dice[i].nRollValue & 6) == 6 ? "o " : "  "));
		rows[2].append(temp);
		sprintf_s(temp,512,"| %s  %s|    ",((dice[i].nRollValue & 4) ? "o " : "  "),((dice[i].nRollValue & 2 || dice[i].nRollValue & 4) ? "o " : "  "));
		rows[3].append(temp);
		sprintf_s(temp,512," %s     ",(dice[i].bHeld ? "-HELD!-" : (dice[i].bFarkled ? "FARKLE!" : "-------")));
		rows[4].append(temp);
	}

	//output each row's collective information followed by a new line.
	cout << endl;
	for (int i = 0; i < 5; i++) {
		cout << rows[i] << "\n";
	}
}

//function to roll numDice number of dice
void rollDice(int numDice, Dice dice[], int sides=6) {
	
	//loop through each die
	for (int i = 0; i < numDice; i++) {
		dice[i].roll(sides); //call that die's roll function
	}
}

bool allHeld(int numDice, Dice dice[]) {

	int heldCount = 0;
	//loop through each die
	for (int i = 0; i < numDice; i++) {
		heldCount += (dice[i].bHeld ? 1 : 0); //call that die's roll function
	}

	return heldCount == numDice;
}


int calculatePoints(int numDice,Dice dice[]) {
	
	int points = 0;

	for (int i = 0; i < numDice; i++) {
		if (!dice[i].bCounted && dice[i].bHeld) {
			int tempVal = dice[i].nRollValue;
			int valCount = 1;
			for (int h = i + 1; h < numDice; h++) {
				if (dice[h].nRollValue == tempVal && !dice[h].bCounted && dice[h].bHeld) valCount++;
			}
			if (valCount >= 3) {
				
				valCount = 3;
				points += (tempVal == 1 ? 1000 : (tempVal * 100));
				for (int j = 0; valCount > 0; j++) {
					if (dice[j].nRollValue == tempVal && dice[j].bHeld) {
						dice[j].bCounted = true;
						valCount--;
					}
				}

			}
			else {
				switch (dice[i].nRollValue) {
					case 1:
						points += 100;
						dice[i].bCounted = true;
						break;
					case 5:
						points += 50;
						dice[i].bCounted = true;
						break;
				}
			}
		}
	}

	return points;
}

bool hotDice(int numDice, Dice dice[]) {
	int hotDicePoints = 0;
	int countedCount = 0;

	//loop through each die
	for (int i = 0; i < numDice; i++) {
		countedCount += (dice[i].bCounted ? 1 : 0); 
	}

	if (countedCount == numDice) {
		for (int i = 0; i < numDice; i++) {
			dice[i].bHeld = false;
			dice[i].bCounted = false;
		}
		return true;
	}
	return false;
}


//TODO: corect this to count points properly
int farkle(int numDice, Dice dice[]) {
	

	int possiblePoints = 0;


	for (int i = 0; i < numDice; i++) {
		if (dice[i].bReRolled && !dice[i].bCounted) {
			int tempVal = dice[i].nRollValue;
			int valCount = 1;
			for (int h = i + 1; h < numDice; h++) {
				if (dice[h].nRollValue == tempVal && dice[h].bReRolled) valCount++;
			}
			if (valCount >= 3) {
				valCount = 3;
				possiblePoints += (tempVal == 1 ? 1000 : (tempVal * 100));
				for (int j = 0; valCount > 0; j++) {
					if (dice[j].nRollValue == tempVal) {
						dice[j].bReRolled = false;
						valCount--;
					}
				}

			}
			else {
				switch (dice[i].nRollValue) {
				case 1:
					possiblePoints += 100;
					dice[i].bReRolled = false;
					break;
				case 5:
					possiblePoints += 50;
					dice[i].bReRolled = false;
					break;
				}
			}
		}
	}

	if (possiblePoints <= 0 && !allHeld(numDice,dice)) {
		for (int i = 0; i < numDice; i++) {
			dice[i].bCounted = true;
			dice[i].bFarkled = true;
		}
		return 0;
	}
	return possiblePoints;
}

int promptRoll(int numDice, Dice dice[], bool hDice = false) {

	string heldDice;
	int score = 0;
	int fval = farkle(numDice, dice);

	if (hDice) {
		system("cls");
		cout << endl << "HOT DICE! At least 1 Roll is required! Good Luck!" << endl << endl;
	}

	while (!allHeld(numDice, dice) && fval > 0) {
		if (!hDice) {
			system("cls");
		}
		else {
			hDice = false;
		}
		drawDice(numDice, dice);
		cout << endl << "Type the dice ID's separated by a SPACE you would like to hold:" << endl;
		getline(cin, heldDice);

		stringstream in(heldDice);
		int temp;
		int nheld = 0;
		while (in >> temp) {
			if (temp - 1 >= 0 && temp - 1 < numDice) {
				dice[temp - 1].bHeld = true;
				dice[temp - 1].bReRolled = false;
				nheld++;
			}
		}

		if (nheld == 0) {
			for (int i = 0; i < numDice; i++) {
				dice[i].bHeld = true;
			}
		}

		rollDice(numDice, dice, 6);
		fval = farkle(numDice, dice);
		score += calculatePoints(numDice, dice);
	}

	return (fval == 0 && !allHeld(numDice, dice) ? 0 : score);

}

bool allOut(int numPlayers, bool *playerStatus) {
	for (int i = 0; i < numPlayers; i++) {
		if (playerStatus[i] == false)
			return false;
	}
	return true;
}

int determineWinner(int numPlayers, int *scores) {
	int highScore = 0;
	int winInd = 0;

	cout << "Player | Score" << endl;
	for (int i = 0; i < numPlayers; i++) {
		cout << "   " << i + 1 << "   |" << "   " << scores[i] << endl;
		if (scores[i] > highScore) {
			highScore = scores[i];
			winInd    =  i;
		}
	}

	return winInd;
}

int main()
{
	bool exiting        =   false;
	char pAgainAnswer   =   'y';
	int nNumPlayers     =   0;
	bool bIsError	    =   false;
	int nErrorID        =   -1;
	int nRoundPoints    =   0;
	int nCurPlayer      =   0;
	bool turnEnded      =   false;
	int turnScore       =   0;
	bool isHotDice      =   false;
	bool lastTurn       =   false;
	int winningPlayer   =   0;
	
	Dice playerDice[6];
	

	//Seed Random with current time (basic method typically used)
	srand(time(0));

	while (!exiting)
	{
		
		//ensure roll total and number of rolls always start at 0 and console is cleared
		bool hasEntered[10] = { false };
		int scores[10] = { 0 };
		bool isOut[10] = { false };
		nNumPlayers = 0;
		nRoundPoints = 0;
		nCurPlayer = 0;
		lastTurn = false;
		system("cls");	//windows specific system call to clear the console screen buffer


		//output error if user attempted to input a number outside the range.
		if (bIsError) {
			switch (nErrorID) {
			case 1:

				cout << endl << "Invalid Number Entered, Lets try that again..." << endl;
				bIsError = false;
				nErrorID = -1;
				break;
			}
		}


		//prompt user to enter a number
		cout << endl << "Enter number Of Players between 2 and 10: ";
		cin >> nNumPlayers;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');


		//make sure input is within range otherwise start again with error flag set
		if (nNumPlayers >= 2 && nNumPlayers <= 10)
		{

			while (!allOut(nNumPlayers, isOut))
			{

				turnEnded = false;
				turnScore = 0;
				isHotDice = false;
				system("cls");
				

				if (!isOut[nCurPlayer]) {
					
					if (lastTurn) {
						isOut[nCurPlayer] = true;
						cout << endl << "LAST TURN, MAKE IT A GOOD ONE!" << endl;
					}

					cout << endl << "Player " << nCurPlayer + 1 << " Current Score:" << scores[nCurPlayer] << ", IF you are ready ";
					system("pause");

					while (!turnEnded) {
						rollDice(6, playerDice, 6);
						nRoundPoints = promptRoll(6, playerDice, isHotDice);

						system("cls");
						if (nRoundPoints == 0) {
							turnEnded = true;
							drawDice(6, playerDice);
							cout << endl << "FARKLE!!!" << endl;
							turnScore = 0;
						}
						else
						{
							if (!hotDice(6, playerDice)) {
								turnEnded = true;
								drawDice(6, playerDice);
							}
							else {
								isHotDice = true;
							}
						}
						for (int i = 0; i < 6; i++) {
							playerDice[i].bHeld = false;
							playerDice[i].bFarkled = false;
						}
						turnScore += nRoundPoints;

					}
					if (turnScore >= 1000 && hasEntered[nCurPlayer] == false) {
						hasEntered[nCurPlayer] = true;
					}
					else {
						if (!hasEntered[nCurPlayer] && turnScore != 0)
							cout << endl << "Sorry " << turnScore << " is not enough to enter!" << endl;
					}
					if (hasEntered[nCurPlayer]) scores[nCurPlayer] += turnScore;

					if (scores[nCurPlayer] >= 10000) {
						isOut[nCurPlayer] = true;
						lastTurn = true;
					}
				}
				cout << endl << "Player " << nCurPlayer + 1 << (isOut[nCurPlayer] ? " IS OUT!" : " Turn Over,") << " Score: " << scores[nCurPlayer] << ", ";
				system("pause");
				system("cls");
				nCurPlayer = (nCurPlayer + 1 >= nNumPlayers ? 0 : nCurPlayer + 1);
			}
			winningPlayer = determineWinner(nNumPlayers,scores);
			cout << endl << "Player " << winningPlayer + 1 << " WINS! " << endl << "Would You like to have another go? [Y/n]: ";
			cin >> pAgainAnswer;


			//set exiting to true only if the user does not wish to go again
			exiting = (pAgainAnswer == 'n' || pAgainAnswer == 'N' ? true : false);
		}
		else 
		{
			//user input a number ouside the range 2-12
			bIsError = true;
			nErrorID = 1;
		}
	}

	//exit with error code SUCCESS
	return 0;
}
