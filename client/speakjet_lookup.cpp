/*
 * speakjet_lookup.cpp
 *
 *  Created on: Mar 20, 2012
 *      Author: Matt Painter
 */

#include "speakjet_lookup.h"

SpeakjetLookup::SpeakjetLookup() {

	init_dictionary_lookup();
	init_code_lookup();
}

void SpeakjetLookup::init_dictionary_lookup() {
	dictionary_lookup["AA0"] = "AW";
	dictionary_lookup["AA1"] = "AW";
	dictionary_lookup["AA2"] = "AW";
	dictionary_lookup["AE0"] = "AY";
	dictionary_lookup["AE1"] = "AY";
	dictionary_lookup["AE2"] = "AY";
	dictionary_lookup["AH0"] = "EY";
	dictionary_lookup["AH1"] = "UX";
	dictionary_lookup["AH2"] = "UX";
	dictionary_lookup["AO0"] = "OH";
	dictionary_lookup["AO1"] = "AW AW";
	dictionary_lookup["AO2"] = "AW AW";
	dictionary_lookup["AW0"] = "OW";
	dictionary_lookup["AW1"] = "AXUW";
	dictionary_lookup["AW2"] = "AXUW";
	dictionary_lookup["AY0"] = "OHIH";
	dictionary_lookup["AY1"] = "OHIH";
	dictionary_lookup["AY2"] = "OHIH";
	dictionary_lookup["B"] = "EB";
	dictionary_lookup["CH"] = "CH";
	dictionary_lookup["D"] = "ED";
	dictionary_lookup["DH"] = "DH";
	dictionary_lookup["EH0"] = "EH";
	dictionary_lookup["EH1"] = "EH";
	dictionary_lookup["EH2"] = "EH";
	dictionary_lookup["ER0"] = "AXRR";
	dictionary_lookup["ER1"] = "AXRR";
	dictionary_lookup["ER2"] = "AXRR";
	dictionary_lookup["EY0"] = "EY";
	dictionary_lookup["EY1"] = "EYIY";
	dictionary_lookup["EY2"] = "EYIY";
	dictionary_lookup["F"] = "FF";
	dictionary_lookup["G"] = "GE";
	dictionary_lookup["HH"] = "HE";
	dictionary_lookup["IH0"] = "IH";
	dictionary_lookup["IH1"] = "IH";
	dictionary_lookup["IH2"] = "IH IH";
	dictionary_lookup["IY0"] = "IY";
	dictionary_lookup["IY1"] = "IY IY";
	dictionary_lookup["IY2"] = "IY IY IY";
	dictionary_lookup["JH"] = "JH";
	dictionary_lookup["K"] = "KE"; // EK?
	dictionary_lookup["L"] = "LE";
	dictionary_lookup["M"] = "MM";
	dictionary_lookup["N"] = "NE";
	dictionary_lookup["NG"] = "NGE";
	dictionary_lookup["OW0"] = "OH";
	dictionary_lookup["OW1"] = "OW OW";
	dictionary_lookup["OW2"] = "OW OW";
	dictionary_lookup["OY0"] = "OWIY";
	dictionary_lookup["OY1"] = "OWIY";
	dictionary_lookup["OY2"] = "OWIY";
	dictionary_lookup["P"] = "PO"; // PE?
	dictionary_lookup["R"] = "RR";
	dictionary_lookup["S"] = "SE";
	dictionary_lookup["SH"] = "SH";
	dictionary_lookup["T"] = "TT";
	dictionary_lookup["TH"] = "DH";
	dictionary_lookup["UH0"] = "UH";
	dictionary_lookup["UH1"] = "UH UH";
	dictionary_lookup["UH2"] = "UH UH";
	dictionary_lookup["UW0"] = "UW";
	dictionary_lookup["UW1"] = "UW UW";
	dictionary_lookup["UW2"] = "UW UW UW";
	dictionary_lookup["V"] = "VV";
	dictionary_lookup["W"] = "WW";
	dictionary_lookup["Y"] = "IYEH";
	dictionary_lookup["Z"] = "ZZ";
	dictionary_lookup["ZH"] = "ZH";
}

void SpeakjetLookup::init_code_lookup() {
	code_lookup["P0"] = 0; // Pauses
	code_lookup["P1"] = 1;
	code_lookup["P2"] = 2;
	code_lookup["P3"] = 3;
	code_lookup["P4"] = 4;
	code_lookup["P5"] = 5;
	code_lookup["P6"] = 6;
	code_lookup["FAST"] = 7; // Play next phoneme with double speed
	code_lookup["SLOW"] = 8; // Play next phoneme 1.5 times slower
	code_lookup["STRS"] = 9; // Play next phoneme with a bit stress in the voice
	code_lookup["RELX"] = 10; // Relax again...
	code_lookup["IY"] = 128;
	code_lookup["IH"] = 129;
	code_lookup["EY"] = 130;
	code_lookup["EH"] = 131;
	code_lookup["AY"] = 132;
	code_lookup["AX"] = 133;
	code_lookup["UX"] = 134;
	code_lookup["OH"] = 135;
	code_lookup["AW"] = 136;
	code_lookup["OW"] = 137;
	code_lookup["UH"] = 138;
	code_lookup["UW"] = 139;
	code_lookup["MM"] = 140;
	code_lookup["NE"] = 141;
	code_lookup["NO"] = 142;
	code_lookup["NGE"] = 143;
	code_lookup["NGO"] = 144;
	code_lookup["LE"] = 145;
	code_lookup["LO"] = 146;
	code_lookup["WW"] = 147;
	code_lookup["RR"] = 148;
	code_lookup["IYRR"] = 149;
	code_lookup["EYRR"] = 150;
	code_lookup["AXRR"] = 151;
	code_lookup["AWRR"] = 152;
	code_lookup["OWRR"] = 153;
	code_lookup["EYIY"] = 154;
	code_lookup["OHIY"] = 155;
	code_lookup["OWIY"] = 156;
	code_lookup["OHIH"] = 157;
	code_lookup["IYEH"] = 158;
	code_lookup["EHLL"] = 159;
	code_lookup["IYUW"] = 160;
	code_lookup["AXUW"] = 161;
	code_lookup["IHWW"] = 162;
	code_lookup["AYWW"] = 163;
	code_lookup["OWWW"] = 164;
	code_lookup["JH"] = 165;
	code_lookup["VV"] = 166;
	code_lookup["ZZ"] = 167;
	code_lookup["ZH"] = 168;
	code_lookup["DH"] = 169;
	code_lookup["BE"] = 170;
	code_lookup["BO"] = 171;
	code_lookup["EB"] = 172;
	code_lookup["OB"] = 173;
	code_lookup["DE"] = 174;
	code_lookup["DO"] = 175;
	code_lookup["ED"] = 176;
	code_lookup["OD"] = 177;
	code_lookup["GE"] = 178;
	code_lookup["GO"] = 179;
	code_lookup["EG"] = 180;
	code_lookup["OG"] = 181;
	code_lookup["CH"] = 182;
	code_lookup["HE"] = 183;
	code_lookup["HO"] = 184;
	code_lookup["WH"] = 185;
	code_lookup["FF"] = 186;
	code_lookup["SE"] = 187;
	code_lookup["SO"] = 188;
	code_lookup["SH"] = 189;
	code_lookup["TH"] = 190;
	code_lookup["TT"] = 191;
	code_lookup["TU"] = 192;
	code_lookup["TS"] = 193;
	code_lookup["KE"] = 194;
	code_lookup["KO"] = 195;
	code_lookup["EK"] = 196;
	code_lookup["OK"] = 197;
	code_lookup["PE"] = 198;
	code_lookup["PO"] = 199;
	code_lookup["R0"] = 200;
	code_lookup["R1"] = 201;
	code_lookup["R2"] = 202;
	code_lookup["R3"] = 203;
	code_lookup["R4"] = 204;
	code_lookup["R5"] = 205;
	code_lookup["R6"] = 206;
	code_lookup["R7"] = 207;
	code_lookup["R8"] = 208;
	code_lookup["R9"] = 209;
	code_lookup["A0"] = 210;
	code_lookup["A1"] = 211;
	code_lookup["A2"] = 212;
	code_lookup["A3"] = 213;
	code_lookup["A4"] = 214;
	code_lookup["A5"] = 215;
	code_lookup["A6"] = 216;
	code_lookup["A7"] = 217;
	code_lookup["A8"] = 218;
	code_lookup["A9"] = 219;
	code_lookup["B0"] = 220;
	code_lookup["B1"] = 221;
	code_lookup["B2"] = 222;
	code_lookup["B3"] = 223;
	code_lookup["B4"] = 224;
	code_lookup["B5"] = 225;
	code_lookup["B6"] = 226;
	code_lookup["B7"] = 227;
	code_lookup["B8"] = 228;
	code_lookup["B9"] = 229;
	code_lookup["C0"] = 230;
	code_lookup["C1"] = 231;
	code_lookup["C2"] = 232;
	code_lookup["C3"] = 233;
	code_lookup["C4"] = 234;
	code_lookup["C5"] = 235;
	code_lookup["C6"] = 236;
	code_lookup["C7"] = 237;
	code_lookup["C8"] = 238;
	code_lookup["C9"] = 239;
	code_lookup["D0"] = 240;
	code_lookup["D1"] = 241;
	code_lookup["D2"] = 242;
	code_lookup["D3"] = 243;
	code_lookup["D4"] = 244;
	code_lookup["D5"] = 245;
	code_lookup["D6"] = 246;
	code_lookup["D7"] = 247;
	code_lookup["D8"] = 248;
	code_lookup["D9"] = 249;
	code_lookup["D10"] = 250;
	code_lookup["D11"] = 251;
	code_lookup["M0"] = 252;
	code_lookup["M1"] = 253;
	code_lookup["M2"] = 254;
}

string &SpeakjetLookup::lookup_dictionary(const string &phoneme) {
	return dictionary_lookup[phoneme];
}

unsigned char &SpeakjetLookup::lookup_phoneme(const string & phoneme) {
	return code_lookup[phoneme];
}

#include <iostream>

list<unsigned char> SpeakjetLookup::translate(const string &phonemes) {
	list<string> tokenized_phonemes = tokenise(phonemes);
	list<unsigned char> codes;

	string translated_phonemes = "";

	for (list<string>::iterator it = tokenized_phonemes.begin(); it != tokenized_phonemes.end(); it++) {
		codes.push_back(lookup_phoneme(*it));
	}

	return codes;
}
