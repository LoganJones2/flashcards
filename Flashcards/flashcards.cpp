#include "flashcards.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Flashcards::Flashcards(){
	read_files();
}

void Flashcards::start(){
	string ans;
	do{
		add_word();
		cout << "Repeat? (y/n): ";
		getline(cin, ans);
	} while (toupper(ans[0]) == 'Y');
}

void Flashcards::read_files(){
	ifstream words;
	string st_temp;
	Verb v_temp;
	Noun n_temp;
	
	words.open("nouns.dat");
	while (!words.eof()){
		getline(words, st_temp);
		if (words.eof()){
			break;
		}
		stringstream stream(st_temp);
		for (int i = 0; i < 3; i++){
			getline(stream, n_temp.word[i], '\t');
		}
		nouns.push_back(n_temp);
	}
	words.close();

	words.open("verbs.dat");
	while (!words.eof()){
		getline(words, st_temp);
		if (words.eof()){
			break;
		}
		stringstream stream(st_temp);
		for (int i = 0; i < 8; i++){
			getline(stream, v_temp.word[i], '\t');
		}
		verbs.push_back(v_temp);
	}
	words.close();

}

void Flashcards::add_word(){
	enum word_type { noun, verb };
	string input;
	cout << "What type of word?\n\t0-Noun\n\t1-Verb\n\nPlease enter your selection: ";
	getline(cin, input);
	int ans = input[0] - '0';

	while (ans != noun && ans != verb){
		cout << "Invalid selection!\nWhat type of word?\n\t0-Noun\n\t1-Verb\n\nPlease enter your selection: ";
		getline(cin, input);
		ans = input[0] - '0';
	}

	if (ans == noun){
		add_noun();
		print_to_file(noun);
	}
	else if (ans == verb){
		add_verb();
		print_to_file(verb);
	}
}

void Flashcards::add_verb(){
	Verb input;
	vector<Verb>::iterator it = verbs.begin();

	cout << "Please enter the English infinitive form of the verb: ";
	getline(cin, input.word[0]);

	cout << "Please enter the German infinitive form of the verb: ";
	getline(cin, input.word[1]);

	add_conjugation(input);

	cout << sort(input.word[0], 1);
	verbs.insert(it + sort(input.word[0], 1), input);
}

void Flashcards::add_conjugation(Verb &input){
	//add conjugation beginning with singular, then plural
	cout << "Conjugate the german verb.\n\nich ";
	getline(cin, input.word[2]);

	cout << "du ";
	getline(cin, input.word[3]);

	cout << "er/sie/es ";
	getline(cin, input.word[4]);

	cout << "wir ";
	getline(cin, input.word[5]);

	cout << "ihr ";
	getline(cin, input.word[6]);

	cout << "sie ";
	getline(cin, input.word[7]);
}

void Flashcards::add_noun(){
	Noun input;
	vector<Noun>::iterator it = nouns.begin();

	cout << "Please enter the English noun: ";
	getline(cin, input.word[0]);

	cout << "Please enter the German singular noun: ";
	getline(cin, input.word[1]);

	cout << "Please enter the German plural noun: ";
	getline(cin, input.word[2]);

	cout << sort(input.word[0], 0);
	nouns.insert(it + sort(input.word[0], 0), input);

}

int Flashcards::sort(string st, int num){
	int i, size;
	string temp;
	enum word_type { noun, verb };

	if (num == noun){
		size = nouns.size();
	}
	else if (num == verb){
		size = verbs.size();
	}

	for (i = 0; i < size; i++){
		if (num == noun){
			temp = nouns[i].word[0];
		}
		else if (num == verb){
			temp = verbs[i].word[0];
		}
		for (int j = 0; j < st.length(); j++){
			if (tolower(st[j]) < tolower(temp[j])){
				//entry belings in this location
				return i;
			}
			else if (tolower(st[j]) > tolower(temp[j])){
				break;
			}
			else if (tolower(st[j]) == tolower(temp[j])){
				if (j == st.length() - 1){
					if (st.length() < temp.length()){
						return i;
					}
				}
			}
		}
	}
	//entry will be added at the final location
	return i;
}

void Flashcards::print_to_file(int num){
	//declare output fstream for adding new words to existing files.
	ofstream output;
	//enum for types of inputs/outputs
	enum type { noun, verb };
	//array holding number of items which each type should contain
	int type_size[2];
	//noun will be size 3: english, german singular, and german plural
	type_size[noun] = 3;
	//verb will be size 8: english infinitive, german infinitive, and the 6 german conjugations
	type_size[verb] = 8;

	//open both ifstreams
	if (num == noun){
		output.open("nouns.dat");

		//print the vector's contents, separated by a tab character
		for (int i = 0; i < nouns.size(); i++){
			for (int j = 0; j < type_size[num]; j++){
				output << nouns[i].word[j] << "\t";
			}
			output << endl;
		}
	}
	else if (num == verb){
		output.open("verbs.dat");
		
		//print the vector's contents, separated by a tab character
		for (int i = 0; i < verbs.size(); i++){
			for (int j = 0; j < type_size[num]; j++){
				output << verbs[i].word[j] << "\t";
			}
			output << endl;
		}
	}

	//close file
	output.close();
}