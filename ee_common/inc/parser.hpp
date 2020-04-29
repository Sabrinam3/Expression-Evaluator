#ifndef GUARD_parser_hpp20091201_
#define GUARD_parser_hpp20091201_

/** @file: parser.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visual C++ v120
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Parser class declaration.
	*/

#include <boost/noncopyable.hpp>
#include "token.hpp"

class Parser : boost::noncopyable {
public:
	typedef std::string string_type;
	TokenList parse( TokenList const& infixTokens );

	//Exception classes for exceptions that might occur during parsing*/

	/*Brief- Base class for exceptions in this file*/
	class XParser : public std::exception
	{
		string_type expression_;
	public:
		XParser(char const* msg) : std::exception(msg) {}
	};

	/*Mismatched parenthesis*/
	class XMismatchedParenthesis : public XParser {
	public:
		XMismatchedParenthesis() : XParser("Error: mismatched parenthesis.") {}
	};
};

/*=============================================================

Revision History
Version 1.0.0: 2014-10-31
Visual C++ 2013

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-01
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
#endif // GUARD_parser_hpp20091201_
