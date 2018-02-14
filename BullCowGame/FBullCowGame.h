/*
The is the header file for the FBullsCowsGame
*/
/////////////////////////////////////////////////
			/*The Including files*/
/////////////////////////////////////////////////
#pragma once
#include<string>
/////////////////////////////////////////////////
				/*Variables*/
/////////////////////////////////////////////////

using FString = std::string;
using int32 = int;

/////////////////////////////////////////////////
				/*Class Only*/
/////////////////////////////////////////////////
//All values inistialied too zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};
/////////////////////////////////////////////////
					/*Class*/
/////////////////////////////////////////////////
class FBullCowGame
{
public:
	FBullCowGame(); //Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void Reset(); //TODO make a more rich return value
	FBullCowCount SubmitValidGuess(FString);
private:
	//see constructor
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};