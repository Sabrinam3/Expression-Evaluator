/**	@file: UI_Prototype_main.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2016-10-29
	@note Compiles under Visual C++ 14.0

	@brief Demonstrates and ee user interface.
	*/

#include <iostream>
#include <string>
using namespace std;

int main() {
	cout << "Expression Evaluator, (c) 1998-2017 Garth Santor\n";
	for (unsigned count = 0; ; ++count) {
		cout << "> ";
		string command;
		if (!getline(cin, command) || command.empty())
			break;

		cout << "[" << count << "] = " << 42 << endl;
	}
}


/*=============================================================

Revision History

Version 1.0.0: 2016-10-29
C++ 11 validated

Version 0.0.2: 2014-10-29
Updated copyright.

Version 0.0.1: 2012-11-13
Updated copyright.

Version 0.0.0: 2009-11-26
Alpha release.

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han of Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/