/*
 * speakjet_lookup.h
 *
 *  Created on: Mar 20, 2012
 *      Author: Matt Painter
 */

#ifndef SPEAKJET_LOOKUP_H_
#define SPEAKJET_LOOKUP_H_

#include <map>
#include <list>
#include <string>
#include <assert.h>
#include "utility.h"

using namespace std;

class SpeakjetLookup {
private:
	map<string, string> dictionary_lookup;
	map<string, unsigned char> code_lookup;

	void init_dictionary_lookup();
	void init_code_lookup();
public:
	SpeakjetLookup();
	string &lookup_dictionary(const string &phoneme);
	unsigned char &lookup_phoneme(const string &phoneme);
	list<unsigned char> translate(const string &phonemes);
};

#endif /* SPEAKJET_LOOKUP_H_ */
