/* @file: expression_evaluator.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110
	@implemented by Sabrina Tessier on  2018-12-05

	@brief ExpressionEvaluator class implementation.
	*/

#include "../inc/expression_evaluator.hpp"

ExpressionEvaluator::result_type ExpressionEvaluator::evaluate(expression_type const& expr)
{
	//Pointers that will get their values further down
	Operand::pointer_type resultType = nullptr;
	Token::pointer_type finalReturn = nullptr;
	try
	{
		//First tokenize the expression
		TokenList infixTokens = tokenizer_.tokenize(expr);
		//Then parse the expression
		TokenList postfixTokens = parser_.parse(infixTokens);
		//Then evaluate the expression
		Operand::pointer_type result = rpn_.evaluate(postfixTokens);
		/*Add the return to the vector that is storing the results for the result function*/
		resultTypes.push_back(result);
		/*return the result*/
		return result;
	}
	catch (Tokenizer::XBadCharacter &e)
	{
		cout << e.get_expression() << endl;
		for (auto i = 0; i < e.get_location(); ++i)
			cout << ".";
		cout << "^" << endl;
		cout << "Error: ";
		throw e;
	}
	
	catch (std::exception &e)
	{
		throw e;
	}
}
	

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
