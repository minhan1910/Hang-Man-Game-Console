
#include <iostream>
#include "Utils.h"
#include <cctype>

using namespace std;

char GetCharacter(const char* prompt, const char* error) {
	bool failure;
	char input;

	do
	{
		failure = false;
		cout << prompt;
		cin >> input;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			failure = true;
			cout << error << endl;
		}
		else {
			cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input)) {
				input = tolower(input);
			}
			else {
				cout << error << endl;
				failure = true;
			}
		}
	} while (failure);

	return input;
}

char GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength) {
	bool failure;
	char input;

	do
	{
		failure = false;
		cout << prompt << endl;
		cin >> input;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			failure = true;
			cout << error << endl;
		}
		else {
			cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input)) {
				input = tolower(input);

				for (int i = 0; i < validInputLength; ++i) {
					if (validInput[i] == input) {
						return input;
					}
				}

				cout << error << endl;
				failure = true;
			}
		}
	} while (failure);

	return input;
}

void ClearScreen() {
	system("cls"); // for windows only
}

void WaitForKeyPress() {
	system("pause"); // Windows only
	//system("read -n 1 -s -p \"Press any key to continue...\";echo"); //Mac
}
