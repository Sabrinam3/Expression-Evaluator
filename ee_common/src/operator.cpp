/** @file: operator.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visual C++ v110
	@brief Operator class implementations.
	@implemented by Sabrina Tessier on  2018-12-05
	*/


#include "../inc/operator.hpp"

/*Power class methods*/
Operand::pointer_type Power::perform(std::stack<Operand::pointer_type> &valueStack) 
{
	//Check if the first two arguments are the same type
	return handleMixedOperands(valueStack)->perform_power(valueStack);
}
void Power::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Power>");
}

/*Assignment class methods*/
Operand::pointer_type Assignment::perform(std::stack<Operand::pointer_type> &valueStack) 
{
	return handleMixedOperands(valueStack)->perform_assignment(valueStack);
}
void Assignment::raiseTooFewParametersException() 
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Assignment>");
}

/*Addition class methods*/
Operand::pointer_type Addition::perform(std::stack<Operand::pointer_type> &valueStack) 
{
	return handleMixedOperands(valueStack)->perform_addition(valueStack);
}
void Addition::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Addition>");
}

/*And class methods*/
Operand::pointer_type And::perform(std::stack<Operand::pointer_type> &valueStack) 
{
	return handleMixedOperands(valueStack)->perform_and(valueStack);
}
void And::raiseTooFewParametersException() 
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <And>");
}

/*Division class methods*/
Operand::pointer_type Division::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_division(valueStack);
}
void Division::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Division>");
}

/*Equality class methods*/
Operand::pointer_type Equality::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_equality(valueStack);
}
void Equality::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Equality>");
}

/*Inequality class methods*/
Operand::pointer_type Inequality::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_inequality(valueStack);
}
void Inequality::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Inequality>");
}

/*Greater class methods*/
Operand::pointer_type Greater::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_greater(valueStack);
}
void Greater::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Greater>");
}

/*GreaterEqual class methods*/
Operand::pointer_type GreaterEqual::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_greater_equal(valueStack);
}
void GreaterEqual::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <GreaterEqual>");
}

/*Less class methods*/
Operand::pointer_type Less::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_less(valueStack);
}
void Less::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Less>");
}

/*LessEqual class methods*/
Operand::pointer_type LessEqual::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_less_equal(valueStack);
}
void LessEqual::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <LessEqual>");
}

/*Modulus class methods*/
Operand::pointer_type Modulus::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_modulus(valueStack);
}
void Modulus::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Modulus>");
}

/*Multiplication class methods*/
Operand::pointer_type Multiplication::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_multiplication(valueStack);
}
void Multiplication::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Multiplication>");
}

/*Nand class methods*/
Operand::pointer_type Nand::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_nand(valueStack);
}
void Nand::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Nand>");
}

/*Nor class methods*/
Operand::pointer_type Nor::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_nor(valueStack);
}
void Nor::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Nor>");
}

/*Or class methods*/
Operand::pointer_type Or::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_or(valueStack);
}
void Or::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Or>");
}

/*Xnor class methods*/
Operand::pointer_type Xnor::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_xnor(valueStack);
}
void Xnor::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Xnor>");
}

/*Xor class methods*/
Operand::pointer_type Xor::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_xor(valueStack);
}
void Xor::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Xor>");
}

/*Subtraction class methods*/
Operand::pointer_type Subtraction::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_subtraction(valueStack);
}
void Subtraction::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Subtraction>");
}

/*Negation class methods*/
Operand::pointer_type Negation::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_negation(valueStack);
}
void Negation::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Negation>");
}

/*Identity class methods*/
Operand::pointer_type Identity::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_identity(valueStack);
}
void Identity::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Identity>");
}

/*Not class methods*/
Operand::pointer_type Not::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_not(valueStack);
}
void Not::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Not>");
}
/*Factorial class methods*/
Operand::pointer_type Factorial::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_factorial(valueStack);
}
void Factorial::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Factorial>");
}

	/*=============================================================

	Revision History

	Version 0.1.1: 2012-11-13
	C++ 11 cleanup

	Version 0.1.0: 2010-11-08
	Added exception for assignment to a non-variable.

	Version 0.0.0: 2009-12-14
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
