/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction. 
For game logic see the FBullCowGame class.
*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
FText ChooseDifficulty();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game at global scope

int main() 
{

	bool bPlayAgain = false;
	do {
		BCGame.Reset(ChooseDifficulty()); // Resets game based on game difficulty
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	std::cout << std::endl;
	return 0;
}


void PrintIntro() 
{
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n"	<< std::endl;
	std::cout << "       /)  (\\                  /)   (\\"			<< std::endl;
	std::cout << "  .-._((,~~.))_.-,        .-._((,~\"~.))_. - ,"	<< std::endl;
	std::cout << "   `-.   @@   ,-'          `-.   e e   ,-'  "		<< std::endl;
	std::cout << "     / ,o--o. \\              / ,o---o. \\"		<< std::endl;
	std::cout << "    ( ( .__. ) )   BULLS    ( ( .___. ) )"		<< std::endl;
	std::cout << "     ) `----' (      &       ) `-----' ("			<< std::endl;
	std::cout << "    /          \\   COWS     /`-.__ __.-'\\"		<< std::endl;
	std::cout << "   /            \\          /     ,8.     \\"		<< std::endl;
	std::cout << "  /              \\        /     /___\\     \\"	<< std::endl;
	std::cout << " /                \\      /      `-&-'      \\"	<< std::endl;
	std::cout << "When you enter a guess the computer will return the number of bulls and cows the guess had.\n";
	std::cout << "A Bull means that a letter in your guess shares a letter and is in the same spot as the hidden word.\n";
	std::cout << "A Cow means that a letter in your guess shares a letter with the hidden word but it is not in the same spot\n";
	std::cout << "For ex. If the hidden word was 'ant' and you guessed 'tna'. The game will show Bulls = 1, and cows = 2";
	std::cout << std::endl;
	std::cout << "\nCan you guess the " << BCGame.GetHiddenWordlength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	return;
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "\nYOU WON! Great job. ";
	}
	else {
		std::cout << "\nYou lose! ";
	}
	std::cout << "The word was " << BCGame.GetHiddenWord() << std::endl;
	return;
}

// plays a single game to completion
void PlayGame() 
{	
	int MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		
		FText Guess = GetValidGuess(); 

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bull = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();

	return;
}


FText GetValidGuess() 
{	
	int CurrentTry = BCGame.GetCurrentTry();
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {

		std::cout << "\nGuess " << CurrentTry << "/"<< BCGame.GetMaxTries() << ". Enter your guess:  ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValid(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordlength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Guess was not an isogram, a word with no repeating letters\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Guess must be in all lowercase";
			break;
		case EGuessStatus::Contains_Non_Alpha_Char:
			std::cout << "Guess cannot contain integers or special characters.\n";
			break;
		default:
			//assumes the guess is valid
			break;
		}

	} while (Status != EGuessStatus::OK);
	return Guess;
}

FText ChooseDifficulty()
{
	FString Choice;
	int RandIndex = rand() % 4;
	std::cout << "Choose difficulty (easy, medium, hard or expert):  ";
	std::getline(std::cin, Choice);
	if (Choice == "easy" || Choice == "medium" || Choice == "hard" || Choice == "expert")
	{
		return Choice;
	}
	else
	{
		std::cout << "\nUnrecognized input, defaulting difficulty to medium." << std::endl;
		return "medium";
	}
}

bool AskToPlayAgain() 
{
	FText Response = "";
	std::cout << "\nDo you want to play again (y/n)?  ";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (tolower(Response[0]) == 'y');
}
