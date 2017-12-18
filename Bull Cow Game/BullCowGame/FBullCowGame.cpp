#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetMaxTries()   const{ return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDEN_WORD = "planet";
	MyHiddenWord = HIDEN_WORD;

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString Guess)
{
	return false;
}

//receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;
	// setup a return variable 
	FBullCowCount BullCowCount;
	// loop through all letters in hte guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) 
	{
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) 
				{
					BullCowCount.Bulls++;
				}
			}
			else
			{
				BullCowCount.Cows++;
			}
		}
	}


	return BullCowCount;
}
