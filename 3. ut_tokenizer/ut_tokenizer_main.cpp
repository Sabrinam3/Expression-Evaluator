/** @file: ut_tokenizer_main.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 2.1.0
	@date 2017-11-23
	@note Compiles under Visual C++ 15.4.4

	@brief Tokenizer Unit Test for Expression Evaluator Project
	*/

// unit test library
//#define _CRT_SECURE_NO_WARNINGS
#define BOOST_TEST_MODULE TokenizerUnitTest
#include <boost/test/unit_test.hpp>
#include <iostream>

// Tokenizer system
#include "../ee_common/inc/tokenizer.hpp"
#include "../ee_common/inc/boolean.hpp"
#include "../ee_common/inc/function.hpp"
#include "../ee_common/inc/integer.hpp"
#include "../ee_common/inc/operator.hpp"
#include "../ee_common/inc/pseudo_operation.hpp"
#include "../ee_common/inc/real.hpp"
#include "../ee_common/inc/variable.hpp"

// std
#include <string>
using namespace std;

#include "../phase_list/ut_test_phase.hpp"


#if TEST_TOKENIZER

#pragma region test_support
// ==============================================================================
// TEST CASE SUPPORT
// ==============================================================================

/** Performs tokenizer test case

	1. Tokenizes the expression.
	2. Checks that returned token list matches correct list.

	@param expression [in] The expression to tokenize.
	*/
bool test(Tokenizer::string_type expression, TokenList const & correct) {
	Tokenizer tokenizer;
	TokenList tokens = tokenizer.tokenize(expression);
	bool ok = true;
 	ok = ok && (correct.size() == tokens.size());
	size_t n = std::min(correct.size(), tokens.size());
	for (size_t i = 0; i < n; ++i) {
		bool match =  correct[i] == tokens[i];
		BOOST_CHECK_MESSAGE(match, "Token [" << i << "] = " << tokens[i]->to_string() << " should be " << correct[i]->to_string());
		ok = ok && match;
	}
	return ok;
}
#pragma endregion // test_support


#pragma region trivial_cases
// ==============================================================================
// Trivial Test Cases
// ==============================================================================
BOOST_AUTO_TEST_CASE(lexer_no_token) {
	BOOST_CHECK(test("", TokenList({	})));
}


BOOST_AUTO_TEST_CASE( unknown_token ) {
	try {
		Tokenizer tkn;
		TokenList tl = tkn.tokenize("@");
		BOOST_FAIL("XBadCharacter exception not thrown");
	}
	catch (Tokenizer::XBadCharacter& e) {
		string s("Tokenizer::Bad character in expression.");
		string es(e.what());
		BOOST_CHECK(s == es);
		BOOST_CHECK(e.get_expression() == "@");
		BOOST_CHECK(e.get_location() == 0);
	}
}
#pragma endregion


#if TEST_INTEGER //all integer test cases pass
	// ==============================================================================
	// Integer Test Cases
	// ==============================================================================
	BOOST_AUTO_TEST_CASE(lexer_single_integer_1234) {
		BOOST_CHECK(test("1234", TokenList({ make<Integer>(1234) }))); 
	}

	BOOST_AUTO_TEST_CASE(lexer_single_integer_0) {
		BOOST_CHECK(test("0", TokenList({ make<Integer>(0) }))); 
	}

	BOOST_AUTO_TEST_CASE(lexer_single_integer_big) {
		BOOST_CHECK(test("1234567890123456789012345678901234567890", TokenList({ make<Integer>(Integer::value_type("1234567890123456789012345678901234567890")) })));
	}

	BOOST_AUTO_TEST_CASE(lexer_two_integers) {
		BOOST_CHECK(test("23 42", TokenList({ make<Integer>(23), make<Integer>(42) }))); 
	}


	#if TEST_UNARY_OPERATOR
 		BOOST_AUTO_TEST_CASE(lexer_operator_identity) { 
			BOOST_CHECK(test("++2", TokenList({
				make<Identity>(), make<Identity>(), make<Integer>(2)
			})));
		}

		BOOST_AUTO_TEST_CASE(lexer_operator_negation) {
			BOOST_CHECK(test("--2", TokenList({
				make<Negation>(), make<Negation>(), make<Integer>(2)
			})));
		}

		BOOST_AUTO_TEST_CASE(lexer_operator_factorial) {
			BOOST_CHECK(test("42!", TokenList({ make<Integer>(42), make<Factorial>() })));
		}
	#endif // TEST_UNARY_OPERATOR


	#if TEST_BINARY_OPERATOR
		BOOST_AUTO_TEST_CASE(lexer_single_operator_multiplication) {
			BOOST_CHECK(test("1*2", TokenList({
				make<Integer>(1), make<Multiplication>(), make<Integer>(2)
			})));
		}
	BOOST_AUTO_TEST_CASE(lexer_single_operator_division) {
			BOOST_CHECK(test("1/2", TokenList({
				make<Integer>(1), make<Division>(), make<Integer>(2)
			})));
		}
		BOOST_AUTO_TEST_CASE(lexer_single_operator_modulus) {
			BOOST_CHECK(test("1%2", TokenList({
				make<Integer>(1), make<Modulus>(), make<Integer>(2)
			})));
		}
	
		BOOST_AUTO_TEST_CASE(lexer_single_operator_addition) {
			BOOST_CHECK(test("1+2", TokenList({
				make<Integer>(1), make<Addition>(), make<Integer>(2)
			})));
		}
		
		BOOST_AUTO_TEST_CASE(lexer_single_operator_subtraction) {
			BOOST_CHECK(test("1-2", TokenList({
				make<Integer>(1), make<Subtraction>(), make<Integer>(2)
			})));
		}
		
		BOOST_AUTO_TEST_CASE(lexer_single_operator_power) {
			BOOST_CHECK(test("1**2", TokenList({
				make<Integer>(1), make<Power>(), make<Integer>(2)
			})));
		}
	
		BOOST_AUTO_TEST_CASE(lexer_combined_1) {
			BOOST_CHECK(test("1+2*3/4%5", TokenList({
				make<Integer>(1),
				make<Addition>(),
				make<Integer>(2),
				make<Multiplication>(),
				make<Integer>(3),
				make<Division>(),
				make<Integer>(4),
				make<Modulus>(),
				make<Integer>(5)
			})));
		}

		#if TEST_NAMED_OPERATOR
			BOOST_AUTO_TEST_CASE(lexer_single_operator_modulus_name) {
				BOOST_CHECK(test("1 mod 2", TokenList({
					make<Integer>(1), make<Modulus>(), make<Integer>(2)
				})));
			}
		#endif // TEST_NAMED_OPERATOR
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_INTEGER


#if TEST_PARENTHESIS
	#if TEST_INTEGER
		BOOST_AUTO_TEST_CASE(lexer_single_operator_parenthesis) {
			BOOST_CHECK(test("(42)", TokenList({
				make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
			})));
		}
	#endif // TEST_INTEGER

	#if TEST_UNARY_OPERATOR
		BOOST_AUTO_TEST_CASE(lexer_operator_identity_parenthesis) {
			BOOST_CHECK(test("+(++2", TokenList({
				make<Identity>(), make<LeftParenthesis>(), make<Identity>(), make<Identity>(), make<Integer>(2)
			})));
		}

		BOOST_AUTO_TEST_CASE(lexer_operator_negation_parenthesis) {
			BOOST_CHECK(test("-(--2", TokenList({
				make<Negation>(), make<LeftParenthesis>(), make<Negation>(), make<Negation>(), make<Integer>(2)
			})));
		}
	#endif // TEST_UNARY_OPERATOR

	#if TEST_BINARY_OPERATOR
		BOOST_AUTO_TEST_CASE(lexer_combined_2) {
			BOOST_CHECK(test("-(-3--4)-5", TokenList({
				make<Negation>(),
				make<LeftParenthesis>(),
				make<Negation>(),
				make<Integer>(3),
				make<Subtraction>(),
				make<Negation>(),
				make<Integer>(4),
				make<RightParenthesis>(),
				make<Subtraction>(),
				make<Integer>(5)
			})));
		}
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_PARENTHESIS



#if TEST_FUNCTION && TEST_INTEGER
	BOOST_AUTO_TEST_CASE(lexer_single_operator_separator) {
		BOOST_CHECK(test("1,2", TokenList({
			make<Integer>(1), make<ArgumentSeparator>(), make<Integer>(2)
		})));
	}

	BOOST_AUTO_TEST_CASE(lexer_func_abs) {
		BOOST_CHECK(test("abs(42)", TokenList({
			make<Abs>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
		})));
	}
	BOOST_AUTO_TEST_CASE(lexer_func_fib) {
		BOOST_CHECK(test("fib(42)", TokenList({
			make<Fib>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
			})));
	}
	BOOST_AUTO_TEST_CASE(lexer_func_pel) {
		BOOST_CHECK(test("pel(42)", TokenList({
			make<Pel>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
			})));
	}
	BOOST_AUTO_TEST_CASE(lexer_func_syl) {
		BOOST_CHECK(test("syl(42)", TokenList({
			make<Syl>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
			})));
	}
#endif // TEST_FUNCTION

#if TEST_REAL
	// ==============================================================================
	// Real Test Cases
	// ==============================================================================
	BOOST_AUTO_TEST_CASE(lexer_single_real) {
		BOOST_CHECK(test("1234.56", TokenList({ make<Real>(Real::value_type("1234.56")) })));
	}

	BOOST_AUTO_TEST_CASE(lexer_single_real_small) {
		BOOST_CHECK(test("0.000000000000000000000000000000000000004", TokenList({ make<Real>(Real::value_type("0.000000000000000000000000000000000000004")) })));
	}

	BOOST_AUTO_TEST_CASE(lexer_single_real_big) {
		BOOST_CHECK(test("1234567890123456789012345678901234567890.1234567890123456789012345678901234567890",
			TokenList({ make<Real>(Real::value_type("1234567890123456789012345678901234567890.1234567890123456789012345678901234567890")) })));
	}

	BOOST_AUTO_TEST_CASE(lexer_single_pi) { BOOST_CHECK(test("pi", TokenList({ make<Pi>() }))); }
	BOOST_AUTO_TEST_CASE(lexer_single_Pi) { BOOST_CHECK(test("Pi", TokenList({ make<Pi>() }))); }
	BOOST_AUTO_TEST_CASE(lexer_single_PI) { BOOST_CHECK(test("PI", TokenList({ make<Pi>() }))); }
	BOOST_AUTO_TEST_CASE(lexer_single_e) { BOOST_CHECK(test("e", TokenList({ make<E>() }))); }
	BOOST_AUTO_TEST_CASE(lexer_single_E) { BOOST_CHECK(test("E", TokenList({ make<E>() }))); }

	#if TEST_FUNCTION
		#if TEST_SINGLE_ARG
			BOOST_AUTO_TEST_CASE(lexer_func_arccos) {
				BOOST_CHECK(test("arccos(42)", TokenList({
					make<Arccos>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_arcsin) {
				BOOST_CHECK(test("arcsin(42)", TokenList({
					make<Arcsin>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_arctan) {
				BOOST_CHECK(test("arctan(42)", TokenList({
					make<Arctan>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_ceil) {
				BOOST_CHECK(test("ceil(4.2)", TokenList({
					make<Ceil>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_cos) {
				BOOST_CHECK(test("cos(4.2)", TokenList({
					make<Cos>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_exp) {
				BOOST_CHECK(test("exp(4.2)", TokenList({
					make<Exp>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_floor) {
				BOOST_CHECK(test("floor(4.2)", TokenList({
					make<Floor>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_lb) {
				BOOST_CHECK(test("lb(4.2)", TokenList({
					make<Lb>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_ln) {
				BOOST_CHECK(test("ln(4.2)", TokenList({
					make<Ln>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_log) {
				BOOST_CHECK(test("log(4.2)", TokenList({
					make<Log>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_sin) {
				BOOST_CHECK(test("sin(4.2)", TokenList({
					make<Sin>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_sqrt) {
				BOOST_CHECK(test("sqrt(4.2)", TokenList({
					make<Sqrt>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_tan) {
				BOOST_CHECK(test("tan(4.2)", TokenList({
					make<Tan>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
#endif // TEST_SINGLE_ARG

		#if TEST_MULTI_ARG
			BOOST_AUTO_TEST_CASE(lexer_func_arctan2) {
				BOOST_CHECK(test("arctan2(42,123.3)", TokenList({
					make<Arctan2>(), make<LeftParenthesis>(), make<Integer>(42), make<ArgumentSeparator>(),
					make<Real>(Real::value_type("123.3")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_max) {
				BOOST_CHECK(test("max(42,123.3)", TokenList({
					make<Max>(), make<LeftParenthesis>(), make<Integer>(42), make<ArgumentSeparator>(),
					make<Real>(Real::value_type("123.3")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_min) {
				BOOST_CHECK(test("min(42,123.3)", TokenList({
					make<Min>(), make<LeftParenthesis>(), make<Integer>(42), make<ArgumentSeparator>(),
					make<Real>(Real::value_type("123.3")), make<RightParenthesis>()
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_func_pow) {
				BOOST_CHECK(test("pow(42,123.3)", TokenList({
					make<Pow>(), make<LeftParenthesis>(), make<Integer>(42), make<ArgumentSeparator>(),
					make<Real>(Real::value_type("123.3")), make<RightParenthesis>()
				})));
			}
		#endif // TEST_MULTI_ARG
	#endif // TEST_FUNCTION
#endif // TEST_REAL


#if TEST_BOOLEAN
	// ==============================================================================
	// Boolean Test Cases
	// ==============================================================================
	BOOST_AUTO_TEST_CASE(lexer_single_true) { BOOST_CHECK(test("true", TokenList({ make<Boolean>(true) }))); }
	BOOST_AUTO_TEST_CASE(lexer_single_false) { BOOST_CHECK(test("false", TokenList({ make<Boolean>(false) }))); }


	#if TEST_UNARY_OPERATOR
		BOOST_AUTO_TEST_CASE(lexer_bool_operator_not) {
			BOOST_CHECK(test("not false", TokenList({
				make<Not>(), make<False>()
			})));
		}
	#endif // TEST_UNARY_OPERATOR


	#if TEST_BINARY_OPERATOR
		BOOST_AUTO_TEST_CASE(lexer_bool_operator_and) {
			BOOST_CHECK(test("true and false", TokenList({
				make<True>(), make<And>(), make<False>()
			})));
		}

		BOOST_AUTO_TEST_CASE(lexer_bool_operator_or) {
			BOOST_CHECK(test("true or false", TokenList({
				make<True>(), make<Or>(), make<False>()
			})));
		}

		BOOST_AUTO_TEST_CASE(lexer_bool_operator_xor) {
			BOOST_CHECK(test("true xor false", TokenList({
				make<True>(), make<Xor>(), make<False>()
			})));
		}

		BOOST_AUTO_TEST_CASE(lexer_bool_operator_nand) {
			BOOST_CHECK(test("true nand false", TokenList({
				make<True>(), make<Nand>(), make<False>()
			})));
		}

		BOOST_AUTO_TEST_CASE(lexer_bool_operator_nor) {
			BOOST_CHECK(test("true nor false", TokenList({
				make<True>(), make<Nor>(), make<False>()
			})));
		}

		BOOST_AUTO_TEST_CASE(lexer_bool_operator_xnor) {
			BOOST_CHECK(test("true xnor false", TokenList({
				make<True>(), make<Xnor>(), make<False>()
			})));
		}


		#if TEST_RELATIONAL_OPERATOR && TEST_INTEGER
		BOOST_AUTO_TEST_CASE(lexer_bool_operator_equality) {
				BOOST_CHECK(test("3 == 2", TokenList({
					make<Integer>(3), make<Equality>(), make<Integer>(2)
				})));
			}

			BOOST_AUTO_TEST_CASE(lexer_bool_operator_inequality) {
				BOOST_CHECK(test("3 != 2", TokenList({
					make<Integer>(3), make<Inequality>(), make<Integer>(2)
				})));
			}

			BOOST_AUTO_TEST_CASE(lexer_bool_operator_greater) {
				BOOST_CHECK(test("3 > 2", TokenList({
					make<Integer>(3), make<Greater>(), make<Integer>(2)
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_bool_operator_greaterequal) {
				BOOST_CHECK(test("3 >= 2", TokenList({
					make<Integer>(3), make<GreaterEqual>(), make<Integer>(2)
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_bool_operator_less) {
				BOOST_CHECK(test("3 < 2", TokenList({
					make<Integer>(3), make<Less>(), make<Integer>(2)
				})));
			}
			BOOST_AUTO_TEST_CASE(lexer_bool_operator_lessequal) {
				BOOST_CHECK(test("3 <= 2", TokenList({
					make<Integer>(3), make<LessEqual>(), make<Integer>(2)
				})));
			}
		#endif // TEST_RELATIONAL_OPERATOR && TEST_INTEGER
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_BOOLEAN


#if TEST_VARIABLE
	BOOST_AUTO_TEST_CASE(lexer_single_Variable) {
		BOOST_CHECK(test("variable", TokenList({ make<Variable>() })));
	}

	BOOST_AUTO_TEST_CASE(def_ctor_variable) {
		Variable::pointer_type p(new Variable);
		BOOST_CHECK(p->get_value() == 0);
		BOOST_CHECK(p->to_string() == "Variable: null");
	}

	BOOST_AUTO_TEST_CASE(variable_match) {
		Tokenizer tkr;
		TokenList tl = tkr.tokenize("a");
		Token::pointer_type p = tl.front();
		tl.clear();
		tl = tkr.tokenize("a");
		BOOST_CHECK(p.get() == tl.front().get());
	}


	#if TEST_BINARY_OPERATOR && TEST_INTEGER
		BOOST_AUTO_TEST_CASE(lexer_single_operator_assignment) {
			BOOST_CHECK(test("a=2", TokenList({
				make<Variable>(), make<Assignment>(), make<Integer>(2)
			})));
		}
	#endif // TEST_BINARY_OPERATOR && TEST_INTEGER

	#if TEST_FUNCTION && TEST_SINGLE_ARG
		BOOST_AUTO_TEST_CASE(lexer_func_result) {
			BOOST_CHECK(test("result(4)", TokenList({
				make<Result>(), make<LeftParenthesis>(), make<Integer>(4), make<RightParenthesis>()
			})));
		}
	#endif // TEST_FUNCTION && TEST_SINGLE_ARG
#endif // TEST_VARIABLE


#endif // TEST_TOKENIZER



/*=============================================================

Revision History

Version 2.1.0: 2017-11-23
Added Python-style power operator '**'.

Version 2.0.0: 2015-11-05
Visual Studio 2015
TEST_xxxx macros

Version 1.0.0: 2014-10-29
Visual Studio 2013
Uses boost::multiprecision library.

Version 0.2.0: 2012-11-16
Added Bit operators

Version 0.1.0: 2012-11-15
Added BinaryInteger tests.
Added Binary function test.
Added XNumericOverflow test.

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
