#pragma once

#include "FBullCowGame.h"

//Unreal-friendly syntax
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); } 

int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
int32 FBullCowGame::GetMaxTries()   const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
void FBullCowGame::Reset()
{
	const FString HIDEN_WORD = "planet"; //this MUST be an isogram
	MyHiddenWord = HIDEN_WORD;

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
	else if (!IsLowercase(Guess)) 
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


FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//receives a valid guess, increments turn, and returns count
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
	if (Word.length() <= 1) { return true; }

	//setup our map
	TMap<char, bool> LetterSeen;

	//loop through the letters of the word, one by one
	for (auto Letter : Word)   //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case

		//if the letter is in the TMap, it's not an Isogram:
		if (LetterSeen[Letter]) { return false; }
		//otherwise, add the letter to the map as seen: 
		else { LetterSeen[Letter] = true; }
	}
	

	return true; // for example in cases where /0 is entered
}
bool FBullCowGame::IsLowercase(FString Word) const
{
	//check for 0-length, "\0" and spaces
	if (Word.length() == 0) { return true; }

	//loop through all the letters
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}

	//if every letter is lowercase:
	return true;
}
