/*
 * dictionary.h
 *
 *  Created on: Mar 20, 2012
 *      Author: Matt Painter
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <assert.h>

using namespace std;

class Dictionary {
private:
	map<string, string> dictionary;

public:
	void add_word(const string &word, const string &phoneme);
	string &get_phoneme(const string &phoneme);
	void load(const string &filename);
	unsigned char *translate(const string &phrase, int &num_codes);
};

#endif /* DICTIONARY_H_ */
