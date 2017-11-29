#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame() {
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return REPEATER; }
int32 FBullCowGame::GetCurrentTry() const { return CURENT_TRY; }
int32 FBullCowGame::GetWordLength() const { return WORD_LENGTH; }
bool FBullCowGame::IsGameWon(FText Guess) const { 
	if (Guess == MY_HIDDEN_WORD) {
		return true;
	}
	return false; 
}

void FBullCowGame::Reset()
{
	REPEATER = 5;
	CURENT_TRY = 1;
	MY_HIDDEN_WORD = "planet";
	WORD_LENGTH = MY_HIDDEN_WORD.length();
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FText Guess)
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if(Guess.length() != WORD_LENGTH) {
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else {
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitGuess(FText input)
{
	/* Input must be valid */
	CURENT_TRY++;
	int32 LENGTH = MY_HIDDEN_WORD.length();
	int32 ILENGTH = input.length(); // only for debuging
	FBullCowCount BullCowCount;

	// incrimenting bulls and cows
	for (int32 i = 0; i < LENGTH; i++) {
		char characterHW = MY_HIDDEN_WORD.at(i);
		for (int32 j = 0; j < LENGTH; j++) {
			char characterI = input.at(j);
			if (characterI == characterHW) {
				if (i == j) {
					BullCowCount.Bull++;
				}
				else {
					BullCowCount.Cow++;
				}
			}
		}
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FText Guess) const 
{
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false; 
		}
		else {
			LetterSeen[Letter] = true;
		}
	} 
	return true;
}

bool FBullCowGame::IsLowerCase(FText Guess) const
{
	if (Guess == "\0") { return true; }

	for (char Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
