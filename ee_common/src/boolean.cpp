/** @file: boolean.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.0.1
	@note Compiles under Visual C++ v110
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Boolean class implementation.
	*/

#include "../inc/boolean.hpp"
#include <boost/lexical_cast.hpp>
using namespace std;

/*@Brief prints a boolean datatype's value to the console
@Returns std::string*/

Boolean::string_type Boolean::to_string() const {
	//return string_type("Boolean: ") + boost::lexical_cast<string_type>(get_value());
	if (get_value())
		return "true";
	return "false";
}

/*@Brief performs the addition operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_addition(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	else
		return Operand::pointer_type(new Boolean(false));
}

/*@Brief performs the multiplication operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_multiplication(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(false));

}
/*@Brief performs the not operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_not(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value())
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(true));
}

/*@Brief performs the and operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_and(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(false));
}

/*@Brief performs the nand operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_nand(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	else
		return Operand::pointer_type(new Boolean(true));
}

/*@Brief performs the nor operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_nor(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(true));
}

/*@Brief performs the nor operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_or(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	else
		return Operand::pointer_type(new Boolean(false));
}
/*@Brief performs the xor operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_xor(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	else
		return Operand::pointer_type(new Boolean(false));
}
/*@Brief performs the xnor operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_xnor(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(true));
}

/*@Brief performs the equality operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_equality(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(true));
}

/*@Brief performs the inequality operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_inequality(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	else
		return Operand::pointer_type(new Boolean(false));
}

/*@Brief performs the greater than operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_greater(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	else
		return Operand::pointer_type(new Boolean(false));
}

/*@Brief performs the greater than equal to operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_greater_equal(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	else
		return Operand::pointer_type(new Boolean(true));
}
/*@Brief performs the less than to operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_less(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(false));
}
/*@Brief performs the less than equal to to operator on a boolean and returns an operand pointer type with the correct value*/
Operand::pointer_type Boolean::perform_less_equal(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type boolToken = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type boolTokenTwo = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == true && boolTokenTwo->get_value() == false)
		return Operand::pointer_type(new Boolean(true));
	if (boolToken->get_value() == false && boolTokenTwo->get_value() == true)
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(true));
}

/*@Brief performs the max operation on two booleans and returns an operand pointer type with the maximum of the two */
Operand::pointer_type Boolean::perform_max(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type first = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type second = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (first->get_value() == true || second->get_value() == true)
		return Operand::pointer_type(new Boolean(true));
	else
		return Operand::pointer_type(new Boolean(false));
}

/*@Brief performs the min operation on two booleans and returns an operand pointer type with the minimum of the two */
Operand::pointer_type Boolean::perform_min(std::stack<Operand::pointer_type> &valueStack)
{
	Boolean::pointer_type first = convert<Boolean>(valueStack.top());
	valueStack.pop();
	Boolean::pointer_type second = convert<Boolean>(valueStack.top());
	valueStack.pop();
	if (first->get_value() == false || second->get_value() == false)
		return Operand::pointer_type(new Boolean(false));
	else
		return Operand::pointer_type(new Boolean(true));
}

Operand::pointer_type Boolean::perform_cos(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(cos(1)));
	else 
		return Operand::pointer_type(new Real(cos(0)));
}

Operand::pointer_type Boolean::perform_tan(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(tan(1)));
	else
		return Operand::pointer_type(new Real(tan(0)));
}

Operand::pointer_type Boolean::perform_abs(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(1));
	else
		return Operand::pointer_type(new Real(0));
}

Operand::pointer_type Boolean::perform_arccos(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(acos(1)));
	else
		return Operand::pointer_type(new Real(acos(0)));
}

Operand::pointer_type Boolean::perform_arcsin(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(asin(1)));
	else
		return Operand::pointer_type(new Real(asin(0)));
}

Operand::pointer_type Boolean::perform_arctan(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(atan(1)));
	else
		return Operand::pointer_type(new Real(atan(0)));
}

Operand::pointer_type Boolean::perform_ceil(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Integer(1));
	else
		return Operand::pointer_type(new Integer(0));
}

Operand::pointer_type Boolean::perform_floor(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Integer(1));
	else
		return Operand::pointer_type(new Integer(0));
}

Operand::pointer_type Boolean::perform_exp(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(exp(1)));
	else
		return Operand::pointer_type(new Real(exp(0)));
}

Operand::pointer_type Boolean::perform_lb(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(log2(1)));
	else
		return Operand::pointer_type(new Real(log2(0)));
}

Operand::pointer_type Boolean::perform_ln(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(log(1)));
	else
		return Operand::pointer_type(new Real(log(0)));
}

Operand::pointer_type Boolean::perform_log(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(log10(1)));
	else
		return Operand::pointer_type(new Real(log10(0)));
}

Operand::pointer_type Boolean::perform_sin(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(sin(1)));
	else
		return Operand::pointer_type(new Real(sin(0)));
}

Operand::pointer_type Boolean::perform_sqrt(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Real(sqrt(1)));
	else
		return Operand::pointer_type(new Real(sqrt(0)));
}

Operand::pointer_type Boolean::perform_fib(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Integer(1));
	else
		return Operand::pointer_type(new Integer(1));
}

Operand::pointer_type Boolean::perform_pel(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Integer(1));
	else
		return Operand::pointer_type(new Integer(0));
}

Operand::pointer_type Boolean::perform_syl(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == true)
		return Operand::pointer_type(new Integer(3));
	else
		return Operand::pointer_type(new Integer(2));
}
//METHOD OVERRIDES THAT ARE NOT ALLOWED FOR BOOLEAN DATA TYPE - WILL THROW EXCEPTION
Operand::pointer_type Boolean::perform_subtraction(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Subtraction>");
}

Operand::pointer_type Boolean::perform_division(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Division>");
}

Operand::pointer_type Boolean::perform_modulus(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Modulus>");
}

Operand::pointer_type Boolean::perform_power(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Power>");
}

Operand::pointer_type Boolean::perform_assignment(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XAssignmentToNonVariable();
}

Operand::pointer_type Boolean::perform_identity(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Identity>");
}

Operand::pointer_type Boolean::perform_negation(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Negation>");
}

Operand::pointer_type Boolean::perform_factorial(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Factorial>");
}


Operand::pointer_type Boolean::perform_pow(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Pow>");
}

Operand::pointer_type Boolean::perform_arctan2(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Arctan2>");
}


Operand::pointer_type Boolean::perform_result(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Result>");
}

/*=============================================================

Revision History

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-11-26
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