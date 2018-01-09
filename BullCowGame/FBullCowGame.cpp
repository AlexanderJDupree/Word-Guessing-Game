#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() // Default Constructor initializes to null values
{ 
	MyHiddenWord = "";
	MyCurrentTry = 0;
	MyDifficulty = "";
	bGameWon = false;
} 

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordlength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

EGuessStatus FBullCowGame::CheckGuessValid(FString Guess) const
{	
	if (Guess.length() != GetHiddenWordlength()) {
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsIsogram(Guess)) 	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsAlphabetic(Guess)) {
		return EGuessStatus::Contains_Non_Alpha_Char;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else {
		return EGuessStatus::OK;
	}
}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,16} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}


void FBullCowGame::Reset(FString Difficulty)
{
	FString HIDDEN_WORD = GenerateIsogram(Difficulty);

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}


// receives a VALID guess, increments turn, returns guess.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessLength = Guess.length();
	for (int32 i = 0; i < GuessLength; i++) 
	{
		for (int32 j = 0; j < HiddenWordLength; j++) 
		{
			if (Guess[i] == MyHiddenWord[j]) //Matched letter condition
			{
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	//Check if game won, change bGameWon
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameWon = true;
	}
	else {
		bGameWon = false;
	}

	return BullCowCount;
}

FString FBullCowGame::GenerateIsogram(FString Difficulty)
{	
	int RandIndex = rand() % 4;

	if (Difficulty == "easy") { return EasyWords[RandIndex]; }
	else if (Difficulty == "medium") { return MediumWords[RandIndex]; }
	else if (Difficulty == "hard") { return HardWords[RandIndex]; }
	else if (Difficulty == "expert") { return ExpertWords[RandIndex]; }
	else { return MediumWords[RandIndex]; }
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 2) { return true; }
	
	TMap<char, bool> LetterSeen; // create hash table
	for (auto Letter : Word) // Ranged-based for loop
	{	
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; } 
		else { LetterSeen[Letter] = true; } // Adds letter to map
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{	
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}

bool FBullCowGame::IsAlphabetic(FString Word) const
{
	for (auto Letter : Word)
	{
		if (isdigit(Letter) || !isalnum(Letter))
		{ 
			return false; 
		}
	}
	return true;
}
