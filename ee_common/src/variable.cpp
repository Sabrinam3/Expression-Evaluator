/** @file: variable.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visual C++ v110
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Variable class implementation.
	*/

#include "../inc/variable.hpp"
using namespace std;

/*@Brief returns a variable token and it's value
@Return string*/

Variable::string_type Variable::to_string() const {
	if (this->get_value() == nullptr)
		return string_type("Variable: null");
	else
	{
		Operand::pointer_type variableValue = this->get_value();
		if (is<Integer>(variableValue))
		{
			Integer::pointer_type intVal = convert<Integer>(variableValue);
			return string_type(boost::lexical_cast<string_type>(intVal->get_value()));
		}
		else if (is<Real>(variableValue))
		{
			return get_value()->to_string();
		}
		else if (is<Boolean>(variableValue))
		{
			Boolean::pointer_type boolVal = convert<Boolean>(variableValue);
			if (boolVal->get_value() == true)
				return "True";
			else
				return "False";
		}
		else if (is<Variable>(variableValue))
		{
			Variable::pointer_type varVal = convert<Variable>(variableValue);
			return varVal->to_string();
		}
		else return variableValue->to_string();
	}
}

/*@Brief- assigns a value to a variable*/
Operand::pointer_type Variable::perform_assignment(std::stack<Operand::pointer_type>&valueStack)
{
	//Store the top of the stack to use to provide the variable with its value
	Operand::pointer_type variableValue = valueStack.top();
	valueStack.pop();
	/*If the next value isnt a varable, throw exception*/
	if(!is<Variable>(valueStack.top()))
	throw RPNEvaluator::XAssignmentToNonVariable();
	//If the value meant to give the variable it's value is a nullptr, the variable doesn't exist so throw an exception
	if (is<Variable>(variableValue))
	{
		Variable::pointer_type variableAssignment = convert<Variable>(variableValue);
		if (variableAssignment->to_string() == "Variable: null")
		{
			throw RPNEvaluator::XVariableNotInitialized();
		}
	}
	//Convert the top of the stack to a variable pointer
	Variable::pointer_type variable = convert<Variable>(valueStack.top());

	/*If the variable is being assigned to itself, just return one of the variables*/
	if (variableValue.get() == variable.get())
	{
		valueStack.pop();
		return variableValue;
	}
		
	//Assign the variable the operand from above
	variable->set_value(variableValue);
	valueStack.pop();

	return variable;
}

/*Brief- performs addition with variables*/
Operand::pointer_type Variable::perform_addition(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);
		if (!variableValue)
			throw RPNEvaluator::XVariableNotInitialized();
		
	}	
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);
		if (!variableValue)
			throw RPNEvaluator::XVariableNotInitialized();
		
	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
			return variableValue->perform_addition(valueStack);
		else
			return valueStack.top()->perform_addition(valueStack);
}

/*Brief- performs multiplication with variables*/
Operand::pointer_type Variable::perform_multiplication(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_multiplication(valueStack);
	else
		return valueStack.top()->perform_multiplication(valueStack);
}
/*Brief- performs subtraction with variables*/
Operand::pointer_type Variable::perform_subtraction(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_subtraction(valueStack);
	else
		return valueStack.top()->perform_subtraction(valueStack);
}

/*Brief- performs division with variables*/
Operand::pointer_type Variable::perform_division(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_division(valueStack);
	else
		return valueStack.top()->perform_division(valueStack);
}
/*@Brief Performs not operation with variables*/
Operand::pointer_type Variable::perform_not(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = get_value();
	return variableValue->perform_not(valueStack);
}

/*@Brief Performs and operation with variables*/
Operand::pointer_type Variable::perform_and(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_and(valueStack);
	else
		return valueStack.top()->perform_and(valueStack);
}

/*@Brief Performs nand operation with variables*/
Operand::pointer_type Variable::perform_nand(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_nand(valueStack);
	else
		return valueStack.top()->perform_nand(valueStack);
}

/*@Brief Performs nor operation with variables*/
Operand::pointer_type Variable::perform_nor(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_nor(valueStack);
	else
		return valueStack.top()->perform_nor(valueStack);
}

/*@Brief Performs or operation with variables*/
Operand::pointer_type Variable::perform_or(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_or(valueStack);
	else
		return valueStack.top()->perform_or(valueStack);
}

/*@Brief Performs xor operation with variables*/
Operand::pointer_type Variable::perform_xor(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_xor(valueStack);
	else
		return valueStack.top()->perform_xor(valueStack);
}

/*@Brief Performs or operation with variables*/
Operand::pointer_type Variable::perform_xnor(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_xnor(valueStack);
	else
		return valueStack.top()->perform_xnor(valueStack);
}


/*@Brief Performs modulus operation with variables*/
Operand::pointer_type Variable::perform_modulus(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_modulus(valueStack);
	else
		return valueStack.top()->perform_modulus(valueStack);
}

/*@Brief Performs power operation with variables*/
Operand::pointer_type Variable::perform_power(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_pow(valueStack);
	else
		return valueStack.top()->perform_pow(valueStack);
}


/*@Brief Performs equality operation with variables*/
Operand::pointer_type Variable::perform_equality(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_equality(valueStack);
	else
		return valueStack.top()->perform_equality(valueStack);
}

/*@Brief Performs inequality operation with variables*/
Operand::pointer_type Variable::perform_inequality(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_inequality(valueStack);
	else
		return valueStack.top()->perform_inequality(valueStack);
}

/*@Brief Performs greater than operation with variables*/
Operand::pointer_type Variable::perform_greater(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_greater(valueStack);
	else
		return valueStack.top()->perform_greater(valueStack);
}

/*@Brief Performs greater than equal to operation with variables*/
Operand::pointer_type Variable::perform_greater_equal(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_greater_equal(valueStack);
	else
		return valueStack.top()->perform_greater_equal(valueStack);
}

/*@Brief Performs less than operation with variables*/
Operand::pointer_type Variable::perform_less(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_less(valueStack);
	else
		return valueStack.top()->perform_less(valueStack);
}

/*@Brief Performs less than or equal to than operation with variables*/
Operand::pointer_type Variable::perform_less_equal(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_less_equal(valueStack);
	else
		return valueStack.top()->perform_less_equal(valueStack);
}

/*@Brief Performs identity operation with variables*/
Operand::pointer_type Variable::perform_identity(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_identity(valueStack);
}

/*@Brief Performs negation operation with variables*/
Operand::pointer_type Variable::perform_negation(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_negation(valueStack);
}

/*@Brief Performs factorial operation with variables*/
Operand::pointer_type Variable::perform_factorial(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_factorial(valueStack);
}

/*@Brief Performs abs function with variables*/
Operand::pointer_type Variable::perform_abs(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_abs(valueStack);
}

/*@Brief Performs arccos function with variables*/
Operand::pointer_type Variable::perform_arccos(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_arccos(valueStack);
}

/*@Brief Performs arcsin function with variables*/
Operand::pointer_type Variable::perform_arcsin(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_arcsin(valueStack);
}

/*@Brief Performs arctan function with variables*/
Operand::pointer_type Variable::perform_arctan(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_arctan(valueStack);
}

/*@Brief Performs cos function with variables*/
Operand::pointer_type Variable::perform_cos(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_cos(valueStack);
}

/*@Brief Performs ceil function with variables*/
Operand::pointer_type Variable::perform_ceil(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_ceil(valueStack);
}

/*@Brief Performs floor function with variables*/
Operand::pointer_type Variable::perform_floor(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_floor(valueStack);
}

/*@Brief Performs exp function with variables*/
Operand::pointer_type Variable::perform_exp(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_exp(valueStack);
}

/*@Brief Performs lb function with variables*/
Operand::pointer_type Variable::perform_lb(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_lb(valueStack);
}

/*@Brief Performs ln function with variables*/
Operand::pointer_type Variable::perform_ln(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_ln(valueStack);
}

/*@Brief Performs log function with variables*/
Operand::pointer_type Variable::perform_log(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_log(valueStack);
}

/*@Brief Performs sin function with variables*/
Operand::pointer_type Variable::perform_sin(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_sin(valueStack);
}

/*@Brief Performs sqrt function with variables*/
Operand::pointer_type Variable::perform_sqrt(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_sqrt(valueStack);
}

/*@Brief Performs tan function with variables*/
Operand::pointer_type Variable::perform_tan(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_tan(valueStack);
}

/*@Brief Performs fib function with variables*/
Operand::pointer_type Variable::perform_fib(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_fib(valueStack);
}

/*@Brief Performs pel function with variables*/
Operand::pointer_type Variable::perform_pel(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_pel(valueStack);
}

/*@Brief Performs syl function with variables*/
Operand::pointer_type Variable::perform_syl(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_syl(valueStack);
}

/*@Brief Performs max function with variables*/
Operand::pointer_type Variable::perform_max(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_max(valueStack);
	else
		return valueStack.top()->perform_max(valueStack);
}

/*@Brief Performs min function with variables*/
Operand::pointer_type Variable::perform_min(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_min(valueStack);
	else
		return valueStack.top()->perform_min(valueStack);
}

/*@Brief Performs pow function with variables*/
Operand::pointer_type Variable::perform_pow(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_pow(valueStack);
	else
		return valueStack.top()->perform_pow(valueStack);
}

/*@Brief Performs arctan2 function with variables*/
Operand::pointer_type Variable::perform_arctan2(std::stack<Operand::pointer_type>&valueStack)
{
	Variable::value_type variableValue = nullptr;
	/*Check which operand is the variable*/
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.pop();
	if (is<Variable>(firstOperand))
	{
		//Check what type of object the variable is holding
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(secondOperand);

	}
	else if (is<Variable>(secondOperand))
	{
		variableValue = get_value();
		valueStack.push(variableValue);
		valueStack.push(firstOperand);

	}
	if (variableValue->get_operand_precedence() >= valueStack.top()->get_operand_precedence())
		return variableValue->perform_arctan2(valueStack);
	else
		return valueStack.top()->perform_arctan2(valueStack);
}

/*@Brief Performs Result function with variables*/
Operand::pointer_type Variable::perform_result(std::stack<Operand::pointer_type>&valueStack)
{
	return get_value()->perform_result(valueStack);
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
