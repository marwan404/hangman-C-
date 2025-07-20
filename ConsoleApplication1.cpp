#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <cctype>
#include <numeric>
#include <algorithm>
using namespace std;

void displayMan(int tries, map<int, vector<string>> hangman) {
	cout << "**************************" << endl;

	vector<string>& lines = hangman[tries]; // gets the hangman level based on current number of tries
	//outpusts hangmans body
	for (int i = 0; i < lines.size(); i++) {
		cout << lines[i] << endl;
	}

	cout << "**************************" << endl;
}

void displayHint(string hint) {
	// outputs the underscores 
	for (int i = 0; i < hint.length(); ++i) {
		cout << hint[i];
		if (i != hint.length() - 1) cout << " ";
	}
	cout << endl;
}

void displayAnswer(string answer) {
	//outputs the letters
	for (int i = 0; i < answer.length(); ++i) {
		cout << answer[i];
		if (i != answer.length() - 1) cout << " ";
	}
	cout << endl;
}

void program(string answer, map<int,vector<string>> hangman) {

	//dynamic array to store the underscoers based on the length of the word picked
	vector<string> hint;
	hint.push_back(string(answer.length(), '_'));
	//convert vector into a string
	string hintstr = accumulate(hint.begin(), hint.end(), string(""));

	set<char> guessedLetters;
	int tries = 0;
	bool is_running = true;

	while (is_running) {

		displayMan(tries, hangman);
		displayHint(hintstr);

		string guess;

		cout << "Guess a letter: ";
		cin >> guess;
		cout << endl;

		//lower cases all input from guess
		transform(guess.begin(), guess.end(), guess.begin(),::tolower);

		// checks if the user inputed more than one letter or inputed a digit
		if (guess.length() != 1 || isdigit(guess[0]) == true) {
			cout << "invalid input";
			continue;
		}

		char letter = guess[0];

		// checks if the letter is in the guessedletters set
		if (guessedLetters.count(letter)) {
			cout << "You've already guessed '" << letter << "'!\n";
			continue;
		}

		guessedLetters.insert(letter); // inserts letter in guessedletters set

		//checks if the letter inputed is in the answer
		if (answer.find(letter) != string::npos) {
			for (int i = 0; i <= answer.length(); i++) {
				if (answer[i] == letter) {
					hintstr[i] = letter;
				}
			}
		}

		else {
			tries += 1;
		}

		// if the tries are over and the hangmans body is complete, the game is lost
		if (tries >= 6) {
			displayMan(tries, hangman);
			displayAnswer(answer);
			cout << "You loose" << endl;
			is_running = false;
		}

		// if there are no longer underscores in the hint the game is won
		if (hintstr.find("_") == string::npos) {
			displayMan(tries, hangman);
			displayAnswer(answer);
			cout << "You Win" << endl;
			is_running = false;
		}
	}
}

int main() {
	srand(time(0));

	//random word picker
	vector <string> words = {"apple","goat","slipper","food","ball"};
	string answer = words[rand() % words.size()];
	
	//this is the hangman
	map<int, vector<string>> hangman;
	hangman[0] = { "   ", "   ", "   " };
	hangman[1] = { " o ", "   ", "   " };
	hangman[2] = { " o ", " | ", "   " };
	hangman[3] = { " o ", "/| ", "   " };
	hangman[4] = { " o ", "/|\\", "   " };
	hangman[5] = { " o ", "/|\\", "/  " };
	hangman[6] = { " o ", "/|\\", "/ \\" };

	//the entire programs code
	program(answer, hangman);

	return 0;
}