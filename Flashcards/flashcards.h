#ifndef _FLASHCARDS_H
#define _FLASHCARDS_H

#include <vector>
#include <string>

using namespace std;

class Flashcards{
private: 
	struct Noun{
		string word[3];
	};
	struct Verb{
		string word[8];
	};
	vector<Noun> nouns;
	vector<Verb> verbs;

public:
	Flashcards();
	void start();
	void read_files();
	void add_word();
	void add_verb();
	void add_conjugation(Verb&);
	void add_noun();
	int sort(string, int);
	void print_to_file(int);
	void read_word();
};

#endif