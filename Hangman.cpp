// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include<stdlib.h>
#include<time.h>


using namespace std;

void clearscreen() {
	for (int i = 0; i < 50; i++) {
		cout << endl;
	}
}


class Hangman {
public:
	Hangman(): word(""), incorrect(0), guess(""), difficulty(0), length(0), guessed("") {
	}
	Hangman(string w, int i, string g, int wa, int l,string gu) : word(w), incorrect(i), guess(g), difficulty(wa), length(l), guessed(gu) {}
	void save() {
		//save
		ofstream outFS;
		outFS.open("save.txt");
		outFS << word<<endl;
		outFS << incorrect << endl;
		outFS << guess << endl;
		outFS << difficulty << endl;
		outFS << length << endl;
		outFS << guessed << endl;
		outFS.close();
	}

	bool checkGuess(char g) {
		bool parsingString = false;
		for (int i = 0; i < guessed.size(); i++) {
			if (!parsingString) {
				if (guessed[i] == '"')
					parsingString = true;
				else
					if (g == guessed[i])
						return true;
			}
			else {
				if (guessed[i] == '"')
					parsingString = false;
			}
		}
		return false;
	}

	bool checkString(string g) {
		bool parsingString = false;
		string temp = "";
		for (int i = 0; i < guessed.size(); i++) {
			if (!parsingString) {
				if (guessed[i] == '"')
					parsingString = true;

			}
			else {
				if (guessed[i] == '"') {
					parsingString = false;
					if (g == temp) {
						return true;
					}
					else {
						temp = "";
					}
				}
				else {
					temp = temp + guessed[i];
				}
			}
		}
		return false;
	}

	void printHangman() {

		switch (incorrect) {
		case 0: {
			    cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |                           \n"
				"\t\t    |                           \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
			break; 
		}

		case 1: {
			cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |                           \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
			break; }
		case 2: {
			cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |      |                    \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
			break; 
		}
		case 3: {
			cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |      |\\                   \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
			break; 
		}
		case 4: {
			cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |     /|\\                   \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
			break; 
		}
		case 5: {
			cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |     /|\\                   \n"
				"\t\t    |     /                     \n"
				"\t\t ___|___                        \n\n\n";
			break; 
		}
		case 6: {
			cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |     /|\\                   \n"
				"\t\t    |     / \\                   \n"
				"\t\t ___|___                        \n\n\n";
			break; 
		}
		}
	}
	virtual void play() {
		bool win = false;
		bool foundletter = false;
		bool willsave = false;
		
		string temp;
		while (true) {
			if (willsave) {
				cout << "Your progress has been saved." << endl;
				save();
				break;
			}
			if (win) {
				cout << "You win! The word was " << word << endl;
				clearscreen();
				break;
			}

			printHangman();

			if (incorrect == 6)
			{
				cout << "You lose! The word was: " << word << endl;
				break;
			}
			cout << "Word: " << guess << endl << "Guesses: " << guessed << endl;
			while (true) {
				foundletter = false;
				cout << "Your guess or ! to save and exit: ";
				cin >> temp;
				cout << endl;
				if (temp.empty()){
					cout << "Enter a letter or word!" << endl;
				}
				else if (temp.size() > 1) {
					if (word == temp) {
						win = true;
						break;
					}
					else {
						clearscreen();
						cout << temp << " was not the word." << endl;
						if (!checkString(temp)) {
							incorrect++;
							guessed = "\"" + temp + "\"" + " " + guessed;
						}
						break;
					}
				}
				else {
					if (isdigit(temp[0])) {
						cout << "Enter a letter or a word!" << endl;
					}
					
					else if (temp[0] == '!') {
						willsave = true;
						clearscreen();
						break;
					}
					else {
						for (int i = 0; i < length; i++) {
							if (word[i] == temp[0]) {
								foundletter = true;
								guess[i] = temp[0];
							}
						}
						if (foundletter) {
							clearscreen();
							cout << "There is a(n) " << temp[0] << " in the word." << endl;
							if (word == guess)
								win = true;
							if (!checkGuess(temp[0]))
								guessed = temp + " " + guessed;
							break;
						}
						else {
							clearscreen();
							cout << "There is no " << temp[0] << " in the word." << endl;
	
							if (!checkGuess(temp[0])) {
								incorrect++;
								guessed = temp + " " + guessed;
							}

							break;
						}
					}
				}
			}
		}
	}
    void openDictionary(int difficulty) {
		ifstream inFile;
		switch (difficulty) {
		case 1:
		{
			inFile.open("easy.txt");
			break;
		}
		case 2:
		{
			inFile.open("medium.txt");
			break;
		}
		case 3:
		{
			inFile.open("hard.txt");
			break;
		}

		}

		string temp;
		for (int i = 0; i < 10; i++) {
			getline(inFile, temp);
			dictionary[i] = temp;
		}
	}

	void pickWord() {
		//generate random int
		int num;
		srand(time(NULL));
		num = rand() % 10;
		word = dictionary[num];
		length = word.size();
		for (int i = 0; i < length; i++) {
			guess = guess + "-";
		}
	}
	string getWord() { return word; }
	void setIncorrect(int inc) { incorrect = inc; }
	void setDif(int dif) { difficulty = dif; }
protected:
	string word;
	string guess;
	string guessed;
	string dictionary[10];
	int length;
	int difficulty;
	int incorrect;
};

class Easy: public Hangman{
public:
	Easy() :Hangman() {
		
		openDictionary(1);
		pickWord();
		setDif(1);

	}

};

class Medium : public Hangman {
public:
	Medium() :Hangman() {
		openDictionary(2);
		pickWord();
		setDif(2);
		setIncorrect(1);
	}

};
class Hard :public Hangman {
public:
	Hard() :Hangman() {
		openDictionary(3);
		setDif(3);
		pickWord();
	}
	Hard(string w, int i, string g, int wa, int l, string gu) : Hangman(w, i, g, wa, l, gu) {}

	void play() {
		bool win = false;
		bool foundletter = false;
		bool willsave = false;

		string temp;
		while (true) {
			if (willsave) {
				clearscreen();
				cout << "Your progress has been saved." << endl;
				save();
				break;
			}
			if (win) {
				clearscreen();
				cout << "You win! The word was " << word << endl;
				break;
			}

			printHangman();

			if (incorrect == 6)
			{
				clearscreen();
				cout << "You lose! The word was: " << word << endl;
				break;
			}
			cout << "Word: " << guess << endl << "Guesses: " << guessed << endl;
			while (true) {
				foundletter = false;
				cout << "Your guess or ! to save and exit: ";
				cin >> temp;
				cout << endl;
				if (temp.empty())
					cout << "Enter a letter or word!" << endl;
				else if (temp.size() > 1) {
					if (word == temp) {
						win = true;
						break;
					}
					else {
						clearscreen();
						cout << temp << " was not the word." << endl;
						if (!checkString(temp)) {
							incorrect++;
							guessed = "\"" + temp + "\"" + " " + guessed;
						}
						break;
					}
				}
				else {
					if (isdigit(temp[0]))
						cout << "Enter a letter or a word!" << endl;
					else if (temp[0] == '!') {
						willsave = true;
						break;
					}
					else {
						for (int i = 0; i < length; i++) {
							if (word[i] == temp[0]) {
								foundletter = true;
								guess[i] = temp[0];
							}
						}
						if (foundletter) {
							clearscreen();
							cout << "There is a(n) " << temp[0] << " in the word." << endl;
							if (word == guess)
								win = true;
							if (!checkGuess(temp[0])) {
								incorrect++;
								guessed = temp + " " + guessed;
							}
							break;
						}
						else {
							clearscreen();
							cout << "There is no " << temp[0] << " in the word." << endl;
							if (!checkGuess(temp[0])) {
								incorrect++;
								guessed = temp + " " + guessed;
							}

							break;
						}
					}
				}
			}
		}
	}

};


int selectDif() {
	int selection = 0;
	string select;
	while (true) {
		clearscreen();
		cout << "Select a difficulty." << endl << "\n" <<
			"(1) Easy: 5 letter words, 6 incorrect guesses allowed." << endl << "(2) Medium: 5-8 letter words, 5 incorrect guesses allowed." << endl << "(3) Hard: 8+ letter words, 6 guesses allowed" << endl;
		cin >> select;
		clearscreen();
		if (select == "1" || select == "2" || select == "3")
			selection = stoi(select);

		if (selection == 1 || selection == 2 || selection == 3)
			break;
		else
			cout << "Enter a number between 1 and 3." << endl;
	}
	return selection;
}

void load(Hangman *&game) {
	ifstream inFS;
	inFS.open("save.txt");
	if (!inFS.is_open()) {
		cout << "Save does not exist." << endl;

	}
	// Hangman(): word(""), incorrect(0), guess(""), difficulty(0), length(0), guessed("")
	else {
		string word, guess, guessed, temp;
		int incorrect, difficulty, length;
		for (int i = 0; getline(inFS, temp); i++) {
			switch (i) {
			case 0:
				word = temp;
				break;
			case 1:
				incorrect = stoi(temp);
				break;
			case 2:
				guess = temp;
				break;
			case 3:
				difficulty = stoi(temp);
				break;
			case 4:
				length = stoi(temp);
				break;
			case 5:
				guessed = temp;
				break;
			default:
				cout << "Error reached!";
				break;
			}
		}
		inFS.close();
		switch (difficulty) {
		case 3:
		{
			game = new Hard(word, incorrect, guess, difficulty, length, guessed);
			game->play();
			break;
		}
		default:
			game = new Hangman(word, incorrect, guess, difficulty, length, guessed);
			game->play();
			break;
		}
		
	}

}

int main()
{
	int select;
	string selection;
	Hangman* game;
	while (true) {
		cout << "-----Hangman-----" << endl;
		cout << "Select (1) Play Game" << endl;
		cout << "Select (2) Load Saved Game" << endl;
		cout << "Select (3) Exit Game" << endl;
		cin >> selection;
		clearscreen();
		if (selection == "1" || selection == "2" || selection == "3") {
			select = stoi(selection);
		}
		else
			select = 4;
		switch (select) {
		case 1:
		{
			select = selectDif();
			switch (select) {
			case 1:
			{
				game = new Easy;
				break;
			}
			case 2:
			{
				game = new Medium;
				break;
			}
			case 3:
			{
				game = new Hard;
				break;
			}
			default:
			{
				game = new Hangman;
				break;
			}
			}
			game->play();
			delete game;
			break;
		}

		case 2:
		{
			load(game);
			break;
		}
		case 3:
			return 0;
		default:
		{
			cout << "Enter a number between one and three" << endl;
		}

		}

	}
	


	
	

}

