/** @file: integer.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-16
	@version 1.0.0
	@note Compiles under Visaul C++ v120
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Integer class implementation.
	*/

#include "../inc/integer.hpp"
#include "../inc/real.hpp"
#include "../inc/boolean.hpp"
#include <boost/lexical_cast.hpp>
using namespace std;

std::vector<Operand::pointer_type> resultTypes;

/*Throws exception if non numeric type is entered into numeric function*/
#define NON_NUMERIC() throw RPNEvaluator::XCannotConvert();

/*@Brief returns an integer datatype's value as a string
@Returns string*/
Integer::string_type Integer::to_string() const {
	//return string_type("Integer: ") + boost::lexical_cast<string_type>(get_value());
	return string_type(boost::lexical_cast<string_type>(get_value()));
}

/*@Brief performs addition on two integers and returns an operand pointer with the correct result*/
Operand::pointer_type Integer::perform_addition(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	/*If one of the operands is a boolean, throw exception*/
	valueStack.pop();
	if (!first || !second)
		NON_NUMERIC()
	value_type additionResult = first->get_value() + second->get_value();
	return Operand::pointer_type(new Integer(additionResult));
}

/*@Brief performs subtraction on two integers and returns an operand pointer with the correct result*/
Operand::pointer_type Integer::perform_subtraction(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	value_type additionResult = first->get_value() - second->get_value();
	return Operand::pointer_type(new Integer(additionResult));
}

/*@Brief performs the identity operator on an integer and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_identity(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Integer(1  * value));
}

/*@Brief performs the negation operator on an integer and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_negation(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Integer(-1 * value));
}

/*@Brief performs the factorial operator on an integer and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_factorial(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	Integer::value_type factorial = 1;
	for (auto i = value; i >= 2; --i)
		factorial *= i;
	return Operand::pointer_type(new Integer(factorial));
}

/*@Brief performs the multiplication and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_multiplication(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Integer(first->get_value() * second->get_value()));
}

/*@Brief performs the division and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_division(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Integer(first->get_value() / second->get_value()));
}

/*@Brief performs the modulus and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_modulus(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Integer(first->get_value() % second->get_value()));
}

/*@Brief performs the power and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_power(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	//For clarity and easier reference down below
	Integer::value_type base = first->get_value();
	Integer::value_type exp = second->get_value();
	if (exp == 1)
		return Operand::pointer_type(new Integer(base));
	if (exp == 0)
		return Operand::pointer_type(new Integer(1));
	else
	{
		Integer::value_type negativeExp = exp;
		if (exp < 0)
			negativeExp = -1 * exp;
		Integer::value_type power = 1;
		for (Integer::value_type i = 0; i < negativeExp; ++i)
			power *= base;
		if (exp < 0)
			return Operand::pointer_type(new Real(1 / static_cast<Real::value_type>(power)));
		return Operand::pointer_type(new Integer(power));
	}
}

/*@Brief performs the equality operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_equality(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Boolean(first->get_value() == second->get_value()));
}

/*@Brief performs the inequality operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_inequality(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Boolean(first->get_value() != second->get_value()));
}

/*@Brief performs the greater than operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_greater(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Boolean(first->get_value() > second->get_value()));
}

/*@Brief performs the greater than equal to operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_greater_equal(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Boolean(first->get_value() >= second->get_value()));
}

/*@Brief performs the less than operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_less(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Boolean(first->get_value() < second->get_value()));
}

/*@Brief performs the less than equal to operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_less_equal(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Boolean(first->get_value() <= second->get_value()));
}

/*@Brief performs the abs function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_abs(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Integer(abs(value)));
}

Operand::pointer_type Integer::perform_fib(std::stack<Operand::pointer_type>&valueStack)
{
	Integer::value_type n = get_value();
	valueStack.pop();
	if (n <= 1)
		return Operand::pointer_type(new Integer(1));
	Integer::value_type n1 = 1, n2 = 1, next;
	for (Integer::value_type i = 2; i <= n; ++i) {
		next = n1 + n2;
		n2 = n1;
		n1 = next;
	}
	return Operand::pointer_type(new Integer(next));
}
Operand::pointer_type Integer::perform_syl(std::stack<Operand::pointer_type>&valueStack)
{
	Integer::value_type n = get_value();
	valueStack.pop();
	if (n == 0)
		return Operand::pointer_type(new Integer(2));
	Integer::value_type previous = 2;
	Integer::value_type sylvester = 0;
	for (size_t i = 0; i < n; ++i)
	{
		sylvester = ((previous * previous) - previous) + 1;
		previous = sylvester;
	}
	return Operand::pointer_type(new Integer(sylvester));
}
Operand::pointer_type Integer::perform_pel(std::stack<Operand::pointer_type>&valueStack)
{
	Integer::value_type n = get_value();
	valueStack.pop();
	if (n < 2)
		return Operand::pointer_type(new Integer(n));

	Integer::value_type first = 0;
	Integer::value_type second = 1;
	Integer::value_type pell = 0;

	for (size_t i = 1; i < n; ++i)
	{
		pell = 2 * second + first;
		first = second;
		second = pell;
	}

	return Operand::pointer_type(new Integer(pell));
}

/*@Brief performs the max function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_max(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Integer(max(first->get_value(), second->get_value())));
}

/*@Brief performs the min function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_min(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	return Operand::pointer_type(new Integer(min(first->get_value(), second->get_value())));
}

/*@Brief performs the pow function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_pow(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::pointer_type first = convert<Integer>(valueStack.top());
	valueStack.pop();
	Integer::pointer_type second = convert<Integer>(valueStack.top());
	valueStack.pop();
	/*If one of the operands is a boolean, throw exception*/
	if (!first || !second)
		NON_NUMERIC()
	//For clarity and easier reference down below
	Integer::value_type exp = first->get_value();
	Integer::value_type base = second->get_value();
	if (exp == 1)
		return Operand::pointer_type(new Integer(base));
	if (exp == 0)
		return Operand::pointer_type(new Integer(1));
	else
	{
		Integer::value_type negativeExp = exp;
		if (exp < 0)
			negativeExp = -1 * exp;
		Integer::value_type power = 1;
		for (Integer::value_type i = 0; i < negativeExp; ++i)
			power *= base;
		if (exp < 0)
			return Operand::pointer_type(new Real(1 / static_cast<Real::value_type>(power)));
		return Operand::pointer_type(new Integer(power));
	}
}

/*@Brief performs the not function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_not(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == 0)
		return Operand::pointer_type(new Integer(1));
	else
		return Operand::pointer_type(new Integer(0));
}

/*@Brief performs the arccos function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_arccos(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(acos(static_cast<Real::value_type>(value))));
}

/*@Brief performs the arcsin function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_arcsin(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(asin(static_cast<Real::value_type>(value))));
}

/*@Brief performs the arctan function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_arctan(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(atan(static_cast<Real::value_type>(value))));
}

/*@Brief performs the cos function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_cos(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(cos(static_cast<Real::value_type>(value))));
}

/*@Brief performs the ceil function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_ceil(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(ceil(static_cast<Real::value_type>(value))));
}

/*@Brief performs the floor function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_floor(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(floor(static_cast<Real::value_type>(value))));
}

/*@Brief performs the exp function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_exp(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(exp(static_cast<Real::value_type>(value))));
}

/*@Brief performs the lb function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_lb(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(log2(static_cast<Real::value_type>(value))));
}

/*@Brief performs the ln function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_ln(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(log(static_cast<Real::value_type>(value))));
}
/*@Brief performs the log function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_log(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(log10(static_cast<Real::value_type>(value))));
}

/*@Brief performs the sin function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_sin(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(sin(static_cast<Real::value_type>(value))));
}

/*@Brief performs the sqrt function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_sqrt(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(sqrt(static_cast<Real::value_type>(value))));
}

/*@Brief performs the tan function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_tan(std::stack<Operand::pointer_type> &valueStack)
{
	Integer::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(tan(static_cast<Real::value_type>(value))));
}

/*@Brief performs the result function and returns an operand pointer type with the correct value*/
Operand::pointer_type Integer::perform_result(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	unsigned long long requestedIndex = static_cast<unsigned long long>(get_value());
	/*Return the operand pointer type that is at the specified index*/
	if (requestedIndex > resultTypes.size())
		throw RPNEvaluator::XResultHigherThanIndex();
	return resultTypes.at(requestedIndex-1);
}

//METHOD OVERRIDES THAT ARE NOT ALLOWED FOR INTEGER DATA TYPE - WILL THROW EXCEPTION
Operand::pointer_type Integer::perform_and(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <And>");
}

Operand::pointer_type Integer::perform_nand(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Nand>");
}

Operand::pointer_type Integer::perform_nor(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Nor>");
}

Operand::pointer_type Integer::perform_or(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Or>");
}

Operand::pointer_type Integer::perform_xor(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <xor>");
}

Operand::pointer_type Integer::perform_xnor(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Xnor>");
}

Operand::pointer_type Integer::perform_assignment(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XAssignmentToNonVariable();
}

Operand::pointer_type Integer::perform_arctan2(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Arctan2>");
}















/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Converted Integer::value_type to boost::multiprecision::cpp_int

Version 0.2.0: 2012-11-16
Added Bit operators, Pow

Version 0.1.0: 2012-11-15
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


