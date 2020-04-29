#if !defined(GUARD_operand_hpp20091125_)
#define GUARD_operand_hpp20091125_

/** @file: operand.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.1.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110
	@Implemented by Sabrina Tessier on 2018-11-10
	@brief Operand class declaration.
	*/

#include "token.hpp"
#include <cassert>
#include<boost/lexical_cast.hpp>
#include <stack>

/*Precendence table to handle multiple types in expressions*/
typedef enum{ BOOLEAN = 0, INTEGER, REAL, VARIABLE} operand_precedence_type;

/*@Brief- returns an operand's precedence category*/
#define DEF_OPERAND_PRECEDENCE(operand_category) public: operand_precedence_type get_operand_precedence() const override {return operand_category;}

class Operand : public Token {
public:
	DEF_POINTER_TYPE(Operand)
		/*Get operand precedence method declaration*/
		virtual operand_precedence_type get_operand_precedence()  const = 0;
		/*Operand method declarations*/
		/*Binary operations*/
		virtual Operand::pointer_type perform_addition(std::stack<Operand::pointer_type> &valueStack) = 0;
		virtual Operand::pointer_type perform_subtraction(std::stack<Operand::pointer_type> &valueStack) = 0;
		virtual Operand::pointer_type perform_multiplication(std::stack<Operand::pointer_type> &valueStack) = 0;
		virtual Operand::pointer_type perform_division(std::stack<Operand::pointer_type> &valueStack) = 0;
		virtual Operand::pointer_type perform_not(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_modulus(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_power(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_and(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_nand(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_nor(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_or(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_xor(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_xnor(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_equality(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_inequality(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_greater(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_greater_equal(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_less(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_less_equal(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_assignment(std::stack<Operand::pointer_type>&valueStack) = 0;
		/*Unary operations*/
		virtual Operand::pointer_type perform_identity(std::stack<Operand::pointer_type> &valueStack) = 0;
		virtual Operand::pointer_type perform_negation(std::stack<Operand::pointer_type> &valueStack) = 0;
		virtual Operand::pointer_type perform_factorial(std::stack<Operand::pointer_type>&valueStack) = 0;
		/*One arg functions*/
		virtual Operand::pointer_type perform_abs(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_arccos(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_arcsin(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_arctan(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_cos(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_ceil(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_floor(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_exp(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_lb(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_ln(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_log(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_sin(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_sqrt(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_tan(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_fib(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_pel(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_syl(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_result(std::stack<Operand::pointer_type>&valueStack) = 0;
		/*Two arg functions*/
		virtual Operand::pointer_type perform_max(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_min(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_pow(std::stack<Operand::pointer_type>&valueStack) = 0;
		virtual Operand::pointer_type perform_arctan2(std::stack<Operand::pointer_type>&valueStack) = 0;
};

/** Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, typename U>
inline Operand::pointer_type make_operand( U const& param ) {
	return Operand::pointer_type( new T(param) );
}


/** Gets the value from an operand. */
template <typename OPERAND_TYPE>
typename OPERAND_TYPE::value_type get_value( Token::pointer_type const& operand ) {
	assert( is<OPERAND_TYPE>( operand ) );
	return dynamic_cast<OPERAND_TYPE*>( operand.get() )->get_value();
}


/*=============================================================

Revision History

Version 0.1.1: 2012-11-13
C++ cleanup.

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

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
#endif // GUARD_operand_hpp20091125_
