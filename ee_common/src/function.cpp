/** @file: function.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.0.1
	@note Compiles under Visual C++ v110
	@brief Function class implementations.
	@implemented by Sabrina Tessier on  2018-12-05
	*/

#include "../inc/function.hpp"

/*Abs class methods*/
Operand::pointer_type Abs::perform(std::stack<Operand::pointer_type> &valueStack) 
{
	return valueStack.top()->perform_abs(valueStack);
}
void Abs::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Abs>");
}

/*Arccos class methods*/
Operand::pointer_type Arccos::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_arccos(valueStack);
}
void Arccos::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Arccos>");
}

/*Arcsin class methods*/
Operand::pointer_type Arcsin::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_arcsin(valueStack);
}
void Arcsin::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Arcsin>");
}

/*Arctan class methods*/
Operand::pointer_type Arctan::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_arctan(valueStack);
}
void Arctan::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Arctan>");
}

/*Ceil class methods*/
Operand::pointer_type Ceil::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_ceil(valueStack);
}
void Ceil::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Ceil>");
}

/*Floor class methods*/
Operand::pointer_type Floor::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_floor(valueStack);
}
void Floor::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Floor>");
}

/*Cos class methods*/
Operand::pointer_type Cos::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_cos(valueStack);
}
void Cos::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Cos>");
}

/*Exp class methods*/
Operand::pointer_type Exp::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_exp(valueStack);
}
void Exp::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Exp>");
}

/*Lb class methods*/
Operand::pointer_type Lb::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_lb(valueStack);
}
void Lb::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Lb>");
}

/*Ln class methods*/
Operand::pointer_type Ln::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_ln(valueStack);
}
void Ln::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Ln>");
}

/*Log class methods*/
Operand::pointer_type Log::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_log(valueStack);
}
void Log::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Log>");
}

/*Result class methods*/
Operand::pointer_type Result::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_result(valueStack);
}
void Result::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Result>");
}

/*Sin class methods*/
Operand::pointer_type Sin::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_sin(valueStack);
}
void Sin::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Sin>");
}

/*Sqrt class methods*/
Operand::pointer_type Sqrt::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_sqrt(valueStack);
}
void Sqrt::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Sqrt>");
}

/*Tan class methods*/
Operand::pointer_type Tan::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_tan(valueStack);
}
void Tan::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Tan>");
}

/*Fib class methods*/
Operand::pointer_type Fib::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_fib(valueStack);
}
void Fib::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Fib>");
}

/*Pel class methods*/
Operand::pointer_type Pel::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_pel(valueStack);
}
void Pel::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Pel>");
}

/*Syl class methods*/
Operand::pointer_type Syl::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return valueStack.top()->perform_syl(valueStack);
}
void Syl::raiseTooFewParametersException()
{
	throw RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Syl>");
}

/*Arctan2 class methods*/
Operand::pointer_type Arctan2::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_arctan2(valueStack);
}
void Arctan2::raiseTooFewParametersException()
{
	throw  RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Arctan2>");
}

/*Max class methods*/
Operand::pointer_type Max::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_max(valueStack);
}
void Max::raiseTooFewParametersException()
{
	throw  RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Max>");
}

/*Min class methods*/
Operand::pointer_type Min::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_min(valueStack);
}
void Min::raiseTooFewParametersException()
{
	throw  RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Min>");
}

/*Pow class methods*/
Operand::pointer_type Pow::perform(std::stack<Operand::pointer_type> &valueStack)
{
	return handleMixedOperands(valueStack)->perform_pow(valueStack);
}
void Pow::raiseTooFewParametersException()
{
	throw  RPNEvaluator::XTooFewOperands("Error: Insufficient parameters to <Pow>");
}



	/*=============================================================

	Revision History

	Version 0.0.1: 2012-11-13
	C++ 11 cleanup

	Version 0.0.0: 2009-12-31
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
