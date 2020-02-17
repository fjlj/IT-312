// FinalProjectBB1.cpp : The players are presented the Farkle Rules from a text file
// the user is then prompted to input a number between 2 and 10 players and then begins gameplay with player1. 
// player one is informed of their current score and when ready rolls 6 dice and is asked to hold dice. 
// the players turn continues until all or no dice are held or a farkle occurse, resulting in loss of points.
// the player is given their points for their turn and their new overall score for the game. and asked to continue when ready
// The next player is displayed their score and asked to press a key when ready to roll. (no pun intended)
// the next player will take their turn. Players are not allowed to keep their points until they enter the game.
// entering the game occurs when the player achieves more than 1000 points in a turn.
// gameplay continues until a player 'goes out' by breaking 10,000 points. Remaining players are given a final turn.

#include "pch.h"
#include <iostream>
#include <time.h>   //used for seeding random  
#include <string>   //used to process strings
#include <vector>   //really only used to store player names...
#include <sstream>  //used for string stream processing

using namespace std;


//Dice class that will handle rolling and returning dice values

class Dice {
	
	//track IDs of dice internally and auto incriment on creation of new dice
	static int totalIDs;

	//values used to track/set various states of the dice
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
	
		if (!bHeld) {               //dont set a new value if the die is held
			int trv = nRollValue;   //temp variable to store the original value.
		
			//ensure player is not given the same value they had previously (just a little help to reduce the "cheated" feeling, not required)
			while (nRollValue == trv) {
				nRollValue = (rand() % sides) + 1;
			}
			
			//reset counted and set rerolled
			bCounted = false;
			bReRolled = true;
		}

		return nRollValue;
	}

	//a function to return the total number of dice created + 1
	int numDice() {
		return totalIDs;
	}

	//used to set the Dice ID on creation
	Dice() :
		nID(totalIDs++) {}

};   
	

//default value of totalIDs
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
	    rows[0].append(temp);		                          //append formatted information to the correct row (repeated for each row)

		//will draw dots in top left if the value is 2 3 4 5 or 6 and top right if the value is 4 5 or 6
		sprintf_s(temp,512,"| %s  %s|    ", ((dice[i].nRollValue & 2 || dice[i].nRollValue & 4) ? "o " : "  "), ((dice[i].nRollValue & 4) ? "o " : "  "));  
		rows[1].append(temp);
		
		//will draw dots in the center line on the left and right if the value is 6, will draw center dot if value is 1 3 or 5
		sprintf_s(temp,512,"| %s%s%s|    ",((dice[i].nRollValue & 6) == 6 ? "o " : "  "),(dice[i].nRollValue & 1 ? "o " : "  "),((dice[i].nRollValue & 6) == 6 ? "o " : "  "));
		rows[2].append(temp);
		
		//will draw dots in bottom left if value is 4 5 or 6 and bottom right if the value is 2 3 4 5 or 6
		sprintf_s(temp,512,"| %s  %s|    ",((dice[i].nRollValue & 4) ? "o " : "  "),((dice[i].nRollValue & 2 || dice[i].nRollValue & 4) ? "o " : "  "));
		rows[3].append(temp);
		
		//used to draw default, held or farkled status
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


//function to determine if the player has held all the dice
bool allHeld(int numDice, Dice dice[]) {

	//loop through each die return false if any have bHeld not set
	for (int i = 0; i < numDice; i++) {
		if(!dice[i].bHeld) 
			return false; 
	}

	//made it through all the dice, return true.
	return true;
}


//function to calculate points (this could probable be cleaner as well as multipurpose for farkle check.. however that was getting confusing and ugly)
int calculatePoints(int numDice,Dice dice[]) {
	
	int points = 0;  //accumulator

	//loop through each die and check for points
	for (int i = 0; i < numDice; i++) {

		if (!dice[i].bCounted && dice[i].bHeld) {                //only check dice that have not already been counted and have been held
			int tempVal = dice[i].nRollValue;                    //store the die's value for referencing 3 of a kind
			int valCount = 1;									 //initialize temporary variable for counting 3 of a kind as 1 since we already have 1 die with this value


			//loop through dice that have not been checked for 3 of a kind to occur.
				for (int h = (i + 1); h < numDice; h++) {

					//only incriment if the die matched saved value, is held and has not been counted
					if (dice[h].nRollValue == tempVal && !dice[h].bCounted && dice[h].bHeld) valCount++;    
				}


			//if we have 3 or more of a kind set 3 of those that are held to be counted
			if (valCount >= 3) {

				valCount = 3;                                            //used as a counter to make sure we mark 3 held dice as counted 
				points += (tempVal == 1 ? 1000 : (tempVal * 100));       //add 1000 to points if the face value was 1 otherwise set to 100 times face value
				

				//loop through dice until we have marked 3 of a kind that were held as counted, also stop if 6 would result in bounds error
				for (int j = 0; (valCount > 0 && j < numDice); j++) 
				{
					if (dice[j].nRollValue == tempVal && dice[j].bHeld) 
					{
						dice[j].bCounted = true;
						valCount--;
					}
				}

			}

			//if there was not 3 of a kind check that die face point value 1 = 100, 5 = 50  
			else {

				//(used switch mainly for readability... compier will optimize this to cascaded IF statements)
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


//function to determine if the player has hot-dice
bool hotDice(int numDice, Dice dice[]) {

	//loop through each die return false if any were not counted as points
	for (int i = 0; i < numDice; i++) {
		if(!dice[i].bCounted)
			return false;
	}

	//reset dice bHeld and bCounted states since all dice were counted as points and return true
		for (int i = 0; i < numDice; i++) {
			dice[i].bHeld = false;
			dice[i].bCounted = false;
		}
		return true;
}


//almost a copy of the calculate points function (merging these two functions is possible... however it started to get pretty ugly very quickly
//the difference is that this function counts the dice that were not held but have been reRolled and will reset the dies reRolled value to false
//thinking further about it now.. these should be a simplified class method that would compare its own value to other die in the same state.
//at this point that would be a significant rewrite for little to no benefit other than organization. *sings*I will refactor this later, refactor this later I will!*sings*
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
				for (int j = 0; (valCount > 0 && j < numDice); j++) {
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

	//if the reRolled dice have no point potential and we did not hold all of the dice (accepting non point die to end turn) we have farkled
	if (possiblePoints <= 0 && !allHeld(numDice,dice)) {
		for (int i = 0; i < numDice; i++) {
			dice[i].bCounted = true;
			dice[i].bFarkled = true;
		}
		return 0; //used to set turn points to 0
	}
	return possiblePoints; //used to track points
}


//function responsible for drawing the dice and handling player hold selection. 
//this is where farkle check is also implimented, points are returned to the main loop.
//function loops until all dice are held or a farkle occurs.
int promptRoll(int numDice, Dice dice[], bool hDice = false) {

	//variables to receive player input, save the score to, and determine if a farkle has occured
	string heldDice;
	int score = 0;
	int fval = farkle(numDice, dice);

	//if we made it to this function as a result of hot dice, let the user know we have hot dice
	if (hDice) {
		system("cls");
		cout << endl << "HOT DICE! At least 1 Roll is required! Good Luck!" << endl << endl;
		system("pause");   //pause before hot-dice roll, to prevent "instant farkle after first roll" this would be confusing to a player.
		system("cls");
	}

	//primary loop of function to continue rolling/holding until all held or a farkle.
	while (!allHeld(numDice, dice) && fval > 0) {

		//extra flag to clear screen buffer at the beginning of each roll as long as we didnt just clear it and display hot-dice message
		if (!hDice) {
			system("cls");
		}
		else {
			hDice = false;
		}


		//draw dice and prompt user to enter the IDs they want to hold.
		drawDice(numDice, dice);
		cout << endl << "Type the dice ID's separated by a SPACE you would like to hold:" << endl;
		getline(cin, heldDice);


		//variables to proccess user input as a single space delimited line of IDs
		stringstream in(heldDice);
		int temp;
		int nheld = 0;  //used to allow an emoty string to count the same as holding all dice and ending turn.

		//process each ID entered and set that Dice held to true and reRolled to false (to ensure it is not processed in farkel check)
		while (in >> temp) {
			if (temp - 1 >= 0 && temp - 1 < numDice) {
				dice[temp - 1].bHeld = true;
				dice[temp - 1].bReRolled = false;
				nheld++;
			}
		}

		//if we held 0 IDs treat this the same as holding all dice and mark them as held. 
		//no need to set ReRolled as a farkle is not allowed when all dice have been held.
		if (nheld == 0) {
			for (int i = 0; i < numDice; i++) {
				dice[i].bHeld = true;
			}
		}

		
		rollDice(numDice, dice, 6);                //reRoll the dice (dice class will only reRoll dice that were not held)
		fval = farkle(numDice, dice);              //set the farkle check value
		score += calculatePoints(numDice, dice);   //set the score the the calculated point value for held dice
	}

	//once outside of the loop we will return 0 if and only if we ended on a farkle and not all dice are held (mildly reduntant check)
	//otherwise we will return the overall turn score
	return (fval == 0 && !allHeld(numDice, dice) ? 0 : score);

}


//function to determine if all players are out or not
bool allOut(int numPlayers, bool *playerStatus) {

	//loop through each players out status return false if any are not out.
	for (int i = 0; i < numPlayers; i++) {
		if (playerStatus[i] == false)
			return false;
	}

	//all are out.
	return true;
}

//function to print out each players score as well as determine which player index is the highest and returns that index value.
int determineWinner(int numPlayers, int *scores) {
	
	//variables to store current highest score and that players index
	int highScore = 0;
	int winInd = 0;

	//title for score board
	cout << "Player | Score" << endl;

	//loop through each players score
	for (int i = 0; i < numPlayers; i++) 
	{

		//output the player number and their score
		cout << "   " << i + 1 << "   |" << "   " << scores[i] << endl;

		//set the highest score variable and the winner index to that scores index.
		if (scores[i] > highScore) {
			highScore = scores[i];
			winInd    =  i;
		}
	}

	//return the index of the highest score
	return winInd;
}

int main()
{

	//various state variables as well as accumulator variables
	bool exiting        =   false;	//used to allow another game when finished
	char pAgainAnswer   =   'y';	//check for play again or not
	int nNumPlayers     =   0;		//number of players
	bool bIsError	    =   false;	//input error flag
	int nErrorID        =   -1;		//input error ID
	int nRoundPoints    =   0;		//temporary variable for each round of dice rolling total points
	int nCurPlayer      =   0;		//value to hold which player is up to bat
	bool turnEnded      =   false;  //flag to determine if a players turn is complete
	int turnScore       =   0;		//overall turn accumulated points
	bool isHotDice      =   false;	//flag for weather we need to "take another turn" 
	bool lastTurn       =   false;	//flag for when each player will get 1 final turn because someone broke 10,000 points
	int winningPlayer   =   0;		//index of the winning player
	
	Dice playerDice[6];				//an array of 6 dice objects
	

	//Seed Random with current time (basic method typically used)
	srand(time(0));

	while (!exiting)
	{
		
		//ensure per game variables are initialized properly and console is cleared (allows for "play again" to work properly
		bool hasEntered[10] = { false };    //used to track weather each player has 'entered'
		int scores[10] = { 0 };				//used to store each players overall score
		bool isOut[10] = { false };			//used to track weather 1 or all players are out.
		nNumPlayers = 0;                   
		nRoundPoints = 0;					
		nCurPlayer = 0;						
		lastTurn = false;					
		system("cls");						//windows specific system call to clear the console screen buffer


		//output error if user attempted to input a number outside the range for number of players.
		if (bIsError) {
			switch (nErrorID) {
			case 1:

				cout << endl << "Invalid Number Entered, Lets try that again..." << endl;
				bIsError = false;
				nErrorID = -1;
				break;
			}
		}


		//prompt user to enter a number of players
		cout << endl << "Enter number Of Players between 2 and 10: ";
		cin >> nNumPlayers;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //prevent endless looping of cin when an error occured


		//make sure number of players is within range otherwise start again with error flag set
		if (nNumPlayers >= 2 && nNumPlayers <= 10)
		{
			//continue game until all players are out.
			while (!allOut(nNumPlayers, isOut))
			{

				//reinitialize turn specific variables
				turnEnded = false;		
				turnScore = 0;
				isHotDice = false;
				system("cls");
				
				//allow a player a turn as long as they are not out. otherwise prompt they are out displaying final score and continue to next player
				if (!isOut[nCurPlayer]) {
					
					//show message to player letting them know when they are on their last turn.
					if (lastTurn) {
						isOut[nCurPlayer] = true;
						cout << endl << "LAST TURN, MAKE IT A GOOD ONE!" << endl;
					}

					//prompt current player it is their turn and what their score is.
					cout << endl << "Player " << nCurPlayer + 1 << " Current Score:" << scores[nCurPlayer] << ", IF you are ready ";
					system("pause");

					//continue turn until flag is set to end the turn
					while (!turnEnded) {

						rollDice(6, playerDice, 6);                            //initial roll of 6 dice
						nRoundPoints = promptRoll(6, playerDice, isHotDice);   //set round points to outcome of rolling

						system("cls");

						//determine if we had a farkle, set turn over and display message.
						if (nRoundPoints == 0) {
							turnEnded = true;
							drawDice(6, playerDice);
							cout << endl << "FARKLE!!!" << endl;
							turnScore = 0;
						}
						else
						{
							//otherwise check to see if the player has hot-dice and set the appropriate flags
							if (!hotDice(6, playerDice)) {
								turnEnded = true;
								drawDice(6, playerDice);
							}
							else {
								isHotDice = true;
							}
						}

						//reset dice states for hot-dice or next players turn 
						for (int i = 0; i < 6; i++) {
							playerDice[i].bHeld = false;
							playerDice[i].bFarkled = false;
						}

						//accumulate total turn score by adding rolls points to it (allows for multiple 'turns' to allow hot-dice)
						turnScore += nRoundPoints;

					}

					//if the players turn results in 1000 or more points set that players entered flag to true
					if (turnScore >= 1000 && hasEntered[nCurPlayer] == false) {
						hasEntered[nCurPlayer] = true;
					}
					else 
					{
						//otherwise let the player know the amount of points and that it was not enough to enter 
						//(should probably show current points while rolling.. but I feel it adds to originality 
						//if the player has to count their own points while rolling.
						if (!hasEntered[nCurPlayer] && turnScore != 0)
							cout << endl << "Sorry " << turnScore << " is not enough to enter!" << endl;
					}

					//if the player has entered add their turn score to their overall game score 
					if (hasEntered[nCurPlayer]) scores[nCurPlayer] += turnScore;

					//check to see if the player has gone out and set flags
					if (scores[nCurPlayer] >= 10000) {
						isOut[nCurPlayer] = true;
						lastTurn = true;
					}
				}

				//output message at end of turn stating the turn is over or the player is out along with their score. 
				cout << endl << "Player " << nCurPlayer + 1 << (isOut[nCurPlayer] ? " IS OUT!" : " Turn Over") << endl << "Score: " << scores[nCurPlayer] << endl;
				
				if (turnScore > 0)
				{
					cout << "Points this turn: " << turnScore << endl;
				}


				system("pause");
				system("cls");

				//set the current player to the next player or the first player if we are at the last player
				nCurPlayer = (nCurPlayer + 1 >= nNumPlayers ? 0 : nCurPlayer + 1);
			}

			//all players are out we need to determine the winning player
			winningPlayer = determineWinner(nNumPlayers,scores);

			//output winning player and prompt for new game.
			cout << endl << "Player " << winningPlayer + 1 << " WINS! " << endl << "Would You like to have another go? [Y/n]: ";
			cin >> pAgainAnswer;

			//set exiting to true only if the user does not wish to go again
			exiting = (pAgainAnswer == 'n' || pAgainAnswer == 'N' ? true : false);
		}
		else 
		{
			//user input a number of players ouside the range 2-10
			bIsError = true;
			nErrorID = 1;
		}
	}

	//exit with error code SUCCESS
	return 0;
}
