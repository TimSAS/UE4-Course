/*	This is the console executable, that makes use of the BullCow class
This  acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#include<iostream>
#include<string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game

int main()
{
	//std::cout << BCGame.GetMaxTries() << std::endl;
	//std::cout << BCGame.GetCurrentTry() << std::endl;
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for the number of tries, asking for 
	for (int32 count = 0; count < MaxTries; count++) // TODO change from FOR to WHILE 
	{
		FText Guess = GetGuess(); 

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;

		//print number of bulls and cows
		std::cout << "You entered: " << Guess << std::endl;
		std::cout << std::endl;
	}

	// TODO add a game summary
}
FText GetGuess() //TODO change to GetValidGuess
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	FText Guess;
	std::getline(std::cin, Guess);
	return Guess;
}
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
