#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetMaxTries()   const{ return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDEN_WORD = "planet";
	
	MyHiddenWord = HIDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if the guess isn't an isogram, return an error
	if (!IsIsogram(Guess)) 
	{ 
		return EGuessStatus::Not_Isogram;
	}
	//if the guess isn't all lowercase, return an error 
	else if (false) 
	{ 
		return EGuessStatus::Not_Lowercase; //TODO write function
	}
	//if the guess length is wrong, return an error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	//otherwise, return OK
	else
	{
		return EGuessStatus::OK;
	}
}

//receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) //if they're in the same place
				{
					BullCowCount.Bulls++; //increment bulls
				}
				else
				{
					BullCowCount.Cows++; //must be a cow otherwise
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) { bGameIsWon = true; }
	else { bGameIsWon = false; }

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms

	//loop through the letters of the word, one by one
		//if the letter is in the TMap
			//it's not an isogram
		//otherwise
			//add the letter to the map as seen

	return true; // for example in cases where /0 is entered
}
