/*
 * utility.cpp
 *
 *  Created on: Mar 20, 2012
 *      Author: mattpainter
 */

#include "utility.h"

list<string> tokenise(string const& input) {
	istringstream str(input);
	istream_iterator<string> cur(str), end;
	return list<string>(cur, end);
}
