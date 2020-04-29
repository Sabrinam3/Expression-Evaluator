/** @file: token.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.0.0
	@note Compiles under Visual C++ v110
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Operation class implemenation.
	*/

#include "../inc/token.hpp"
using namespace std;

/*@Brief returns a token and it's type as a string
@Returns string*/

Token::string_type	Token::to_string() const {
	return string_type("<") + string_type(typeid(*this).name()).substr(6) + string_type(">");
}

/*=============================================================

Revision History

Version 0.0.0: 2012-11-13
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


