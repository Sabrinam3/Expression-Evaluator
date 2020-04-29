#if !defined(GUARD_integer_hpp20091125_)
#define GUARD_integer_hpp20091125_

/**@file: integer.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-15
	@note Compiles under Visual C++ v110 
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Integer class declaration.
	*/

#include "operand.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/debug_adaptor.hpp>
using namespace std;
extern std::vector<Operand::pointer_type> resultTypes;
/** Integer token. */
class Integer : public Operand {
public:
	using value_type = boost::multiprecision::cpp_int;
	DEF_POINTER_TYPE(Integer)
	DEF_OPERAND_PRECEDENCE(INTEGER)
private:
	value_type value_;
public:
	Integer(value_type value = 0 )
		: value_( value ) { }

	value_type get_value() const { return value_; }
	string_type to_string() const;

	/*Integer functionality method declarations*/
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

/*Binary Integer Token*/
class BinaryInteger :public Integer
{
	DEF_POINTER_TYPE(BinaryInteger)
public:
	BinaryInteger(Integer::value_type value) : Integer(value) {}
};

/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Converted Integer::value_type to boost::multiprecision::cpp_int
Removed BinaryInteger

Version 0.2.0: 2012-11-15
Added BinaryInteger.

Version 0.1.1: 2012-11-13
C++ 11 cleanup.

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.
Switched __int64 to long long.

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
#endif // GUARD_integer_hpp20091125_
