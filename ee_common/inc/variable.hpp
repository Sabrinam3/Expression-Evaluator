#if !defined(GUARD_variable_hpp20091126_)
#define GUARD_variable_hpp20091126_

/** @file: variable.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visual C++ v110
	@Implemented by Sabrina Tessier on 2018-11-10

	@brief Variable class declaration.
	*/

#include "operand.hpp"
#include "RPNEvaluator.hpp"

class Variable :public Operand {
public:
	DEF_POINTER_TYPE(Variable)
	DEF_OPERAND_PRECEDENCE(VARIABLE)
		using value_type = Operand::pointer_type;
private:
	Operand::pointer_type value_;
public:
	void set_value(Operand::pointer_type a) { value_ = a; }
	Operand::pointer_type get_value()const { return value_; }
	string_type to_string() const;
	//Variable operation function declarations
			/*Binary operations*/
	Operand::pointer_type perform_addition(std::stack<Operand::pointer_type> &valueStack) override;
	Operand::pointer_type perform_multiplication(std::stack<Operand::pointer_type> &valueStack) override;
	Operand::pointer_type perform_subtraction(std::stack<Operand::pointer_type> &valueStack) override;
	Operand::pointer_type perform_division(std::stack<Operand::pointer_type> &valueStack) override;
	Operand::pointer_type perform_not(std::stack<Operand::pointer_type> &valueStack) override;
	Operand::pointer_type perform_modulus(std::stack<Operand::pointer_type> &valueStack) override;
	Operand::pointer_type perform_power(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_and(std::stack<Operand::pointer_type> &valueStack) override;
	Operand::pointer_type perform_nand(std::stack<Operand::pointer_type> &valueStack) override;
	Operand::pointer_type perform_nor(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_or(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_xor(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_xnor(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_equality(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_inequality(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_greater(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_greater_equal(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_less(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_less_equal(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_assignment(std::stack<Operand::pointer_type>&valueStack) override;
	/*Unary operations*/
	Operand::pointer_type perform_identity(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_negation(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_factorial(std::stack<Operand::pointer_type>&valueStack) override;
	/*One arg functions*/
	Operand::pointer_type perform_abs(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_arccos(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_arcsin(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_arctan(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_cos(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_ceil(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_floor(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_exp(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_lb(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_ln(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_log(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_sin(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_sqrt(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_tan(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_fib(std::stack<Operand::pointer_type>&valueStack)  override;
	Operand::pointer_type perform_pel(std::stack<Operand::pointer_type>&valueStack)  override;
	Operand::pointer_type perform_syl(std::stack<Operand::pointer_type>&valueStack)  override;
	Operand::pointer_type perform_result(std::stack<Operand::pointer_type>&valueStack) override;
	/*Two arg functions*/
	Operand::pointer_type perform_max(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_min(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_pow(std::stack<Operand::pointer_type>&valueStack) override;
	Operand::pointer_type perform_arctan2(std::stack<Operand::pointer_type>&valueStack) override;
};

#endif // GUARD_variable_hpp20091126_
