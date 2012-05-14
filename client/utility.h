/*
 * utility.h
 *
 *  Created on: Mar 20, 2012
 *      Author: mattpainter
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <iterator>
#include <sstream>
#include <string>
#include <list>

using namespace std;

list<string> tokenise(const string &input);

template<typename T, size_t N>
char (&array(T (&)[N]))[N];

#endif /* UTILITY_H_ */
