#pragma once
#include <string>

using FText = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bull = 0;
	int32 Cow = 0;
};

enum class EGuessStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetWordLength() const;
	bool IsGameWon(FText) const;
	void Reset();
	EGuessStatus CheckGuessValidity(FText);
	FBullCowCount SubmitGuess(FText);

private:
	int32 REPEATER;
	int32 CURENT_TRY;
	int32 WORD_LENGTH;
	FText MY_HIDDEN_WORD;
	bool IsIsogram(FText) const;
	bool IsLowerCase(FText) const;
};
