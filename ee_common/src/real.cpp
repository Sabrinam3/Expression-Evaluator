/** @file: real.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 1.0.0
	@note Compiles under Visual C++ v120
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Real class implementation.
	*/

#include "../inc/real.hpp"
#include "../inc/integer.hpp"
#include "../inc/boolean.hpp"
#include <sstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>
using namespace std;

/*@Brief returns a real's value as string
@Returns string*/

Real::string_type Real::to_string() const {
	//return string_type("Real: ") + boost::lexical_cast<string_type>(get_value());
	//return string_type(boost::lexical_cast<string_type>(get_value()));
	ostringstream oss;
	oss << fixed << setprecision(10);
	oss << get_value();
	return oss.str();
}

/*@Brief makes sure that both operands are reals before conducting calculations*/
void convertToRealType(std::stack<Operand::pointer_type>&valueStack)
{
	if (!is<Real>(valueStack.top()))
	{
		//Check if it's an integer
		if (is<Integer>(valueStack.top()))
		{
			/*Extract the value from the integer and create a real from it*/
			Integer::pointer_type tempInt = convert<Integer>(valueStack.top());
			Real::value_type valueFromInt = tempInt->get_value().convert_to<Real::value_type>();//convert_to<Real::value_type>(valueFromInt);
			Operand::pointer_type newReal = make_operand<Real>(valueFromInt);
			valueStack.pop();
			valueStack.push(newReal);
			return;
		}
		else
		{
			throw RPNEvaluator::XCannotConvert();
		}
	}
	/*The first value was a real so check if the second value in the stack is a real*/
	/*Temporarily store the first value*/
	Operand::pointer_type temp = valueStack.top();
	valueStack.pop();
	if (!is<Real>(valueStack.top()))
	{
		if (is<Integer>(valueStack.top()))
		{
			/*Extract the value from the integer and create a real from it*/
			Integer::pointer_type tempInt = convert<Integer>(valueStack.top());
			Real::value_type valueFromInt = tempInt->get_value().convert_to<Real::value_type>();//convert_to<Real::value_type>(valueFromInt);
			Operand::pointer_type newReal = make_operand<Real>(valueFromInt);		
			valueStack.pop();
			valueStack.push(newReal);
			valueStack.push(temp);
			return;
		}
		else
		{
			throw RPNEvaluator::XCannotConvert();
		}
	}
	/*Both values are real so put the other real back on the stack and return*/
	valueStack.push(temp);
	return;	
}
/*@Brief performs addition on two reals and returns an operand pointer with the correct result*/
Operand::pointer_type Real::perform_addition(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(realOne->get_value() + realTwo->get_value()));
}

/*@Brief performs subtraction on two reals and returns an operand pointer with the correct result*/
Operand::pointer_type Real::perform_subtraction(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(realTwo->get_value() - realOne->get_value()));
}
/*@Brief- performs identity operation on a real operator and returns an operand pointer with the correct value*/
Operand::pointer_type Real::perform_identity(std::stack<Operand::pointer_type> &valueStack)
{
	Real::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(1.0 * value));
}

/*@Brief- performs negation operation on a real operator and returns an operand pointer with the correct value*/
Operand::pointer_type Real::perform_negation(std::stack<Operand::pointer_type> &valueStack)
{
	Real::value_type value = get_value();
	valueStack.pop();
	return Operand::pointer_type(new Real(-1.0 * value));
}

/*@Brief performs the multiplication and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_multiplication(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(realTwo->get_value() * realOne->get_value()));
}

/*@Brief performs the division and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_division(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(realTwo->get_value() / realOne->get_value()));
}

/*@Brief performs the power and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_power(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(pow(realTwo->get_value(), realOne->get_value())));
}

/*@Brief performs the equality operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_equality(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Boolean(realTwo->get_value() == realOne->get_value()));
}

/*@Brief performs the inequality operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_inequality(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Boolean(realTwo->get_value() != realOne->get_value()));
}

/*@Brief performs the greater than operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_greater(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Boolean(realTwo->get_value() > realOne->get_value()));
}

/*@Brief performs the greater than equal to operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_greater_equal(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Boolean(realTwo->get_value() >= realOne->get_value()));
}

/*@Brief performs the less than operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_less(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Boolean(realTwo->get_value() < realOne->get_value()));
}

/*@Brief performs the less than equal to operator and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_less_equal(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Boolean(realTwo->get_value() <= realOne->get_value()));
}

/*@Brief performs the abs function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_abs(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(abs(get_value())));
}

/*@Brief performs the arccos function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_arccos(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(acos(get_value())));
}

/*@Brief performs the arcsin function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_arcsin(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(asin(get_value())));
}

/*@Brief performs the arctan function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_arctan(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(atan(get_value())));
}

/*@Brief performs the cos function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_cos(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(cos(get_value())));
}

/*@Brief performs the cos function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_exp(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(exp(get_value())));
}


/*@Brief performs the ceil function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_ceil(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(ceil(get_value())));
}

/*@Brief performs the floor function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_floor(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(floor(get_value())));
}

/*@Brief performs the binary logarithm function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_lb(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(log2(get_value())));
}

/*@Brief performs the natural logarithm function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_ln(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(log(get_value())));
}

/*@Brief performs the base 10 logarithm function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_log(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(log10(get_value())));
}

/*@Brief performs the sin function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_sin(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(sin(get_value())));
}

/*@Brief performs the sqrt function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_sqrt(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(sqrt(get_value())));
}

/*@Brief performs the tan function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_tan(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	return Operand::pointer_type(new Real(tan(get_value())));
}

/*@Brief performs the max function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_max(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(max(realTwo->get_value(),realOne->get_value())));
}

/*@Brief performs the min function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_min(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(min(realTwo->get_value(), realOne->get_value())));
}

/*@Brief performs the pow function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_pow(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(pow(realTwo->get_value(), realOne->get_value())));
}

/*@Brief performs the arctan2 function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_arctan2(std::stack<Operand::pointer_type> &valueStack)
{
	convertToRealType(valueStack);
	Real::pointer_type realOne = convert<Real>(valueStack.top());
	valueStack.pop();
	Real::pointer_type realTwo = convert<Real>(valueStack.top());
	valueStack.pop();
	return Operand::pointer_type(new Real(atan2(realTwo->get_value(), realOne->get_value())));
}

/*@Brief performs the not function and returns an operand pointer type with the correct value*/
Operand::pointer_type Real::perform_not(std::stack<Operand::pointer_type> &valueStack)
{
	valueStack.pop();
	if (get_value() == 0)
		return Operand::pointer_type(new Real(1));
	else
		return Operand::pointer_type(new Real(0));
}


//METHOD OVERRIDES THAT ARE NOT ALLOWED FOR REAL DATA TYPE - WILL THROW EXCEPTION

Operand::pointer_type Real::perform_factorial(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Factorial>");
}
Operand::pointer_type Real::perform_fib(std::stack<Operand::pointer_type>&valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Fib>");
}
Operand::pointer_type Real::perform_pel(std::stack<Operand::pointer_type>&valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Pel>");
}
Operand::pointer_type Real::perform_syl(std::stack<Operand::pointer_type>&valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Syl>");
}

Operand::pointer_type Real::perform_and(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <And>");
}

Operand::pointer_type Real::perform_nand(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Nand>");
}

Operand::pointer_type Real::perform_nor(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Nor>");
}

Operand::pointer_type Real::perform_or(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Or>");
}

Operand::pointer_type Real::perform_xor(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <xor>");
}

Operand::pointer_type Real::perform_xnor(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Xnor>");
}

Operand::pointer_type Real::perform_assignment(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XAssignmentToNonVariable();
}

Operand::pointer_type Real::perform_modulus(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Modulus>");
}

Operand::pointer_type Real::perform_result(std::stack<Operand::pointer_type> &valueStack)
{
	throw RPNEvaluator::XCannotPerform("Error cannot perform <Result>");
}


/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Switched value_type to boost::multiprecision::cpp_dec_float_100

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
