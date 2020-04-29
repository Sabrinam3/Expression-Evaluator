/**  @file: parser.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visual C++ v120
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Parser class implementation.
	*/

#include "../inc/parser.hpp"
#include "../inc/boolean.hpp"
#include "../inc/function.hpp"
#include "../inc/integer.hpp"
#include "../inc/operator.hpp"
#include "../inc/pseudo_operation.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"
#include <queue>
#include <stack>
using namespace std;

/*@Brief: converts a list of Tokens into infix notation
@Param: TokenList const& infixTokens - the list of tokens in infix notation
@Returns a new list of Tokens in postfix notation */

TokenList Parser::parse(TokenList const& infixTokens) {
	//Declare a vector that will hold the postfix expression
	TokenList postfixList;
	//Declare a queue that will be used for the conversion
	queue<Token::pointer_type> outputQueue;
	//Declare a stack that will be used for the conversion
	stack<Token::pointer_type> operationStack;
	//For each Token in the infix list
	for (Token::pointer_type const& tkn : infixTokens)
	{
		//If the token is an operand, then append the token to the output queue
		if (is<Operand>(tkn))
		{
			outputQueue.push(tkn);
		}
		//Else if the token is a fuction, push the token onto the operation stack
		else if (is<Function>(tkn))
		{
			operationStack.push(tkn);
		}
		//Else if the  token is an argument seperator, start a while loop
		else if (is<ArgumentSeparator>(tkn))
		{
			while (!is<LeftParenthesis>(operationStack.top()))
			{
				outputQueue.push(operationStack.top());
				operationStack.pop();
			}
		}
		//Else if the token is a left-parenthesis, push the token onto the operation stack
		else if (is<LeftParenthesis>(tkn))
		{
			operationStack.push(tkn);
		}

		//Else if the token is a right parenthesis, start a while loop
		else if (is<RightParenthesis>(tkn))
		{
			if(operationStack.empty())
				throw XMismatchedParenthesis();
			while (!is<LeftParenthesis>(operationStack.top()))
			{
				outputQueue.push(operationStack.top());
				operationStack.pop();
				if (operationStack.empty())break;
			}
			//If the operation stack is empty then, Exception
			if (operationStack.empty())
			{
				throw XMismatchedParenthesis();
			}
			//Pop the left parenthesis from the operation stack
			operationStack.pop();
			//If the top of the operation stack is a function, append to output queue
			if (!operationStack.empty() && is<Function>(operationStack.top()))
			{
				outputQueue.push(operationStack.top());
				operationStack.pop();
			}
		}
			//Else if the token is an operator, start a while loop
			else if (is<Operator>(tkn))
			{
				//While the operation stack is not empty do...
				while (!operationStack.empty())
				{
					//If the top of the stack is not an operator, or the top of the stack is a non-associative operator, then break out of loop
					if (!is<Operator>(operationStack.top()) || is<NonAssociative>(tkn))
						break;
					//If the token is left-associative and has greater precedence than top of the stack, exit the loop
					if (is<LAssocOperator>(tkn))
					{
						//Cast the token to an operator
						Operator::pointer_type tknOpr = convert<LAssocOperator>(tkn);
						//Cast the top of the operationStack to an operator
						Operator::pointer_type queueOpr = convert<Operator>(operationStack.top()); 
						//If the token has greater precendence than top of operation stack, exit loop
						if (tknOpr->get_precedence() > queueOpr->get_precedence())
							break;
					}

					//If the token is a right-associative operator and has >= precedence than the top of operation-stack, exit loop
					if (is<RAssocOperator>(tkn))
					{
						//Cast the token to an operator
						Operator::pointer_type tknOpr = convert<RAssocOperator>(tkn);
						//Cast the top of the operationStack to an operator
						Operator::pointer_type queueOpr = convert<Operator>(operationStack.top());
						//If the operator has >= precedence to top of operation-stack, exit while
						if (tknOpr->get_precedence() >= queueOpr->get_precedence())
							break;
					}
					outputQueue.push(operationStack.top());
					operationStack.pop();
				}//end while
				operationStack.push(tkn);
			}//end else if
	}//end for-each
	
	//While the operation stack is not empty do....
	while (!operationStack.empty())
	{
		//If the top of the operation-stack is a left-parenthesis...
		if (is<LeftParenthesis>(operationStack.top()))
		{
			throw XMismatchedParenthesis();
		}
		//Pop an operator from the top of operation stack and append to queue
		outputQueue.push(operationStack.top());
		operationStack.pop();
	}//end while

	//Take the order of items from the queue and place them into the vector 
	while (!outputQueue.empty())
	{
		postfixList.push_back(outputQueue.front());
		outputQueue.pop();
	}
	return postfixList;
}


/*=============================================================

Revision History
Version 1.0.0: 2014-10-31
Visual C++ 2013

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-02
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

