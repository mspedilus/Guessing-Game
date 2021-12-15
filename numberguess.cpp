//cpp file for the numberguess

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include "numberguess.h"
using namespace std;

//default constructor
numberGuess::numberGuess()
{
	//cout << "------------------------------------------------\n";
	//cout << "The default constructor has been called\n";
	count = 0;
	size = 1;
	playerList = new Player[size];
	playerList[0].upperValue = 0;//15, 50, or 150
	//set all variables for the first player to 0

	small = 0;//lowest value for feedback
	large = 0;//highest value for feedback
	above = 0;//current guess above the solution
	below = 0;//current guess below the solution
}

//copy constructor
numberGuess::numberGuess(const numberGuess& gameObject)
{
	cout << "------------------------------------------------\n";
	cout << "The copy constructor has been called\n";
	count = gameObject.count;
	size = gameObject.size;
	playerList = new Player[size];
	for (int i = 0; i < count; i++)
	{
		playerList[i] = gameObject.playerList[i];
	}
	small = 0;
	large = 0;
	above = false;
	below = false;
}

//destructor
numberGuess::~numberGuess()
{
	delete[] playerList;
}


//overload assignment operator
numberGuess& numberGuess::operator = (const numberGuess& right_side)
{
	//if the same object occurs on both sides of the assignment
	//example game1 = game1;
	if (this == &right_side)
	{
		return *this;
	}
	else
	{
		//delete the playList of the guessGame on the left side of the =
		//assignment operator
		delete[] playerList; //remove the playList of the existing object
		cout << "------------------------------------------------\n";
		cout << "The overload assignment operator has been called\n";
		count = right_side.count;//set the count
		size = right_side.size;//set the capacity
		playerList = new Player[size];//new playlist

		//copy all the players
		for (int i = 0; i < count; i++)
		{
			playerList[i] = right_side.playerList[i];
		}
		small = 0;
		large = 0;
		above = false;
		below = false;
		return *this;
	}
}

void numberGuess::SetUpLevel()
//sets up a round of the game
{
	do {
		cout << "************************************************\n";
		cout << "what level (Enter 1,2, or 3) would you like to play in? \n(1) Level 1 - 4 guesses, numbers 1 through 15 \n" <<
			"(2) Level 2 - 6 guesses, numbers 1 through 50\n" <<
			"(3) Level 3 - 8 guesses, numbers 1 through 150\n";
		cin >> playerList[count].level;
		cout << "************************************************\n";
	} while (playerList[count].level > 3 || playerList[count].level < 1);


	if (playerList[count].level == 1)
	{
		playerList[count].numGuesses = 4;
		playerList[count].upperValue = 15;
	}
	else if(playerList[count].level == 2)
		{
			playerList[count].numGuesses = 6;
			playerList[count].upperValue = 50;
		}
	else if(playerList[count].level == 3)
		{
			
			playerList[count].numGuesses = 8;
			playerList[count].upperValue = 150;
		}
	else
	{
		cout << "\nThat is not a valid level";
	}
}

void numberGuess::PlayOneRound()
//Description:  Play one round of the number guess game
{
	//test and double
	TestAndDouble();
	//get the players name
	cout << "What is your name? ";
	cin >> playerList[count].name;

	//set up level
	SetUpLevel();
	//initalize bool
	above = 0;
	below = 0;

	//initialize high and low values
	small = 1;
	large = playerList[count].upperValue;

	cout << "\nYou will have " << playerList[count].numGuesses << " guesses, Good Luck!" << endl;

	//generate the random number
	GenerateSolution();

	//loop(number of guesses)
	for(int i = 0; i < playerList[count].numGuesses; i++)
	{
		cout << "\n-----------------------";
		cout << "\nThis is guess number (" << i + 1 << " of " << playerList[count].numGuesses << ")";
		//get the next guess
		GuessInput();
		//reset above and below bool values to false
		below = 0;
		above = 0;

		if (ProcessGuess())
		{
			//tell the user they won
			cout << "\nYou won that round, " << playerList[count].name << "!\n";
			playerList[count].wonOrLost = 1;
			break;
		}
	}
	if (playerList[count].wonOrLost != 1) //If player lost the round
	{
		cout << "\nYou did not win that round, " << playerList[count].name << ".\n";
		playerList[count].wonOrLost = 0;
	}
	//prints the solution onto the screen
	cout << "\nTHE SOLUTION WAS " << playerList[count].solution << endl;
}


void numberGuess::GuessInput()
//Description:  Displays the range, prompts, and gets the next guess from the user
{
	//member variables
	if (below)
	{
		if (small < playerList[count].currentGuess)
		{
			small = playerList[count].currentGuess;
		}
	}
	if (above)
	{
		if (large > playerList[count].currentGuess)
		{
			large = playerList[count].currentGuess;
		}
	}
	cout << "\nEnter a guess between " << small << " and " << large << " : ";
	cin >> playerList[count].currentGuess;
}

bool numberGuess::ProcessGuess()
//Description:  Describe what the function does.
{
	if (playerList[count].currentGuess > playerList[count].solution) //If the player guess is higher than the solution
	{
		cout << "\nYour guess was too high.";
		cout << "\n-----------------------";
		above = true;
		return false;
	}
	else if(playerList[count].currentGuess < playerList[count].solution){ //If the player guess is lower than the solution
		cout << "\nYour guess was too low.";
		cout << "\n-----------------------";
		below = true;
		return false;

	}
	else if(playerList[count].currentGuess == playerList[count].solution){ //If the player guess equals the solution
		return true;
	}
}

void numberGuess::GenerateSolution()
{
	srand((unsigned)time(0));
	playerList[count].solution = 1 + rand() % playerList[count].upperValue; //Generates random number for the solution
}

void numberGuess::TestAndDouble()
//dynamically double the size of the player list
{
	if (count == size)
	{
		size *= 2;
		Player* t = new Player[size];
		for(int i = 0; i < count; i++)
		{
			t[i] = playerList[i];
		}
		delete [ ] playerList;
		playerList = t;
	}
}

void numberGuess::PrintGameResults()
//prints the player, level, wonOrLost on the screen
{
	cout << "\n***********************************\n";
	cout << "Name\t" << "Level\t" << "won or lost\n";

	//Print the name, level, wonOrlost onto the screen for each player
	for (int i = 0; i < count; i++) {
		cout << playerList[i].name << "\t" << playerList[i].level << "\t" << playerList[i].wonOrLost << endl;
	}

}

//sets the number of players
void numberGuess::SetCount(int numPlayers)
{
	count = numPlayers;
}
