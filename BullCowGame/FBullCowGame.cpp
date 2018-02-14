/*
The Class that will hold the details of the Bull vs. Cows game
*/
/////////////////////////////////////////////////
			/*The including files*/
/////////////////////////////////////////////////

#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

/////////////////////////////////////////////////
				/*Get Methods*/
/////////////////////////////////////////////////

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,15 },{ 7,20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

/////////////////////////////////////////////////
				/*Constructor*/
/////////////////////////////////////////////////

FBullCowGame::FBullCowGame()
{
	Reset();
}

/////////////////////////////////////////////////
				/*Public Methods*/
/////////////////////////////////////////////////

//Checks the Guess and tests to see if the guess is real
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//If the guess isn't a isogram 
	{
		return EGuessStatus::Not_Isogram; //TODO write function
	}
	else if (!IsLowerCase(Guess))//if the guess isn't a lowercase 
	{
		return EGuessStatus::Not_Lowercase; //TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//Resets the game
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // THIS HAS TO BE AN ISOGRAM and 3-7 letters long.
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//Recieves a Valid Guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //Assume same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters agaisnt the Guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//If theyy match
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

/////////////////////////////////////////////////
				/*Private Methods*/
/////////////////////////////////////////////////

//Checks to see if the word is an isogram
bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (auto letter : Word)
	{
		letter = tolower(letter); //handle mixed case
		if (LetterSeen[letter])
		{
			return false; // not a isogram
		}
		else
		{
			LetterSeen[letter] = true; //Add it to the map
		}
	}
	return true; //for example in cases where /0 is entered
}

//Checks to see if the guess is all lower case
bool FBullCowGame::IsLowerCase(FString word) const
{
	if (word.length() <= 1)
	{
		return true;
	}
	for (auto letter : word)
	{
		if (!islower(letter))
		{
			return false; // not lowercase
		}
	}
	return true; //for example in cases where /0 is entered
}
