/**
 * @file src/demanglertool/demangler.cpp
 * @brief Demangler tool.
 * @copyright (c) 2017 Avast Software, licensed under the MIT license
 */

#include <cstring>
#include <iostream>

#include "retdec/demangler/demangler.h"

using namespace std;
using ItaniumDemangler = retdec::demangler::ItaniumDemangler;
using MicrosoftDemangler = retdec::demangler::MicrosoftDemangler;
using BorlandDemangler = retdec::demangler::BorlandDemangler;

/**
 * @brief String constant containing help.
 */
const string helpmsg =
	"Demangler tool.\n"
	"\n"
	"Usage:\n"
	"\t'demangler -h | Show this help.\n"
	"\t'demangler mangledname | Attempt to demangle a name using all available demanglers and print result if succeded.\n";

/**
 * @brief Main function of the Demangler tool.
 * @param argc Argument count.
 * @param argv Arguments.
 */
int main(int argc, char *argv[]) {
	auto dem_gcc = std::make_unique<ItaniumDemangler>();
	auto dem_ms =  std::make_unique<MicrosoftDemangler>();
	auto dem_borland = std::make_unique<BorlandDemangler>();

	string demangledGcc;
	string demangledMs;
	string demangledBorland;

	//no argument -- print help
	if (argc <= 1) {
		cout << helpmsg;
		return 0;
	}

	//first argunment contains help request
	else {
		//print help
		if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0) {
			cout << helpmsg;
			return 0;
		}
	}

	//process all mangled arguments
	for (unsigned int i = 1; i < static_cast<unsigned int>(argc); i++) {
		//demangle using all available demanglers
		demangledGcc = dem_gcc->demangleToString(argv[i]);
		demangledMs = dem_ms->demangleToString(argv[i]);
		demangledBorland = dem_borland->demangleToString(argv[i]);

		if (!demangledGcc.empty()) { cout << "gcc: " << demangledGcc << endl; }
		if (!demangledMs.empty()) { cout << "ms: " << demangledMs << endl; }
		if (!demangledBorland.empty()) { cout << "borland: " << demangledBorland << endl; }
	} //for

	return 0;
}
