/*
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Fallout.
*/
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

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
	Not_Lowercase,
	Contains_Non_Alpha_Char
};


class FBullCowGame 
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordlength() const;
	FString GetHiddenWord() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValid(FString) const;

	void Reset(FString);
	FBullCowCount SubmitValidGuess(FString);

private: //Member variables and helper functions
	int32 MyCurrentTry;
	FString MyHiddenWord;
	FString MyDifficulty;
	bool bGameWon;
	// All posible isograms based on difficulty
	FString EasyWords[4] = { "ant", "red", "fan", "car" };
	FString MediumWords[4] = { "plan", "blue", "care", "easy" };
	FString HardWords[4] = { "plane", "brown", "brick", "juice" };
	FString ExpertWords[4] = { "planet", "vector", "joyful", "losing" };

	FString GenerateIsogram(FString);
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsAlphabetic(FString) const;
};