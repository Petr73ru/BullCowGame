// BullCowGame.cpp : The console game application)
// Current vidio is: 32(end)

#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// using namespace std;

// to make a code more Unreal frendly
using FText = std::string;
using int32 = int;


FBullCowGame BCGame;
FText Guess = "";

void PrintIntro();
void PlayGame();
void GetGuess();
void GetBullsAndCows();
bool AskForPlayAgain();
void GameSummary();

int main()
{
	do {
		PrintIntro();
		PlayGame();
		GameSummary();
	} while (AskForPlayAgain());

	return 0;
}

void PlayGame() {

	BCGame.Reset();
	for (int32 count = 0; count < BCGame.GetMaxTries(); count++) {
		GetGuess();
		if (BCGame.IsGameWon(Guess)) {
			return;
		}
		else {
			GetBullsAndCows();
		}
	}
	return;
}

void PrintIntro() {
	std::cout << std::endl << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "0000000000000000000000" << std::endl;
	std::cout << "0░░╦─╦╔╗╦─╔╗╔╗╔╦╗╔╗░░0" << std::endl;
	std::cout << "0░░║║║╠─║─║─║║║║║╠─░░0" << std::endl;
	std::cout << "0░░╚╩╝╚╝╚╝╚╝╚╝╩─╩╚╝░░0" << std::endl;
	std::cout << "0000000000000000000000" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}
void GetGuess() {
	EGuessStatus Status;
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << "; ";
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default: return;
		}
	} while (Status != EGuessStatus::OK);
}
void GetBullsAndCows() {
	FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
	std::cout << "Bulls = " << BullCowCount.Bull;
	std::cout << ". Cows = " << BullCowCount.Cow << "\n\n";
}
bool AskForPlayAgain() {
	std::cout << std::endl;
	std::cout << "Do you want to play again?(y/n) ";
	FText answer = "";
	std::getline(std::cin, answer);
	if (answer == "Y" || answer == "YES" || answer == "y" || answer == "yes") return true;
	return false;
}
void GameSummary() {
	if (BCGame.IsGameWon(Guess)) {
		std::cout << std::endl;
		std::cout << "WELL DONE - YOU WIN!";
	}
	else {
		std::cout << std::endl;
		std::cout << "Better luck next time!";
	}
}
