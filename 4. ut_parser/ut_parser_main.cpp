/** @file: ut_parser_main.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 2.0.0
	@date 2015-11-05
	@note Compiles under Visual C++ v140

	@brief Parser unit test.
	*/

// unit test library
#define _CRT_SECURE_NO_WARNINGS
#define BOOST_TEST_MODULE ParserUnitTest
#include <boost/test/unit_test.hpp>

// Parser system
#include "../ee_common/inc/parser.hpp"
#include "../ee_common/inc/function.hpp"
#include "../ee_common/inc/integer.hpp"
#include "../ee_common/inc/operator.hpp"
#include "../ee_common/inc/pseudo_operation.hpp"
#include "../ee_common/inc/real.hpp"
#include "../ee_common/inc/variable.hpp"

#include "../phase_list/ut_test_phase.hpp"

#if TEST_PARSER

#pragma region test_support
//=================================================================================================
// MACRO Framework
//=================================================================================================


/** Performs tokenizer test case

	1. Tokenizes the expression.
	2. Checks that returned token list matches correct list.

	@param expression [in] The expression to tokenize.
	*/
bool parse_test(TokenList const& infixTokenList, TokenList const & correct) {
	TokenList postfixTokenList = Parser().parse(infixTokenList);
	bool ok = true;
	ok = ok && (correct.size() == postfixTokenList.size());
	size_t n = std::min(correct.size(), postfixTokenList.size());
	for (size_t i = 0; i < n; ++i) {
		bool match = correct[i] == postfixTokenList[i];
		BOOST_CHECK_MESSAGE(match, "Token [" << i << "] = " << postfixTokenList[i]->to_string() << " should be " << correct[i]->to_string());
		ok = ok && match;
	}
	return ok;
}

#pragma endregion


	BOOST_AUTO_TEST_CASE( parser_empty ) {
		TokenList infixTokenList, postfixTokenList;
		TokenList result = Parser().parse( infixTokenList );
		BOOST_CHECK( result.size() == postfixTokenList.size() );
	}



	#if TEST_INTEGER
		BOOST_AUTO_TEST_CASE(parser_single_number) {
			BOOST_CHECK(parse_test(
				// Test: 42
				TokenList({ make<Integer>(42) }),
				TokenList({ make<Integer>(42) })));
		}



		#if TEST_UNARY_OPERATOR
			BOOST_AUTO_TEST_CASE(parser_single_negative) {
				BOOST_CHECK(parse_test(
					// Test: -42
					TokenList({ make<Negation>(), make<Integer>(42) }),
					TokenList({ make<Integer>(42), make<Negation>() })));
			}
		#endif // TEST_UNARY



		#if TEST_BINARY_OPERATOR
			BOOST_AUTO_TEST_CASE(parser_binary_addition) {
				BOOST_CHECK(parse_test(
					// Test: 4+2
					TokenList({ make<Integer>(4), make<Addition>(), make<Integer>(2) }),
					TokenList({ make<Integer>(4), make<Integer>(2), make<Addition>() })
					));
			}

			BOOST_AUTO_TEST_CASE(parser_order_of_operation_a_m) {
				BOOST_CHECK(parse_test(
					// Test: 4+2*3
					TokenList({ make<Integer>(4), make<Addition>(), make<Integer>(2), make<Multiplication>(), make<Integer>(3) }),
					TokenList({ make<Integer>(4), make<Integer>(2), make<Integer>(3), make<Multiplication>(), make<Addition>() })
					));
			}

			BOOST_AUTO_TEST_CASE(parser_order_of_operation_m_a) {
				BOOST_CHECK(parse_test(
					// Test: 4*2+3
					TokenList({ make<Integer>(4), make<Multiplication>(), make<Integer>(2), make<Addition>(), make<Integer>(3) }),
					TokenList({ make<Integer>(4), make<Integer>(2), make<Multiplication>(), make<Integer>(3), make<Addition>() })
					));
			}

			#if TEST_RIGHT_ASSOCIATIVE_OPERATOR
				BOOST_AUTO_TEST_CASE(parser_order_of_operation_right_assoc) {
					BOOST_CHECK(parse_test(
						// Test: 2#3#4
						TokenList({ make<Integer>(2), make<Power>(), make<Integer>(3), make<Power>(), make<Integer>(4) }),
						TokenList({ make<Integer>(2), make<Integer>(3), make<Integer>(4), make<Power>(), make<Power>() })
						));
				}
		#endif // TEST_RIGHT_ASSOCIATIVE_OPERATOR
	#endif // TEST_BINARY_OPERATOR


		#if TEST_PARENTHESIS

			BOOST_AUTO_TEST_CASE(parser_single_parenthesis) {
				BOOST_CHECK(parse_test(
					// Test: (2)
					TokenList({ make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>() }),
					TokenList({ make<Integer>(2) })
					));
			}

			BOOST_AUTO_TEST_CASE(parser_double_parenthesis) {
				BOOST_CHECK(parse_test(
					// Test: ((2))
					TokenList({ make<LeftParenthesis>(), make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>(), make<RightParenthesis>() }),
					TokenList({ make<Integer>(2) })
					));
			}

			BOOST_AUTO_TEST_CASE(parser_multi_parenthesis) {
				BOOST_CHECK(parse_test(
					// Test: (3+4)*5
					TokenList({ make<LeftParenthesis>(), make<Integer>(3), make<Addition>(), make<Integer>(4), make<RightParenthesis>(), make<Multiplication>(), make<Integer>(5) }),
					TokenList({ make<Integer>(3), make<Integer>(4), make<Addition>(), make<Integer>(5), make<Multiplication>() })
					));
			}

		#endif // TEST_PARENTHESIS

		#if TEST_FUNCTION && TEST_PARENTHESIS
			#if TEST_SINGLE_ARG

				BOOST_AUTO_TEST_CASE(parser_function_1_arg_abs) {
					BOOST_CHECK(parse_test(
						// Test: abs(2)
						TokenList({ make<Abs>(), make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>() }),
						TokenList({ make<Integer>(2), make<Abs>() })
						));
				}

			#endif // TEST_SINGLE_ARG

			#if TEST_MULTI_ARG

				BOOST_AUTO_TEST_CASE(parser_function_2_arg_max) {
					BOOST_CHECK(parse_test(
						// Test: max(2,4)
						TokenList({ make<Max>(), make<LeftParenthesis>(), make<Integer>(2), make<ArgumentSeparator>(), make<Integer>(4), make<RightParenthesis>() }),
						TokenList({ make<Integer>(2), make<Integer>(4), make<Max>() })
						));
				}

				BOOST_AUTO_TEST_CASE(parser_function_2_arg_min) {
					BOOST_CHECK(parse_test(
						// Test: min(2,4)
						TokenList({ make<Min>(), make<LeftParenthesis>(), make<Integer>(2), make<ArgumentSeparator>(), make<Integer>(4), make<RightParenthesis>() }),
						TokenList({ make<Integer>(2), make<Integer>(4), make<Min>() })
						));
				}

			#endif // TEST_MULTI_ARG
		#endif // TEST_FUNCTION && TEST_PARENTHESIS
	#endif // TEST_INTEGER



	#if TEST_REAL
		#if TEST_FUNCTION && TEST_PARENTHESIS
			#if TEST_SINGLE_ARG

				BOOST_AUTO_TEST_CASE(parser_function_1_arg_sin) {
					BOOST_CHECK(parse_test(
						// Test: sin(2.0)
						TokenList({ make<Sin>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.0), make<Sin>() })
						));
				}

				BOOST_AUTO_TEST_CASE(parser_function_1_arg_cos) {
					BOOST_CHECK(parse_test(
						// Test: cos(2.0)
						TokenList({ make<Cos>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.0), make<Cos>() })
						));
				}

				BOOST_AUTO_TEST_CASE(parser_function_1_arg_tan) {
					BOOST_CHECK(parse_test(
						// Test: tan(2.0)
						TokenList({ make<Tan>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.0), make<Tan>() })
						));
				}

			#endif // TEST_SINGLE_ARG


		#if TEST_MULTI_ARG

				BOOST_AUTO_TEST_CASE(parser_function_2_arg_pow) {
					BOOST_CHECK(parse_test(
						// Test: pow(2.3,3.4)
						TokenList({ make<Pow>(), make<LeftParenthesis>(), make<Real>(2.3), make<ArgumentSeparator>(), make<Real>(3.4), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.3), make<Real>(3.4), make<Pow>() })
						));
				}

				BOOST_AUTO_TEST_CASE(parser_function_expression) {
					BOOST_CHECK(parse_test(
						// Test: atan2(2.1,4.2)-10.3
						TokenList({ make<Arctan2>(), make<LeftParenthesis>(), make<Real>(2.1), make<ArgumentSeparator>(), make<Real>(4.2), make<RightParenthesis>(), make<Subtraction>(), make<Real>(10.3) }),
						TokenList({ make<Real>(2.1), make<Real>(4.2), make<Arctan2>(), make<Real>(10.3), make<Subtraction>() })
						));
				}

				BOOST_AUTO_TEST_CASE(parser_function_argument_expression) {
					BOOST_CHECK(parse_test(
						// Test: atan2(2.1,4.2-10.3)
						TokenList({ make<Arctan2>(), make<LeftParenthesis>(), make<Real>(2.1), make<ArgumentSeparator>(), make<Real>(4.2), make<Subtraction>(), make<Real>(10.3), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.1), make<Real>(4.2), make<Real>(10.3), make<Subtraction>(), make<Arctan2>() })
						));
				}

			#endif // TEST_MULTI_ARG
		#endif // TEST_FUNCTION
	#endif // TEST_REAL


	#if TEST_VARIABLE
		#if TEST_BINARY_OPERATOR

			BOOST_AUTO_TEST_CASE(parser_variable) {
				BOOST_CHECK(parse_test(
					// Test: x=2
					TokenList({ make<Variable>(), make<Assignment>(), make<Integer>(2) }),
					TokenList({ make<Variable>(), make<Integer>(2), make<Assignment>() })
					));
			}

			BOOST_AUTO_TEST_CASE(parser_variable_variable) {
				BOOST_CHECK(parse_test(
					// Test: x=y
					TokenList({ make<Variable>(), make<Assignment>(), make<Variable>() }),
					TokenList({ make<Variable>(), make<Variable>(), make<Assignment>() })
					));
			}

		#endif // TEST_BINARY_OPERATOR
	#endif // TEST_VARIABLE
#endif // TEST_PARSER


/*=============================================================

Revision History
Version 2.0.0: 2015-11-05
Visual Studio 2015
TEST_xxxx macros

Version 1.0.0: 2014-10-31
Visual Studio 2013

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitXor, BitShiftLeft, BitShiftRight

Version 0.1.0: 2012-11-15
Added BinaryInteger, Binary <function>

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-01
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
