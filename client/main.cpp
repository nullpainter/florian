#include <iostream>
#include <string>
#include <list>
#include "dictionary.h"
#include "math.h"
//#include "hid.h"

const string DICTIONARY_FILENAME = "cmudict.0.7a";

extern "C" int rawhid_open(int max, int vid, int pid, int usage_page, int usage);
extern "C" int rawhid_recv(int num, void *buf, int len, int timeout);
extern "C" int rawhid_send(int num, void *buf, int len, int timeout);
extern "C" void rawhid_close(int num);

int main(int argc, char *argv[]) {
	Dictionary dictionary;

	if (argc != 2) {
		cerr << "Usage: ./florian \"words to speak\"" << endl;
		return EXIT_FAILURE;
	}

	try {
		dictionary.load(DICTIONARY_FILENAME);
	} catch (...) {
		return EXIT_FAILURE;
	}

	// C-based example is 16C0:0480:FFAB:0200
	int r = rawhid_open(1, 0x16C0, 0x0480, 0xFFAB, 0x0200);
	if (r <= 0) {
		// Arduino-based example is 16C0:0486:FFAB:0200
		r = rawhid_open(1, 0x16C0, 0x0486, 0xFFAB, 0x0200);
		if (r <= 0) {
			cout << "Florian not found!" << endl;
			return EXIT_FAILURE;
		}
	}

	int num_codes;
	unsigned char *raw_codes = dictionary.translate(argv[1], num_codes);

	// Add special terminating byte to let Teensy code know the buffer has
	// ended. This is a bit manky. Possibly better to send up front in a
	// specified binary structure

	// FIXME this trashes one byte of memory if num_codes == BUF_SIZE
	raw_codes[num_codes] = 255;	
	int num_bytes = rawhid_send(0, raw_codes, num_codes+1, 100);
	free(raw_codes);

	if (num_bytes < 0) {
		cerr << "Error communicating with Florian." << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

