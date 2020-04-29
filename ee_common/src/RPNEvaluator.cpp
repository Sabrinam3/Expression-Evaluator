/** @file: RPNEvaluator.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110
	@implemented by Sabrina Tessier on 2018-12-05
	@brief RPN Evaluator class implementation.
	*/

#include "../inc/RPNEvaluator.hpp"
#include <stack>
using namespace std;

Operand::pointer_type RPNEvaluator::evaluate(TokenList const& rpnExpression) {

	//If rpnExpression is empty, throw exception
	if (rpnExpression.empty())
		throw XTooFewOperands("Error: insufficient operands");
	//Create an operand stack
	stack<Operand::pointer_type> operandStack;
	//Create the result pointer which will be populated
	Operand::pointer_type result = nullptr;

	//Iterate through the token list
	for (auto token : rpnExpression)
	{
		//If the token is an operand, push onto the operand stack
		if (is<Operand>(token))
		{
			Operand::pointer_type operandTkn = convert<Operand>(token);
			operandStack.push(operandTkn);
		}
		//The token is not an operand, must be an operation
		else
		{
			//Cast the token to an operation
			Operation::pointer_type operationTkn = convert<Operation>(token);

			//Check the operation's required number of arguments
			unsigned numberOfArgs = operationTkn->number_of_args();

			//If the number of arguments is greater than the size of the operand stack, throw an exception
			if (numberOfArgs > operandStack.size())
			{
				operationTkn->raiseTooFewParametersException();
			}

			//Call the perform method on the operator, passing it the value stack
			 result = operationTkn->perform(operandStack);

			 //Push result onto the operandStack
			 operandStack.push(result);
		}
	}//end for
	
	//If the operand stack has more than one element, throw exception
	if (operandStack.size() > 1)
		throw XTooManyOperands();

	//Return the value that is left on the stack
	return operandStack.top();
}
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
