#ifndef GUARD_expression_evaluator_hpp20101031_
#define GUARD_expression_evaluator_hpp20101031_
/** @file: expression_evaluator.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110
	@@implemented by Sabrina Tessier on 2018-11-18

	@brief ExpressionEvaluator class declaration.
	*/

#include "token.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "RPNEvaluator.hpp"
#include <vector>

class ExpressionEvaluator {
public:
	typedef Token::string_type	expression_type;
	typedef Token::pointer_type	result_type;
private:
	Tokenizer		tokenizer_;
	Parser			parser_;
	RPNEvaluator	rpn_;
public:
	result_type evaluate(expression_type const& expr);
};

/*=============================================================

Revision History

Version 0.0.0: 2010-10-31
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
#endif // GUARD_expression_evaluator_hpp20101031_
