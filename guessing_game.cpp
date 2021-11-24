/*************************************************************
Description: number guessing game with a random number generator
introduction to class member functions, private and public member variables
mutator and accessor functions.
*************************************************************/
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
using namespace std;

class numberGuess
{
	public:
  numberGuess(); 	//constructor

  void SetUpperRange(int); //sets the upper range for the round (mutator)
  int  GetUpperRange()const; //returns the value of the private member variable (accessor)
  void SetNumGuesses(int);//sets the number of guesses for the round (mutator)
  int  GetNumGuesses()const;//returns the value of the private member variable (accessor)
  int  GetSolution()const; //returns the value of the private member variable (accessor)

  void GuessInput(); //gets the next guess from the user
  bool ProcessGuess(); //determines if the guess is right or wrong
  void GenerateSolution(); //generates the solution

  int small; //lowest value for feedback
  int large; //highest value for feedback
  bool above; //current guess above the solution
  bool below; //current guess below the solution

 private:
  int upperValue;//15, 50, or 150
  int numGuesses;//4, 6, or 8
  int currentGuess;//current guess input by the user
  int solution;//pseudo random generated number
};

//the default constructor is called when and object of numberGuess is delared
numberGuess::numberGuess()
{
	//initialize all member variables
	upperValue = 0;
	numGuesses = 0; //4, 6, or 8
	currentGuess = 0; //current guess input by the user
	solution = 0; //pseudo random generated number
	small = 0; //lowest value for feedback
	large = 0; //highest value for feedback
	above = 0; //current guess above the solution
	below = 0; //current guess below the solution
}

void numberGuess::SetUpperRange(int upper)
//mutator function
//Description: sets the upper value of the current round
{
	upperValue = upper;
}

int  numberGuess::GetUpperRange()const
//accessor function
//Description:  returns the upper value(private member variable)
{
	return upperValue;
}

void numberGuess::SetNumGuesses(int num)
//Description:  Sets the number of guesses for the current round.
{
	//set
	numGuesses = num;
}

int  numberGuess::GetNumGuesses()const
//returns the value of the private member variable (accessor)
{
	return numGuesses;
}

int  numberGuess::GetSolution()const
//returns the value of the private member variable (accessor)
{
	return solution;
}

void numberGuess::GuessInput()
//gets the next guess from the user
{
	//set the small and large variables
	if (below)
	{
		if (small < currentGuess)
		{
			small = currentGuess;
		}
	}
	if (above)
  {
    if (large > currentGuess)
    {
      large = currentGuess;
    }
}

  //Gets the guess
	cout << "\nEnter a guess between " << small << " and " << large << " : ";
  cin >> currentGuess;

}

bool numberGuess::ProcessGuess()
//determines if the guess is right or wrong
{
	if (currentGuess > solution)
	{
		cout << "\nYour guess was too high.";
		cout << "\n-----------------------";
		above = true;
		return false;
	}
	else if(currentGuess < solution){
		cout << "\nYour guess was too low.";
		cout << "\n-----------------------";
		below = true;
		return false;

	}
	else if(currentGuess == solution){
		return true;
	}
}

void numberGuess::GenerateSolution()
//generates the solution
{
	srand((unsigned)time(0));
	solution = 1 + rand() % upperValue;
}

void PlayOneRound(const string& name, numberGuess& currentGame);
//Precondition: name and currentGame is defined
//Postcondition: Solution is displayed
//Description: Plays the game until the user guesses the correct solution or doesn't responsed yes

void SetUpLevel(numberGuess& currentGame);
//Precondition: currentGame is initialized
//Postcondition: Defines numguesses and upper
//Description: Sets the values for numGuesses and upper based on the user's choice of level


int main()
{
	string name, yesOrNo = "y";
	numberGuess currentGame;

	cout << "Enter your first name: ";
	cin >> name;

	cout << "Do you want to play the guessing game? (y(Y) or n(N)):  ";
	cin >> yesOrNo;

	while (yesOrNo == "Y" || yesOrNo == "y")
	{
		//Play one round of the game
		PlayOneRound(name, currentGame);

		//Play again?
		cout << "\n--------------------------------------------------\n";
		cout << "Do you want to play the another round? (y(Y) or n(N)):  ";
		cin >> yesOrNo;
	}
	cout << "\nThanks for playing :D!\n";
	return  0;
}

void PlayOneRound(const string& name, numberGuess& currentGame)
//Description: Play one round of the number guess game
{
	//initalize bool values (public member variables)
	currentGame.above = 0;
	currentGame.below = 0;

	//set the upper range based on the level (LevelRange function)
	SetUpLevel(currentGame);
	cout << "\nYou will have " << currentGame.GetNumGuesses() << " guesses, Good Luck!" << endl;

	//initialize high and low values
	currentGame.small = 1;
	currentGame.large = currentGame.GetUpperRange(); //accessor function

	//generate the random number
	currentGame.GenerateSolution();

	for(int i = 0; i < currentGame.GetNumGuesses(); i++)
	{
		cout << "\nThis is guess number (" << i + 1 << " of " << currentGame.GetNumGuesses() << ")";
		currentGame.GuessInput(); //gets the next guess from the user

		//reset above and below bool values to false
		currentGame.below = 0;
		currentGame.above = 0;

		if (currentGame.ProcessGuess())
		{
			cout << "\nYou won that round, " << name << "!\n";
			i = currentGame.GetNumGuesses();//(accessor function)
		}
	}

	//Displays the solution
	cout << "\nTHE SOLUTION WAS " << currentGame.GetSolution() << endl;

}

void SetUpLevel(numberGuess& currentGame)
//Asks and gets the level and sets up one round of the game
{
	int level;

	//ask and get the level
	cout << "\n************************************************\n";
  cout << "What level (Enter 1, 2, or 3)?\n";
  cout << "(1) Level 1 - 4 guesses, numbers 1 through 15\n";
  cout << "(2) Level 2 - 6 guesses, numbers 1 through 50\n";
  cout << "(3) Level 3 - 8 guesses, numbers 1 through 150:\n";

  cin >> level;

	if(level == 1)
	{
		//mutator functions
		currentGame.SetNumGuesses(4);
		currentGame.SetUpperRange(15);
	}
	else if(level == 2)
		{
			//mutator functions
			currentGame.SetNumGuesses(6);
			currentGame.SetUpperRange(50);
		}
	else if(level == 3)
		{
			//mutator functions
			currentGame.SetNumGuesses(8);
			currentGame.SetUpperRange(150);
		}
	else
	{
		cout << "\nThat is not a valid level";
		SetUpLevel(currentGame);
	}
}
