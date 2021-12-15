/*************************************************************
Description: number guessing game with a random number generator
introduction to class member functions, private and public member variables
mutator and accessor functions.
*************************************************************/

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include "numberguess.h"
using namespace std;

//function to test the copy constructor
void Print(numberGuess object);


int main()
{
	//Declared variables
	string yesOrNo = "y";
	numberGuess activeGame;
	int numGames = 0; //keep track of the number of games
	

	//ask the user if they want to play  ";
	cout << "Do you want to play the guessing game? (y(Y) or n(N)):  ";
	cin >> yesOrNo;

	while (yesOrNo == "y" || yesOrNo == "Y")
	{
		//add one to the number of games
		numGames++;

		//playOneRound
		activeGame.PlayOneRound();
		
		activeGame.SetCount(numGames);//keep track of the number of games

		//again?
		cout << "\n--------------------------------------------------\n";
		cout << "Do you want to play the another round? (y(Y) or n(N)):  ";
		cin >> yesOrNo;
	}
	activeGame.PrintGameResults();

	return  0;
}


//function to test the copy constructor
void Print(numberGuess object)
{
	object.PrintGameResults();
}
