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
FText GetValidGuess();
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
		FText Guess = GetValidGuess();

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	// TODO add a game summary
}

//loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		FText Guess;
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter an all-lowercase word.\n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
}
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
