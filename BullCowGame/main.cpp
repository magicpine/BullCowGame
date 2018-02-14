/*
This Is the main part of the Bull Vs Cows game. 
*/
/////////////////////////////////////////////////
			/*Including files*/
/////////////////////////////////////////////////
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
/////////////////////////////////////////////////
	/*Declearing the variables and Methods*/
/////////////////////////////////////////////////
using FText = std::string;
using int32 = int32;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;
/////////////////////////////////////////////////
				/*The Methods*/
/////////////////////////////////////////////////
//The entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro(); 
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	} while (bPlayAgain);

	return 0; //exit
}
//Will print the start of the game
void PrintIntro()
{
	//Writes the info for the Start of the Game

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram that I'm thinking of?\n";
	std::cout << std::endl;
	return;
}
//The Main part, this will keep the game running based on answers given
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//Loop for the number of turns asking for guess while the game is not won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".  Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}
//Loop untill the user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		//Gets the Guess from an input
		//The Guess variable
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::OK:
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Pleaser enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
			//Assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping untill we get no errors
	return Guess;
}
//Will do what it needs to, too run the game
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return  (Response[0] == 'y' || Response[0] == 'Y');
}
//Will print the winning/losing method
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN! \n";
	}
	else
	{
		std::cout << "Better luck next time! \n";
	}
}

