/** @file: tokenizer.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.3.0
	@date 2017-11-23
	@note Compiles under Visual C++ 15.4.4
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Tokenizer class implementation.
	*/

#include "../inc/tokenizer.hpp"
#include "../inc/boolean.hpp"
#include "../inc/function.hpp"
#include "../inc/integer.hpp"
#include "../inc/operator.hpp"
#include "../inc/pseudo_operation.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"

#include <exception>
#include <limits>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

/** Default constructor loads the keyword dictionary. */
Tokenizer::Tokenizer() {
keywords_["abs"]     = keywords_["Abs"]		= keywords_["ABS"]		= make<Abs>();
keywords_["Arccos"] = keywords_["arccos"] = keywords_["ARCCOS"] = make<Arccos>();
keywords_["Arcsin"] = keywords_["arcsin"] = keywords_["ARCSIN"] = make<Arcsin>();
keywords_["Arctan"] = keywords_["arctan"] = keywords_["ARCTAN"] = make<Arctan>();
keywords_["Ceil"] = keywords_["ceil"] = keywords_["CEIL"] = make<Ceil>();
keywords_["Cos"] = keywords_["cos"] = keywords_["COS"] = make<Cos>();
keywords_["Exp"] = keywords_["exp"] = keywords_["EXP"] = make<Exp>();
keywords_["Floor"] = keywords_["floor"] = keywords_["FLOOR"] = make<Floor>();
keywords_["Lb"] = keywords_["lb"] = keywords_["LB"] = make<Lb>();
keywords_["Ln"] = keywords_["ln"] = keywords_["LN"] = make<Ln>();
keywords_["Log"] = keywords_["log"] = keywords_["LOG"] = make<Log>();
keywords_["Result"] = keywords_["result"] = keywords_["RESULT"] = make<Result>();
keywords_["Sin"] = keywords_["sin"] = keywords_["SIN"] = make<Sin>();
keywords_["Sqrt"] = keywords_["sqrt"] = keywords_["SQRT"] = make<Sqrt>();
keywords_["Tan"] = keywords_["tan"] = keywords_["TAN"] = make<Tan>();
keywords_["Fib"] = keywords_["fib"] = keywords_["FIB"] = make<Fib>();
keywords_["Pel"] = keywords_["pel"] = keywords_["PEL"] = make<Pel>();
keywords_["Syl"] = keywords_["syl"] = keywords_["SYL"] = make<Syl>();
keywords_["Arctan2"] = keywords_["arctan2"] = keywords_["ARCTAN2"] = make<Arctan2>();
keywords_["Max"] = keywords_["max"] = keywords_["MAX"] = make<Max>();
keywords_["Min"] = keywords_["min"] = keywords_["MIN"] = make<Min>();
keywords_["Pow"] = keywords_["pow"] = keywords_["POW"] = make<Pow>();
keywords_["Mod"] = keywords_["mod"] = keywords_["MOD"] = make<Modulus>();
keywords_["Pi"] = keywords_["pi"] = keywords_["PI"] = make<Pi>();
keywords_["E"] = keywords_["e"] = make<E>();
keywords_["True"] = keywords_["true"] = keywords_["TRUE"] = make<Boolean>(true);
keywords_["False"] = keywords_["false"] = keywords_["FALSE"] = make<Boolean>(false);
keywords_["Not"] = keywords_["not"] = keywords_["NOT"] = make<Not>();
keywords_["And"] = keywords_["and"] = keywords_["AND"] = make<And>();
keywords_["Or"] = keywords_["or"] = keywords_["OR"] = make<Or>();
keywords_["Xor"] = keywords_["xor"] = keywords_["XOR"] = make<Xor>();
keywords_["Nand"] = keywords_["nand"] = keywords_["NAND"] = make<Nand>();
keywords_["Nor"] = keywords_["nor"] = keywords_["NOR"] = make<Nor>();
keywords_["Xnor"] = keywords_["xnor"] = keywords_["XNOR"] = make<Xnor>();
}

/*@Brief- accumules a string identifier and returns a variable or token
@return Token::pointer_type of appropriate type
	@param currentChar [in,out] an iterator to the current character.  Assumes that the currentChar is pointing to a digit.
	@param expression [in] the expression being scanned.*/

Token::pointer_type Tokenizer::_get_identifier(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	// accumulate identifier
	string_type ident;
	do
		ident += *currentChar++;
	while (currentChar != end(expression) && isalnum(*currentChar));

	// check for predefined identifier
	dictionary_type::iterator iter = keywords_.find(ident);
	if (iter != end(keywords_))
		return iter->second;
	//The identifier has not been found in the keywords dictionary. See if a pre-existing variable exists with the name
	else
	{
		dictionary_type::iterator iter = variables_.find(ident);
		if (iter != end(variables_))
		{
			//Return the pre-existing variable pointer
			return variables_[ident];
		}
		else
		{
			//make a new variable, add to the map, and return
			variables_[ident] = make<Variable>();
			return variables_[ident];
		}
			
	}
	//a bad character has been found, throw exception
	throw XBadCharacter(expression, currentChar - begin(expression));
}


/** Get a number token from the expression.
	@return One of BinaryInteger, Integer, or Real.
	@param currentChar [in,out] an iterator to the current character.  Assumes that the currentChar is pointing to a digit.
	@param expression [in] the expression being scanned.
*/
Token::pointer_type Tokenizer::_get_number(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	assert(isdigit(*currentChar) && "currentChar must pointer to a digit");
	//String stream to accumulate the numbers
	stringstream ss;
	//Bool that will flip if a decimal is found
	bool real = false;
	//Bool that will flip if binary integer is found
	bool binary = false;
	
	while ((!isspace(*currentChar) && isdigit(*currentChar)) || *currentChar == '.' || *currentChar == '.') 
	{
		if(isdigit(*currentChar))
		ss << *currentChar;
		else if (*currentChar == '.')
		{
			//flip the boolean and then push the decimal place into the string stream
			real = true;
			ss << *currentChar;
		}
		else if (*currentChar == 'b')
		{
			binary = true;
			ss << *currentChar;
		}

		//Increment the iterator
		++currentChar;

		//Make sure the end of the expression has not been reached
		if (currentChar == expression.cend())
			break;
	}

	//pointer that will be returned
	Token::pointer_type returnToken = nullptr;
	//Figure out what kind of value is held in the string stream
	if (!real && !binary)
	{
		Integer::value_type token;
		ss >> token;
		returnToken = make<Integer>(token);
	}
	else if(real)
	{
	    Real::value_type token;
		ss >> token;
		returnToken = make<Real>(token);
	}
	else if (binary)
	{
		Integer::value_type token;
		ss >> token;
		returnToken = make<BinaryInteger>(token);
	}
	return returnToken;
}//end _get_number



/** Tokenize the expression.
	@return a TokenList containing the tokens from 'expression'.
	@param expression [in] The expression to tokenize.
	@note Tokenizer dictionary may be updated if expression contains variables.
	@note Will throws 'BadCharacter' if the expression contains an un-tokenizable character.
	*/
TokenList Tokenizer::tokenize( string_type const& expression ) {
	TokenList tokenizedExpression;

	//Set the iterator to the first character of the expression
	auto currentChar = expression.cbegin();
	//Initialize the previous token to be an open parenthesis
	Token::pointer_type previousToken = make<LeftParenthesis>();
	//Initialize next token to be a nullptr
	Token::pointer_type nextToken = nullptr;

	for(;;)
	{
		// strip whitespace
		while (currentChar != end(expression) && isspace(*currentChar))
			++currentChar;

		// check of end of expression
		if (currentChar == end(expression))break;
			
		// check for a number
		else if (isdigit(*currentChar)) {
			nextToken = _get_number(currentChar, expression);
		}

		//Check for brackets
		else if (*currentChar == '(')
		{
			++currentChar;
			nextToken = make<LeftParenthesis>();
		}
		else if (*currentChar == ')')
		{
			++currentChar;
			nextToken = make<RightParenthesis>();
		}

		//Check for a plus sign
		else if (*currentChar == '+')
		{
			//increment the iterator
			++currentChar;
			if (is<RightParenthesis>(previousToken) || is<Operand>(previousToken) || is<PostfixOperator>(previousToken))
				nextToken = make<Addition>();
			else
				nextToken = make<Identity>();
		}

		//Check for a dash
		else if (*currentChar == '-')
		{
			++currentChar;
			if (is<RightParenthesis>(previousToken) || is<Operand>(previousToken) || is<PostfixOperator>(previousToken))
				nextToken = make<Subtraction>();
			else
				nextToken = make<Negation>();
		}

		//Check for exclamation mark
		else if (*currentChar == '!')
		{
			++currentChar;
			//Check if the next character is an '='
			if (currentChar != expression.cend() &&*currentChar == '=')
			{
				++currentChar;
				nextToken = make<Inequality>();
			}
			else
			{
				if (is<RightParenthesis>(previousToken) || is<Operand>(previousToken) || is<PostfixOperator>(previousToken))
					nextToken = make<Factorial>();
				else
					throw XTokenizer(expression, std::distance(expression.begin(), currentChar), "Factorial must follow Expression");
			}
		}

		//Check for multiplication
		else if (*currentChar == '*')
		{
			++currentChar;
			//Check if the next character is also a '*'
			if (*currentChar == '*')
			{
				nextToken = make<Power>();
				++currentChar;
			}
			else
				nextToken = make<Multiplication>();
		}

		//Check for division
		else if (*currentChar == '/')
		{
			++currentChar;
			nextToken = make<Division>();
		}

		//Check for modulus
		else if (*currentChar == '%')
		{
			++currentChar;
			nextToken = make<Modulus>();
		}

		//Check for argument separator
		else if (*currentChar == ',')
		{
			++currentChar;
			nextToken = make<ArgumentSeparator>();
		}

		//Check for equality/assignment
		else if (*currentChar == '=')
		{
			++currentChar;
			//See if the next character is also an '='
			if (*currentChar == '=')
			{
				++currentChar;
				nextToken = make<Equality>();
			}
			else
			{
				nextToken = make<Assignment>();
			}
		}

		//Check for greater than / greater than equal to
		else if (*currentChar == '>')
		{
			++currentChar;
			if (*currentChar == '=')
			{
				++currentChar;
				nextToken = make<GreaterEqual>();
			}
			else
			{
				nextToken = make<Greater>();
			}
		}

		//Check for less than/ less than equal to
		else if (*currentChar == '<')
		{
			++currentChar;
			if (*currentChar == '=')
			{
				++currentChar;
				nextToken = make<LessEqual>();
			}
			else
			{
				nextToken = make<Less>();
			}
		}
		
		//Check for an alphabetic character
		else if (isalpha(*currentChar))
		{
			nextToken = _get_identifier(currentChar, expression);
		}

		else
		{
		// not a recognized token - throw exception
		throw Tokenizer::XBadCharacter(expression, currentChar - begin(expression));
		}

		//Push the token into the vector
		tokenizedExpression.push_back(nextToken);
		//Set the previous token to be the next token
		previousToken = nextToken;
	}//end for

	return tokenizedExpression;
}


/*=============================================================

Revision History

Version 0.3.0: 2017-11-23
Added Python-style power operator '**'.

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitXOr, BitShiftLeft, BitShiftRight
Simplified CHECK_OP macros

Version 0.1.0: 2012-11-15
Replaced BadCharacter with XTokenizer, XBadCharacter, and XNumericOverflow
Added BinaryInteger, Binary <function>

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-11-25
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