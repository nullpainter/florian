#include <iostream>
#include "dictionary.h"
#include "utility.h"
#include "speakjet_lookup.h"

SpeakjetLookup speakjet_lookup;

// TODO this should be in the speakjet class
unsigned char robot_sounds[] = { 200,201,202,203,204,205,206,207,208,209};

void Dictionary::add_word(const string &word, const string &phoneme) {
	dictionary[word] = phoneme;
}

string &Dictionary::get_phoneme(const string &word) {
	string uppercase_word = word;
	transform(uppercase_word.begin(), uppercase_word.end(), uppercase_word.begin(), ::toupper);

	return dictionary[uppercase_word];
}

unsigned char *Dictionary::translate(const string &phrase, int &num_codes) {
	list<string> tokenized_phrase = tokenise(phrase);
	unsigned char *raw_codes = (unsigned char *)malloc(BUFSIZ);
	assert(raw_codes != NULL);

	num_codes = 0;
	raw_codes[num_codes++] = 20;	// Volume
	raw_codes[num_codes++] = 127;	// Volume

	raw_codes[num_codes++] = 23;	// Bend
	raw_codes[num_codes++] = 5;		// Default

	char first_word = 1;
	for (list<string>::iterator it = tokenized_phrase.begin(); it != tokenized_phrase.end(); it++) {
		list<unsigned char> word_codes = speakjet_lookup.translate(get_phoneme(*it));

		string word = *it;

		if (isupper(word.at(0)) && !first_word) {
			raw_codes[num_codes++] = 14;	// Stress - no real difference?
		}

		// If there are no words, assign random noises
		if (word_codes.size() == 0) {
			for (int j = 0; j < rand() % 30; j++) {
				word_codes.push_back(robot_sounds[rand() % sizeof(robot_sounds)]);
			}

		}

		int num_buffers = 1;
		for (list<unsigned char>::iterator word_code_it = word_codes.begin(); word_code_it != word_codes.end(); word_code_it++) {
			if (num_codes == BUFSIZ - 1) {
				raw_codes = (unsigned char *)realloc(raw_codes, BUFSIZ * (num_buffers++));
				assert(raw_codes != NULL);
			}

			raw_codes[num_codes++] = *word_code_it;
		}

		raw_codes[num_codes++] = 000; // Insert break between words. FIXME need to take into account hyphen, full stop, etc. Also, may trash memory if reach BUFSIZ
		first_word = 0;
	}

	return raw_codes;
}

void Dictionary::load(const string &filename) {
	ifstream in;

	// Open dictionary
	in.open(filename.c_str());

	// Verify dictionary can be opened
	if (!in.is_open()) {
		string error = "Unable to open dictionary " + filename;
		cerr << error << endl;
		throw error;
	}

	string line;
	int index;
	while (in.good()) {
		getline(in, line);

		// Skip over comment lines
		if (line.size() > 3 && line.substr(0, 3) == ";;;") {
			continue;
		}

		// Extract word and phoneme from line
		index = line.find(' ');
		if (index < 0) {
			continue;
		}

		const string word = line.substr(0, index);
		const string phonemes = line.substr(index + 2, line.length());
		list<string> tokenized_phonemes = tokenise(phonemes);

		string translated_phonemes = "";
		for (list<string>::iterator it = tokenized_phonemes.begin(); it != tokenized_phonemes.end(); it++) {
			string value = speakjet_lookup.lookup_dictionary(*it);
			if (it != tokenized_phonemes.begin()) {
				value = " " + value;
			}

			translated_phonemes.append(value);
		}

		// Add word to lookup map
		add_word(word, translated_phonemes);
	}

	in.close();
}
