
/*
* 
 Create the program Hangman. Prompt the player to enter a phrase.
 That phrase will be hidden by a series of dashes (excluding spaces).
 The player can then guess letters. If they guess correctly all the letters that match will be revealed.
 If they guess incorrectly, then 1 more body part will be added to the gallows.
 If they lose the gallows should look like this:

 +---+
 |   |
 |   o
 |  /|\
 |  / \
-+-

If the player loses, the phrase should be revealed.
After the game is over the player should be prompted if they want to play again.
 */

 //we need a way of storing the secret phrase
 //we need a way of storing the hidden phrase (with dashes)
 //we need a variable that holds the number of guesses left (set to 6 initially)

/*
	Step 1:
	Main
	---

	do {
		PlayGame
	} while(WanToPlayGame)

	
	Draw 
	+--+
	|  |
	|  
	|
	|
   -+-

   --------
   
   Play game
   -------
   secretPhrase = GetSecretWord()
   hiddenPhrase = MakeHiddenPhrase(secretPhrase)
   numberOfGuessesLeft = 6

   DrawBoard(hiddenPhrase)

   do {
		guess = GetGuess()
		UpdateBoard(guess, secretPhrase, hiddenPhrase, numberOfGuessesLeft)
		DrawBoard(hiddenPhrase)

   } while(IsGameOver(numberOfGuessesLeft, hiddenPhrase))

   DisplayResult(numberOfGuessesLeft, hiddenPhrase)


   GetSecretWord
   -------------

   prompt the user for the secret phrase
   get the secret phrase

   return secret phrase

   MakeHiddenPhrase(secretPhrase)
   ------------------------------

   hiddenPhrase = make new cstring given the length of the secret phrase

   for (the length of the secret phrase) {
	hiddenPhrase[i] = '-';
   }

   return hiddenPhrase

	
   GetGuess
   --------

   prompt the user for the guess
   get guess

   return guess


   UpdateBoard(guess, secretPhrase, hiddenPhrase, numberOfGuessesLeft)
   -------------------------------------------------------------------

   bool found = false;

   for (length of the secret phrase) {
	if (secretPhrase[i] == guess) {
		found = true
		hiddenPhrase[i] = secretPhrase[i] // Hello hi -> h is not uppercase from guess
	}
   }

   if(!found)
	--numberOfGuessesLeft

   return found;
	

   IsGameOver(numberOfGuessesLeft, hiddenPhrase)
   ---------------------------------------------

   boo hasDash = false

   for (length of the hiddenPhrase && !hasDash) {
	if (hiddenPhrase[i] == '-') 
	 hasDash = true
   }

   return numberOfGuessesLeft == 0 || !hasDash
   

   DisplayResult(numberOfGuessesLeft, hiddenPhrase)
   ------------------------------------------------

*/

#include <iostream>
#include <cstring>
#include <cctype>

#include "Utils.h"

using namespace std;

const int MAX_LENGTH_OF_SECRET_PHRASE = 256;
const int MAX_NUMBER_OF_GUESSES = 6;
const char* INPUT_ERROR_STRING = "Input error! Please try again.";
const char SPACE_CHARACTER = ' ';
const char DASH_CHARACTER = '-';

void PlayGame();
bool WantToPlayAgain();
bool IsGameOver(int, const char*, int);
int GetSecretPhrase(char[], int);
char* MakeHiddenPhrase(const char*, int);
void UpdateBoard(const char, char*, const char[], int, int&);
void DrawBoard(int, const char*);
char GetGuess();
void DisplayResult(const char*, int);

int main()
{
	do {
		PlayGame();
	} while (WantToPlayAgain());

	return 0;
}


void PlayGame() {
	char* optrHiddenPhrase = nullptr;
	int numberOfGuessesLeft = MAX_NUMBER_OF_GUESSES;
	char secretPhrase[MAX_LENGTH_OF_SECRET_PHRASE];

	int secretPhraseLength = GetSecretPhrase(secretPhrase, MAX_LENGTH_OF_SECRET_PHRASE);
	
	optrHiddenPhrase = MakeHiddenPhrase(secretPhrase, secretPhraseLength);

	DrawBoard(numberOfGuessesLeft, optrHiddenPhrase);
	
	do {
		char guess = GetGuess();
		UpdateBoard(guess, optrHiddenPhrase, secretPhrase, secretPhraseLength, numberOfGuessesLeft);
		DrawBoard(numberOfGuessesLeft, optrHiddenPhrase);

	} while (!IsGameOver(numberOfGuessesLeft, optrHiddenPhrase, secretPhraseLength));
	
	DisplayResult(secretPhrase, numberOfGuessesLeft);
	
	delete[] optrHiddenPhrase;
	optrHiddenPhrase = nullptr;
}

void DisplayResult(const char* secretPhrase, int numberOfGuessesLeft) {
	if (numberOfGuessesLeft > 0) {
		cout << "You got it! The word was: " << secretPhrase << endl;
	}
	else {
		cout << "You didn't get it ... The phrase was: " << secretPhrase << endl;
	}
}

bool WantToPlayAgain() {
	const char validInputs[] = {'y', 'n'};

	char response = GetCharacter("Would your like to play again? (y/n)",
								 INPUT_ERROR_STRING,
								 validInputs, 2);
	return response == 'y';
}

bool IsGameOver(int numberOfGuessesLeft, const char* noptrHiddenPhrase, int secretPhraseLength) {
	bool hasDash = false;

	for (int i = 0; i < secretPhraseLength; ++i) {
		if (noptrHiddenPhrase[i] == DASH_CHARACTER) {
			hasDash = true;
			break;
		}
	}

	return numberOfGuessesLeft == 0 || !hasDash;
}

int GetSecretPhrase(char secretPhrase[], int maxLength) {
	bool failure;
	int length = 0;
	do
	{
		failure = false;
		cout << "Please enter the secret phrase: ";
		cin.get(secretPhrase, maxLength);

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << INPUT_ERROR_STRING << endl;
		}
		else {
			length = strlen(secretPhrase);
			
			if (length == 0) {
				failure = true;
				cout << "You must be enter a word that's longer than 0 characters! Plesae try again!" << endl;
			}
		}
	} while (failure);

	return length;
}

char* MakeHiddenPhrase(const char* secretPhrase, int secretPhraseLength) {
	char* hiddenPhrase = new char[secretPhraseLength + 1]; // for null character

	for (int i = 0; i < secretPhraseLength; ++i) {
		hiddenPhrase[i] = secretPhrase[i] != SPACE_CHARACTER ? DASH_CHARACTER : SPACE_CHARACTER;
	}

	hiddenPhrase[secretPhraseLength] = '\0';

	return hiddenPhrase;
}

char GetGuess() {
	return GetCharacter("Please input your guess: ", INPUT_ERROR_STRING);
}

void UpdateBoard(const char guess, char* noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int& numberOfGuessesLeft) {
	bool found = false;

	for (int i = 0; i < secretPhraseLength; ++i) {
		if (guess == tolower(secretPhrase[i])) {
			found = true;
			noptrHiddenPhrase[i] = secretPhrase[i];
		}
	}

	if (!found)
		numberOfGuessesLeft--;
}

void DrawBoard(int numberOfGuesses, const char* noptrHiddenPhrase) {
	ClearScreen();
	
	switch (numberOfGuesses) {
		case 0: 
			cout << " +---" << endl;
			cout << " |  |" << endl;
			cout << " |  0" << endl;
			cout << " | /|\\" << endl;
			cout << " | / \\" << endl;
			cout << "-+-" << endl << endl;
 			break;
		case 1: 
			cout << " +---" << endl;
			cout << " |  |" << endl;
			cout << " |  0" << endl;
			cout << " | /|\\" << endl;
			cout << " | / " << endl;
			cout << "-+-" << endl << endl;
 			break;
		case 2: 
			cout << " +---" << endl;
			cout << " |  |" << endl;
			cout << " |  0" << endl;
			cout << " | /|\\" << endl;
			cout << " |  " << endl;
			cout << "-+-" << endl << endl;
 			break;
		case 3: 
			cout << " +---" << endl;
			cout << " |  |" << endl;
			cout << " |  0" << endl;
			cout << " | /|" << endl;
			cout << " |  " << endl;
			cout << "-+-" << endl << endl;
 			break;
		case 4: 
			cout << " +---" << endl;
			cout << " |  |" << endl;
			cout << " |  0" << endl;
			cout << " | /" << endl;
			cout << " |  " << endl;
			cout << "-+-" << endl << endl;
 			break;
		case 5: 
			cout << " +---" << endl;
			cout << " |  |" << endl;
			cout << " |  0" << endl;
			cout << " | " << endl;
			cout << " |  " << endl;
			cout << "-+-" << endl << endl;
 			break;
		case 6: 
			cout << " +---" << endl;
			cout << " |  |" << endl;
			cout << " |  " << endl;
			cout << " |  " << endl;
			cout << " |  " << endl;
			cout << "-+-" << endl << endl;
 			break;
		default:
			break;
	}

	cout << "Secret phrase: " << noptrHiddenPhrase << endl << endl;
}







