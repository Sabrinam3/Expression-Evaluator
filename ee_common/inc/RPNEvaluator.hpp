#ifndef GUARD_rpnevaluator_hpp20091210_
#define GUARD_rpnevaluator_hpp20091210_

/** @file: RPNEvaluator.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110
	@implemented by Sabrina Tessier on  2018-11-18
	@brief RPN Evaluator class declaration.
	*/

#include "operand.hpp"
#include "operation.hpp"
#include "boolean.hpp"
#include "variable.hpp"
#include "integer.hpp"

class RPNEvaluator {
public:
	typedef std::string string_type;
	Operand::pointer_type evaluate(TokenList const& container);

	//Exception classes for exceptions that might occur during evaluation*/

	/*Brief- Base class for exceptions in this file*/
	class XEvaluator : public std::exception
	{
	public:
		XEvaluator(char const* msg) : std::exception(msg) {}
	};

	/*Too many operands*/
	class XTooManyOperands : public XEvaluator {
	public:
		XTooManyOperands() : XEvaluator("Error: too many operands") {}
	};

	/*Insufficient operands exception class*/
	class XTooFewOperands : public XEvaluator {
	public:
		XTooFewOperands(const char* msg) : XEvaluator(msg) {}
	};

	/*Cannot perform*/
	class XCannotPerform : public XEvaluator {
	public:
		XCannotPerform(const char* msg) : XEvaluator(msg) {}
	};
	/*Cannot convert*/
	class XCannotConvert : public XEvaluator {
	public:
		XCannotConvert() : XEvaluator("Cannot Convert") {}
	};

	/*Assignment to non-variable*/
	class XAssignmentToNonVariable : public XEvaluator {
	public:
		XAssignmentToNonVariable() : XEvaluator("Error: assignment to a non-variable.") {}
	};

	/*Variable not initialized*/
	class XVariableNotInitialized : public XEvaluator {
	public: 
		XVariableNotInitialized() : XEvaluator("Error: variable not initialized.") {}
	};

	/*Result higher than index*/
	class XResultHigherThanIndex : public XEvaluator {
	public:
		XResultHigherThanIndex() : XEvaluator("Error: Result index is above range.") {}
	};

};



/*=============================================================

Revision History

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-10
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
#endif // GUARD_rpnevaluator_hpp20091210_
