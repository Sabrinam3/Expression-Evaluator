/**	@file: ut_tokens_main.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.1.0
	@date 2017-11-23
	@note Compiles under Visual C++ 15.4.4

	@brief Token unit test.
	*/

// unit test library
#define BOOST_TEST_MODULE TokensUnitTest
#include <boost/test/auto_unit_test.hpp>

// Tokenizer system
#include "../ee_common/inc/boolean.hpp"
#include "../ee_common/inc/function.hpp"
#include "../ee_common/inc/integer.hpp"
#include "../ee_common/inc/operator.hpp"
#include "../ee_common/inc/pseudo_operation.hpp"
#include "../ee_common/inc/real.hpp"
#include "../ee_common/inc/variable.hpp"
#include "../ee_common/inc/token.hpp"

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <string>
using namespace std;

#include "../phase_list/ut_test_phase.hpp"

#if TEST_TOKENS

// Test the root type of the Token hierarchy.
BOOST_AUTO_TEST_CASE(token_test) {
	auto tkn = make<Token>();
	BOOST_CHECK(is<Token>(tkn));
	BOOST_CHECK_EQUAL(tkn->to_string(), "<Token>");
}

// Test the PseudoOperation types
// ==============================
#if TEST_PARENTHESIS
BOOST_AUTO_TEST_CASE(left_parenthesis_token_test) { 
	auto tkn = make<LeftParenthesis>();
	BOOST_CHECK(is<Token>(tkn));
	BOOST_CHECK(is<PseudoOperation>(tkn));
	BOOST_CHECK(is<Parenthesis>(tkn));
	BOOST_CHECK(is<LeftParenthesis>(tkn));
	BOOST_CHECK(!is<RightParenthesis>(tkn));
	BOOST_CHECK_EQUAL(tkn->to_string(), "<LeftParenthesis>");
}
BOOST_AUTO_TEST_CASE(right_parenthesis_token_test) { 
	auto tkn = make<RightParenthesis>();
	BOOST_CHECK(is<Token>(tkn));
	BOOST_CHECK(is<PseudoOperation>(tkn));
	BOOST_CHECK(is<Parenthesis>(tkn));
	BOOST_CHECK(!is<LeftParenthesis>(tkn));
	BOOST_CHECK(is<RightParenthesis>(tkn));
	BOOST_CHECK_EQUAL(tkn->to_string(), "<RightParenthesis>");
}
#endif

#if TEST_FUNCTION && TEST_MULTI_ARG
BOOST_AUTO_TEST_CASE(separator_token_test) {
	auto tkn = make<ArgumentSeparator>();
	BOOST_CHECK(is<Token>(tkn));
	BOOST_CHECK(is<PseudoOperation>(tkn));
	BOOST_CHECK(!is<Parenthesis>(tkn));
	BOOST_CHECK(is<ArgumentSeparator>(tkn));
	BOOST_CHECK_EQUAL(tkn->to_string(), "<ArgumentSeparator>");
}
#endif


// Test the Operand types
// ==============================
#if TEST_INTEGER
BOOST_AUTO_TEST_CASE(integer_test) { 
	BOOST_CHECK(Integer().get_value() == 0);
	BOOST_CHECK(Integer(42).get_value() == 42);
	BOOST_CHECK(
		Integer(Integer::value_type("123456789012345678901234567890")).get_value() ==
		Integer::value_type("123456789012345678901234567890"));

	auto i = make<Integer>();
	BOOST_CHECK(is<Token>(i));
	BOOST_CHECK(!is<Operation>(i));
	BOOST_CHECK(is<Operand>(i));
#if TEST_BOOLEAN
	BOOST_CHECK(!is<Boolean>(i));
#endif
#if TEST_REAL
	BOOST_CHECK(!is<Real>(i));
#endif
#if TEST_VARIABLE
	BOOST_CHECK(!is<Variable>(i));
#endif
	BOOST_CHECK(is<Integer>(i));
}
#endif // TEST_INTEGER



#if TEST_REAL
BOOST_AUTO_TEST_CASE(real_test) { 
	BOOST_CHECK(Real().get_value() == 0.0);
	BOOST_CHECK(Real(4.2).get_value() == 4.2);
	BOOST_CHECK(
		Real(Real::value_type("12345678901234567890.1234567890")).get_value() ==
		Real::value_type("12345678901234567890.1234567890"));

	auto i = make<Real>();
	BOOST_CHECK(is<Token>(i));
	BOOST_CHECK(!is<Operation>(i));
	BOOST_CHECK(is<Operand>(i));
#if TEST_BOOLEAN
	BOOST_CHECK(!is<Boolean>(i));
#endif
#if TEST_INTEGER
	BOOST_CHECK(!is<Integer>(i));
#endif
#if TEST_VARIABLE
	BOOST_CHECK(!is<Variable>(i));
#endif
	BOOST_CHECK(is<Real>(i));

	auto e = make<E>();
	BOOST_CHECK(is<Token>(e));
	BOOST_CHECK(!is<Operation>(e));
	BOOST_CHECK(is<Operand>(e));
#if TEST_BOOLEAN
	BOOST_CHECK(!is<Boolean>(e));
#endif
#if TEST_INTEGER
	BOOST_CHECK(!is<Integer>(e));
#endif
#if TEST_VARIABLE
	BOOST_CHECK(!is<Variable>(e));
#endif
	BOOST_CHECK(is<Real>(e));
	BOOST_CHECK(!is<Pi>(e));
	BOOST_CHECK(is<E>(e));

	auto pi = make<Pi>();
	BOOST_CHECK(is<Token>(pi));
	BOOST_CHECK(!is<Operation>(pi));
	BOOST_CHECK(is<Operand>(pi));
#if TEST_BOOLEAN
	BOOST_CHECK(!is<Boolean>(pi));
#endif
#if TEST_INTEGER
	BOOST_CHECK(!is<Integer>(pi));
#endif
#if TEST_VARIABLE
	BOOST_CHECK(!is<Variable>(pi));
#endif
	BOOST_CHECK(is<Real>(pi));
	BOOST_CHECK(!is<E>(pi));
	BOOST_CHECK(is<Pi>(pi));
}
#endif // TEST_REAL


#if TEST_BOOLEAN
BOOST_AUTO_TEST_CASE(boolean_test) {
	BOOST_CHECK(Boolean(false).get_value() == false);
	BOOST_CHECK(Boolean(true).get_value() == true);
	BOOST_CHECK(False().get_value() == false); 
	BOOST_CHECK(True().get_value() == true);

	auto b = make<Boolean>(false);
	BOOST_CHECK(is<Token>(b));
	BOOST_CHECK(!is<Operation>(b));
	BOOST_CHECK(is<Operand>(b));
	BOOST_CHECK(is<Boolean>(b));
#if TEST_INTEGER
	BOOST_CHECK(!is<Integer>(b));
#endif
#if TEST_VARIABLE
	BOOST_CHECK(!is<Variable>(b));
#endif
#if TEST_REAL
	BOOST_CHECK(!is<Real>(b));
#endif

	auto t = make<True>(); 
	BOOST_CHECK(is<Token>(t));
	BOOST_CHECK(!is<Operation>(t));
	BOOST_CHECK(is<Operand>(t));
	BOOST_CHECK(is<Boolean>(t));
#if TEST_INTEGER
	BOOST_CHECK(!is<Integer>(t));
#endif
#if TEST_VARIABLE
	BOOST_CHECK(!is<Variable>(t));
#endif
#if TEST_REAL
	BOOST_CHECK(!is<Real>(t));
#endif
	BOOST_CHECK(is<True>(t));
	BOOST_CHECK(!is<False>(t));

	auto f = make<False>();
	BOOST_CHECK(is<Token>(f));
	BOOST_CHECK(!is<Operation>(f));
	BOOST_CHECK(is<Operand>(f));
	BOOST_CHECK(is<Boolean>(f));

#if TEST_INTEGER
	BOOST_CHECK(!is<Integer>(f));
#endif
#if TEST_VARIABLE
	BOOST_CHECK(!is<Variable>(f));
#endif
#if TEST_REAL
	BOOST_CHECK(!is<Real>(f));
#endif
	BOOST_CHECK(!is<True>(f));
	BOOST_CHECK(is<False>(f));
}
#endif // TEST_BOOLEAN



#if TEST_VARIABLE
BOOST_AUTO_TEST_CASE(variable_test) {
	Integer::pointer_type pi(new Integer(4));
	auto v = make<Variable>();
	Variable::pointer_type pv = convert<Variable>(v);
	pv->set_value(convert<Operand>(pi));
	BOOST_CHECK(pv->get_value()->to_string() == pi->to_string());

	BOOST_CHECK(is<Token>(v));
	BOOST_CHECK(!is<Operation>(v));
	BOOST_CHECK(is<Operand>(v));
#if TEST_BOOLEAN
	BOOST_CHECK(!is<Boolean>(v));
#endif
#if TEST_INTEGER
	BOOST_CHECK(!is<Integer>(v));
#endif
#if TEST_REAL
	BOOST_CHECK(!is<Real>(v));
#endif
	BOOST_CHECK(is<Variable>(v));
}
#endif // TEST_VARIABLE



// Test the Operation types
// ==============================
#if TEST_UNARY_OPERATOR 
typedef boost::mpl::list<Identity, Negation
#if TEST_BOOLEAN
	, Not
#endif
#if TEST_POSTFIX_OPERATOR 
	, PostfixOperator
#endif
> unary_test_types;
BOOST_AUTO_TEST_CASE_TEMPLATE(unary_operator_test, T, unary_test_types) {
	auto tkn = make<T>();
	BOOST_CHECK(!is<Operand>(tkn));
	BOOST_CHECK(!is<PseudoOperation>(tkn));
	BOOST_CHECK(is<Operation>(tkn));

	BOOST_CHECK(is<Operator>(tkn));
#if TEST_FUNCTION
	BOOST_CHECK(!is<Function>(tkn));
#endif

	BOOST_CHECK(is<NonAssociative>(tkn)); 
#if TEST_BINARY_OPERATOR
	BOOST_CHECK(!is<BinaryOperator>(tkn));
#endif
	BOOST_CHECK(is<UnaryOperator>(tkn));

	BOOST_CHECK(is<T>(tkn));

	// Can be only one of the following.
	auto sum = is<Identity>(tkn) + is<Negation>(tkn)
#if TEST_BOOLEAN
		+ is<Not>(tkn)
#endif
#if TEST_POSTFIX_OPERATOR
		+ is<PostfixOperator>(tkn)
#endif
		;
	BOOST_CHECK_EQUAL(sum, 1);
}
#endif


#if TEST_BINARY_OPERATOR
typedef boost::mpl::list<Addition, And, Division
#if TEST_RELATIONAL_OPERATOR
	, Equality, Greater, GreaterEqual, Inequality, Less, LessEqual
#endif
	, Modulus, Multiplication
#if TEST_BOOLEAN
	, Nand, Nor, Or
#endif
	, Subtraction
#if TEST_BOOLEAN
	, Xnor, Xor
#endif
> lassoc_binary_test_types;
BOOST_AUTO_TEST_CASE_TEMPLATE(LAssoc_binary_operator_test, T, lassoc_binary_test_types) { 
	auto tkn = make<T>();
	BOOST_CHECK(!is<Operand>(tkn));
	BOOST_CHECK(!is<PseudoOperation>(tkn));
	BOOST_CHECK(is<Operation>(tkn));

	BOOST_CHECK(is<Operator>(tkn));
#if TEST_FUNCTION
	BOOST_CHECK(!is<Function>(tkn));
#endif

	BOOST_CHECK(!is<NonAssociative>(tkn));
	BOOST_CHECK(!is<UnaryOperator>(tkn));

	BOOST_CHECK(is<BinaryOperator>(tkn));
#if TEST_RIGHT_ASSOCIATIVE_OPERATOR
	BOOST_CHECK(!is<RAssocOperator>(tkn));
	BOOST_CHECK(is<LAssocOperator>(tkn));
#endif
	BOOST_CHECK(is<T>(tkn));

	// Can be only one of the following.
	auto sum = is<Addition>(tkn) + is<And>(tkn) + is<Division>(tkn) + is<Modulus>(tkn) + is<Multiplication>(tkn) + is<Subtraction>(tkn)
#if TEST_RELATIONAL_OPERATOR
		+ is<Equality>(tkn) + is<Greater>(tkn) + is<GreaterEqual>(tkn) + is<Inequality>(tkn) + is<Less>(tkn) + is<LessEqual>(tkn)
#endif
#if TEST_BOOLEAN
		+ is<Nand>(tkn) + is<Nor>(tkn) + is<Or>(tkn) + is<Xnor>(tkn) + is<Xor>(tkn)
#endif
		;

	BOOST_CHECK_EQUAL(sum, 1);
}


#if TEST_RIGHT_ASSOCIATIVE_OPERATOR
typedef boost::mpl::list<Assignment, Power> rassoc_binary_test_types;
BOOST_AUTO_TEST_CASE_TEMPLATE(RAssoc_binary_operator_test, T, rassoc_binary_test_types) {
	auto tkn = make<T>();
	BOOST_CHECK(!is<Operand>(tkn));
	BOOST_CHECK(!is<PseudoOperation>(tkn));
	BOOST_CHECK(is<Operation>(tkn));

	BOOST_CHECK(is<Operator>(tkn));
#if TEST_FUNCTION
	BOOST_CHECK(!is<Function>(tkn));
#endif
	BOOST_CHECK(!is<NonAssociative>(tkn));
#if TEST_UNARY_OPERATOR
	BOOST_CHECK(!is<UnaryOperator>(tkn));
#endif
	BOOST_CHECK(is<BinaryOperator>(tkn));

	BOOST_CHECK(is<RAssocOperator>(tkn));
	BOOST_CHECK(!is<LAssocOperator>(tkn));

	BOOST_CHECK(is<T>(tkn));

	// Can be only one of the following.
	BOOST_CHECK(is<Assignment>(tkn) + is<Power>(tkn) == 1);
}
#endif
#endif

#if TEST_POSTFIX_OPERATOR
BOOST_AUTO_TEST_CASE(postfix_operator_test) {
	auto tkn = make<Factorial>();
	BOOST_CHECK(!is<Operand>(tkn));
	BOOST_CHECK(!is<PseudoOperation>(tkn));
	BOOST_CHECK(is<Operation>(tkn));

	BOOST_CHECK(is<Operator>(tkn));
#if TEST_FUNCTION
	BOOST_CHECK(!is<Function>(tkn));
#endif
	BOOST_CHECK(is<NonAssociative>(tkn));
	BOOST_CHECK(!is<BinaryOperator>(tkn));

	BOOST_CHECK(is<UnaryOperator>(tkn));

	BOOST_CHECK(is<PostfixOperator>(tkn));
	BOOST_CHECK(is<Factorial>(tkn));
}
#endif

#if TEST_FUNCTION
#if TEST_SINGLE_ARG
typedef boost::mpl::list<Abs, Arccos, Arcsin, Arctan, Ceil, Cos, Exp, Floor, Lb, Ln, Log, Result, Sin, Sqrt, Tan> single_arg_function_test_types;
BOOST_AUTO_TEST_CASE_TEMPLATE(Single_arg_function_test, T, single_arg_function_test_types) {
	auto tkn = make<T>();
	BOOST_CHECK(!is<Operand>(tkn));
	BOOST_CHECK(!is<PseudoOperation>(tkn));
	BOOST_CHECK(is<Operation>(tkn));

	BOOST_CHECK(!is<Operator>(tkn));
	BOOST_CHECK(is<Function>(tkn));
	BOOST_CHECK(is<OneArgFunction>(tkn));
	BOOST_CHECK(!is<TwoArgFunction>(tkn));

	BOOST_CHECK(is<T>(tkn));

	// Can be only one of the following.
	BOOST_CHECK(
		is<Abs>(tkn) + is<Arccos>(tkn) + is<Arcsin>(tkn) + is<Arctan>(tkn) +
		is<Ceil>(tkn) + is<Cos>(tkn) + is<Exp>(tkn) + is<Floor>(tkn) +
		is<Lb>(tkn) + is<Ln>(tkn) + is<Log>(tkn) + is<Result>(tkn) +
		is<Sin>(tkn) + is<Sqrt>(tkn) + is<Tan>(tkn) + is<Fib>(tkn) +
		is<Pel>(tkn) + is<Syl>(tkn)
		== 1);
}
#endif
#if TEST_MULTI_ARG
typedef boost::mpl::list<Arctan2, Max, Min, Pow> double_arg_function_test_types;
BOOST_AUTO_TEST_CASE_TEMPLATE(Double_arg_function_test, T, double_arg_function_test_types) {
	auto tkn = make<T>();
	BOOST_CHECK(!is<Operand>(tkn));
	BOOST_CHECK(!is<PseudoOperation>(tkn));
	BOOST_CHECK(is<Operation>(tkn));

	BOOST_CHECK(!is<Operator>(tkn));
	BOOST_CHECK(is<Function>(tkn));
	BOOST_CHECK(!is<OneArgFunction>(tkn));
	BOOST_CHECK(is<TwoArgFunction>(tkn));

	BOOST_CHECK(is<T>(tkn));

	// Can be only one of the following.
	BOOST_CHECK(
		is<Arctan2>(tkn) + is<Max>(tkn) + is<Min>(tkn) + is<Pow>(tkn)
		== 1);
}
#endif
#endif

#endif // TEST_TOKENS


/*=============================================================

Revision History

Version 1.1.0: 2017-11-23
Updated to Visual C++ 15.4.4
New hierarchy tests.

Version 1.0.0: 2014-10-29
Updated to Visual C++ 12

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 0.1.0: 2012-11-15
Added BinaryInteger, Binary <function>

Version 0.0.1: 2012-11-13
C++ 11 cleanup.

Version 0.0.0: 2009-11-30
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
