/** @file: ut_expression_evaluator.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.1.0
	@date 2017-11-23
	@note Compiles under Visual C++ 15.4.4

	@brief Expression Evaluator unit test.
	*/
#include "../ee_common/inc/expression_evaluator.hpp"
#include "../ee_common/inc/integer.hpp"
#include "../ee_common/inc/real.hpp"
#include "../ee_common/inc/variable.hpp"
#include "../ee_common/inc/boolean.hpp"


//#define _CRT_SECURE_NO_WARNINGS
#define BOOST_TEST_MODULE ExpressionEvaluatorUnitTest
#include <boost/test/auto_unit_test.hpp>
#include <string>

#include "../phase_list/ut_test_phase.hpp"

#if TEST_EXPRESSION_EVALUATOR

#if TEST_REAL
	Real::value_type round(Real::value_type x) {
		auto exp = pow(Real::value_type("10.0"), Real::value_type("990"));
		x *= exp;
		x += 0.5;
		x = floor(x);
		x /= exp;
		return x;
	}

	Real::value_type round(Token::pointer_type const& v) {
		return round(get_value<Real>(v));
	}
#endif

// error cases
BOOST_AUTO_TEST_CASE( unknown_token ) {
	try {
		ExpressionEvaluator::result_type result = ExpressionEvaluator().evaluate("@");
		BOOST_FAIL("Failed to throw exception");
	}
	catch( Tokenizer::XBadCharacter& e ) {
		std::string s( "Tokenizer::Bad character in expression." );
		std::string es( e.what() );
		BOOST_CHECK( s == es );
		BOOST_CHECK( e.get_expression() == "@" );
		BOOST_CHECK( e.get_location() == 0 );
	}
	catch( ... ) {
		BOOST_FAIL("Didn't catch Tokenizer::BadCharacter");
	}
}

BOOST_AUTO_TEST_CASE( empty_expression ) {
	try {
		ExpressionEvaluator::result_type result = ExpressionEvaluator().evaluate("");
		BOOST_FAIL("Failed to throw exception");
	}
	catch( std::exception& e ) {
		BOOST_CHECK( strcmp( e.what(), "Error: insufficient operands" ) == 0 );
	}
	catch( ... ) {
		BOOST_FAIL( "Caught wrong exception" );
	}
}


#if TEST_INTEGER
	BOOST_AUTO_TEST_CASE(EE_integer_small) {
		auto result = ExpressionEvaluator().evaluate("1000");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("1000"));
	}
	BOOST_AUTO_TEST_CASE(EE_integer_large) {
		auto result = ExpressionEvaluator().evaluate("123456789012345678901234567890123456789012345678901234567890");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("123456789012345678901234567890123456789012345678901234567890"));
	}

	#if TEST_UNARY_OPERATOR
		BOOST_AUTO_TEST_CASE(EE_identity_integer) {
			auto result = ExpressionEvaluator().evaluate("+42");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("42"));
		}
		BOOST_AUTO_TEST_CASE(EE_negation_integer) {
			auto result = ExpressionEvaluator().evaluate("-42");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("-42"));
		}
		BOOST_AUTO_TEST_CASE(EE_factorial) {
			auto result = ExpressionEvaluator().evaluate("5!");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("120"));
			result = ExpressionEvaluator().evaluate("100!");
			BOOST_CHECK(get_value<Integer>(result) ==
				Integer::value_type("93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000"));
		}
	#endif // TEST_UNARY_OPERATOR
	#if TEST_BINARY_OPERATOR
		BOOST_AUTO_TEST_CASE(EE_addition_integer) {
			auto result = ExpressionEvaluator().evaluate("2+3");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("5"));
		}
		BOOST_AUTO_TEST_CASE(EE_subtraction_integer) {
			auto result = ExpressionEvaluator().evaluate("2-3");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("-1"));
		}
		BOOST_AUTO_TEST_CASE(EE_multiplication_integer) {
			auto result = ExpressionEvaluator().evaluate("2*3");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("6"));
		}
		BOOST_AUTO_TEST_CASE(EE_division_integer) {
			auto result = ExpressionEvaluator().evaluate("21/3");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("7"));
			result = ExpressionEvaluator().evaluate("23/3");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("7"));
		}
		BOOST_AUTO_TEST_CASE(EE_modulo_integer) {
			auto result = ExpressionEvaluator().evaluate("21%3");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("0"));
			result = ExpressionEvaluator().evaluate("23%3");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("2"));
			#if TEST_NAMED_OPERATOR
				result = ExpressionEvaluator().evaluate("23 mod 3");
				BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("2"));
			#endif // TEST_NAMED_OPERATOR
		}
		BOOST_AUTO_TEST_CASE(EE_power_operator_integer) {
			auto result = ExpressionEvaluator().evaluate("5**2");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("25"));

			result = ExpressionEvaluator().evaluate("123**123");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("114374367934617190099880295228066276746218078451850229775887975052369504785666896446606568365201542169649974727730628842345343196581134895919942820874449837212099476648958359023796078549041949007807220625356526926729664064846685758382803707100766740220839267"));
		}
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_INTEGER

#if TEST_REAL
	BOOST_AUTO_TEST_CASE(EE_real_small) {
		auto result = ExpressionEvaluator().evaluate("1234.5678");
		BOOST_CHECK(get_value<Real>(result) == Real::value_type("1234.5678"));
	}
	BOOST_AUTO_TEST_CASE(EE_real_large) {
		auto result = ExpressionEvaluator().evaluate("123456789012345678901234567890123456789012345678901234567890.123456789012345678901234567890123456789012345678901234567890");
		BOOST_CHECK(get_value<Real>(result) == Real::value_type("123456789012345678901234567890123456789012345678901234567890.123456789012345678901234567890123456789012345678901234567890"));
	}
	BOOST_AUTO_TEST_CASE(EE_real_e) {
		auto result = ExpressionEvaluator().evaluate("e");
		BOOST_CHECK(get_value<Real>(result) == boost::math::constants::e<Real::value_type>());
		result = ExpressionEvaluator().evaluate("E");
		BOOST_CHECK(get_value<Real>(result) == boost::math::constants::e<Real::value_type>());
	}
	BOOST_AUTO_TEST_CASE(EE_real_pi) {
		auto result = ExpressionEvaluator().evaluate("pi");
		BOOST_CHECK(get_value<Real>(result) == boost::math::constants::pi<Real::value_type>());
		result = ExpressionEvaluator().evaluate("Pi");
		BOOST_CHECK(get_value<Real>(result) == boost::math::constants::pi<Real::value_type>());
		result = ExpressionEvaluator().evaluate("PI");
		BOOST_CHECK(get_value<Real>(result) == boost::math::constants::pi<Real::value_type>());
	}
	#if TEST_UNARY_OPERATOR
		BOOST_AUTO_TEST_CASE(EE_identity_real) {
			auto result = ExpressionEvaluator().evaluate("+42.3");
			BOOST_CHECK(get_value<Real>(result) == Real::value_type("42.3"));
		}
		BOOST_AUTO_TEST_CASE(EE_negation_real) {
			auto result = ExpressionEvaluator().evaluate("-42.3");
			BOOST_CHECK(get_value<Real>(result) == Real::value_type("-42.3"));
		}
	#endif // TEST_UNARY_OPERATOR
	#if TEST_BINARY_OPERATOR
		BOOST_AUTO_TEST_CASE(EE_addition_real) {
			auto result = ExpressionEvaluator().evaluate("2.2+3.3");
			BOOST_CHECK(get_value<Real>(result) == Real::value_type("5.5"));
		}
		BOOST_AUTO_TEST_CASE(EE_subtraction_real) {
			auto result = ExpressionEvaluator().evaluate("2.2-3.3");
			BOOST_CHECK(get_value<Real>(result) == Real::value_type("-1.1"));
		}
		BOOST_AUTO_TEST_CASE(EE_multiplication_real) {
			auto result = ExpressionEvaluator().evaluate("2.5*3.5");
			BOOST_CHECK(get_value<Real>(result) == Real::value_type("8.75"));
		}
		BOOST_AUTO_TEST_CASE(EE_division_real) {
			auto result = ExpressionEvaluator().evaluate("5.5/1.1");
			BOOST_CHECK(round(result) == round(Real::value_type("5.0")));
		}
		BOOST_AUTO_TEST_CASE(EE_power_operator_real) {
			auto result = ExpressionEvaluator().evaluate("4.0 ** 0.5");
			BOOST_CHECK(round(result) == round(Real::value_type("2.0")));
		}
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_REAL


#if TEST_MIXED && TEST_INTEGER && TEST_REAL
	#if TEST_BINARY_OPERATOR
		BOOST_AUTO_TEST_CASE(EE_mixed_addition) {
			auto result = ExpressionEvaluator().evaluate("1+3.3");
			BOOST_CHECK(round(result) == round(Real::value_type("4.3")));
		}

		BOOST_AUTO_TEST_CASE(EE_mixed_division) {
			auto result = ExpressionEvaluator().evaluate("5/2.0");
			BOOST_CHECK(round(result) == round(Real::value_type("2.5")));

			result = ExpressionEvaluator().evaluate("5.0/2");
			BOOST_CHECK(round(result) == round(Real::value_type("2.5")));
		}


	#endif // TEST_BINARY_OPERATOR
#endif // TEST_MIXED && TEST_INTEGER && TEST_REAL

#if TEST_BOOLEAN
	BOOST_AUTO_TEST_CASE(EE_bool_true) {
		auto result = ExpressionEvaluator().evaluate("true");
		BOOST_CHECK(get_value<Boolean>(result) == true);
		result = ExpressionEvaluator().evaluate("True");
		BOOST_CHECK(get_value<Boolean>(result) == true);
		result = ExpressionEvaluator().evaluate("TRUE");
		BOOST_CHECK(get_value<Boolean>(result) == true);
	}
	BOOST_AUTO_TEST_CASE(EE_bool_false) {
		auto result = ExpressionEvaluator().evaluate("false");
		BOOST_CHECK(get_value<Boolean>(result) == false);
		result = ExpressionEvaluator().evaluate("False");
		BOOST_CHECK(get_value<Boolean>(result) == false);
		result = ExpressionEvaluator().evaluate("FALSE");
		BOOST_CHECK(get_value<Boolean>(result) == false);
	}

	#if TEST_BINARY_OPERATOR
		#if TEST_NAMED_OPERATOR
			BOOST_AUTO_TEST_CASE(EE_and) {
				auto result = ExpressionEvaluator().evaluate("true and true");
				BOOST_CHECK(get_value<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("true and false");
				BOOST_CHECK(get_value<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false and true");
				BOOST_CHECK(get_value<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false and false");
				BOOST_CHECK(get_value<Boolean>(result) == false);
			}
			BOOST_AUTO_TEST_CASE(EE_or) {
				auto result = ExpressionEvaluator().evaluate("true or true");
				BOOST_CHECK(get_value<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("true or false");
				BOOST_CHECK(get_value<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false or true");
				BOOST_CHECK(get_value<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false or false");
				BOOST_CHECK(get_value<Boolean>(result) == false);
			}
			BOOST_AUTO_TEST_CASE(EE_xor) {
				auto result = ExpressionEvaluator().evaluate("true xor true");
				BOOST_CHECK(get_value<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("true xor false");
				BOOST_CHECK(get_value<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false xor true");
				BOOST_CHECK(get_value<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false xor false");
				BOOST_CHECK(get_value<Boolean>(result) == false);
			}
			BOOST_AUTO_TEST_CASE(EE_nand) {
				auto result = ExpressionEvaluator().evaluate("true nand true");
				BOOST_CHECK(get_value<Boolean>(result) == !true);
				result = ExpressionEvaluator().evaluate("true nand false");
				BOOST_CHECK(get_value<Boolean>(result) == !false);
				result = ExpressionEvaluator().evaluate("false nand true");
				BOOST_CHECK(get_value<Boolean>(result) == !false);
				result = ExpressionEvaluator().evaluate("false nand false");
				BOOST_CHECK(get_value<Boolean>(result) == !false);
			}
			BOOST_AUTO_TEST_CASE(EE_nor) {
				auto result = ExpressionEvaluator().evaluate("true nor true");
				BOOST_CHECK(get_value<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("true nor false");
				BOOST_CHECK(get_value<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false nor true");
				BOOST_CHECK(get_value<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false nor false");
				BOOST_CHECK(get_value<Boolean>(result) == true);
			}
			BOOST_AUTO_TEST_CASE(EE_xnor) {
				auto result = ExpressionEvaluator().evaluate("true xnor true");
				BOOST_CHECK(get_value<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("true xnor false");
				BOOST_CHECK(get_value<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false xnor true");
				BOOST_CHECK(get_value<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false xnor false");
				BOOST_CHECK(get_value<Boolean>(result) == true);
			}
		#endif // TEST_NAMED_OPERATOR
		#if TEST_RELATIONAL_OPERATOR
			BOOST_AUTO_TEST_CASE(EE_equal_bool) {
				auto result = ExpressionEvaluator().evaluate("true == true");
				BOOST_CHECK(get_value<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false == true");
				BOOST_CHECK(get_value<Boolean>(result) == false);
			}
			BOOST_AUTO_TEST_CASE(EE_not_equal_bool) {
				auto result = ExpressionEvaluator().evaluate("true != true");
				BOOST_CHECK(get_value<Boolean>(result) != true);
				result = ExpressionEvaluator().evaluate("false != true");
				BOOST_CHECK(get_value<Boolean>(result) != false);
			}

			#if TEST_INTEGER
				BOOST_AUTO_TEST_CASE(EE_equal_integer) {
					auto result = ExpressionEvaluator().evaluate("1 == 1");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1 == 2");
					BOOST_CHECK(get_value<Boolean>(result) == false);
				}
				BOOST_AUTO_TEST_CASE(EE_not_equal_integer) {
					auto result = ExpressionEvaluator().evaluate("1 != 1");
					BOOST_CHECK(get_value<Boolean>(result) != true);
					result = ExpressionEvaluator().evaluate("1 != 2");
					BOOST_CHECK(get_value<Boolean>(result) != false);
				}
				BOOST_AUTO_TEST_CASE(EE_less_integer) {
					auto result = ExpressionEvaluator().evaluate("1 < 1");
					BOOST_CHECK(get_value<Boolean>(result) == false);
					result = ExpressionEvaluator().evaluate("1 < 2");
					BOOST_CHECK(get_value<Boolean>(result) == true);
				}
				BOOST_AUTO_TEST_CASE(EE_less_equal_integer) {
					auto result = ExpressionEvaluator().evaluate("1 <= 1");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1 <= 2");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("3 <= 2");
					BOOST_CHECK(get_value<Boolean>(result) == false);
				}
				BOOST_AUTO_TEST_CASE(EE_greater_integer) {
					auto result = ExpressionEvaluator().evaluate("1 > 1");
					BOOST_CHECK(get_value<Boolean>(result) == false);
					result = ExpressionEvaluator().evaluate("2 > 1");
					BOOST_CHECK(get_value<Boolean>(result) == true);
				}
				BOOST_AUTO_TEST_CASE(EE_greater_equal_integer) {
					auto result = ExpressionEvaluator().evaluate("1 >= 1");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("2 >= 1");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("2 >= 3");
					BOOST_CHECK(get_value<Boolean>(result) == false);
				}

			#endif // TEST_INTEGER
			#if TEST_REAL
				BOOST_AUTO_TEST_CASE(EE_equal_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 == 1.0");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1.0 == 2.0");
					BOOST_CHECK(get_value<Boolean>(result) == false);
				}
				BOOST_AUTO_TEST_CASE(EE_not_equal_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 != 1.0");
					BOOST_CHECK(get_value<Boolean>(result) != true);
					result = ExpressionEvaluator().evaluate("1.0 != 2.0");
					BOOST_CHECK(get_value<Boolean>(result) != false);
				}
				BOOST_AUTO_TEST_CASE(EE_less_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 < 1.0");
					BOOST_CHECK(get_value<Boolean>(result) == false);
					result = ExpressionEvaluator().evaluate("1.0 < 2.0");
					BOOST_CHECK(get_value<Boolean>(result) == true);
				}
				BOOST_AUTO_TEST_CASE(EE_less_equal_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 <= 1.0");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1.0 <= 2.0");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("2.01 <= 2.0");
					BOOST_CHECK(get_value<Boolean>(result) == false);
				}
				BOOST_AUTO_TEST_CASE(EE_greater_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 > 1.0");
					BOOST_CHECK(get_value<Boolean>(result) == false);
					result = ExpressionEvaluator().evaluate("2.0 > 1.0");
					BOOST_CHECK(get_value<Boolean>(result) == true);
				}
				BOOST_AUTO_TEST_CASE(EE_greater_equal_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 >= 1.0");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("2.0 >= 1.0");
					BOOST_CHECK(get_value<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1.99 >= 2.0");
					BOOST_CHECK(get_value<Boolean>(result) == false);
				}

			#endif // TEST_REAL
		#endif // TEST_RELATIONAL_OPERATOR
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_BOOLEAN



#if TEST_FUNCTION
	#if TEST_SINGLE_ARG
		#if TEST_INTEGER
				BOOST_AUTO_TEST_CASE(EE_abs_integer) {
					auto result = ExpressionEvaluator().evaluate("abs(4)");
					BOOST_CHECK(get_value<Integer>(result) == 4);

					result = ExpressionEvaluator().evaluate("abs(-4)");
					BOOST_CHECK(get_value<Integer>(result) == 4);
				}
				BOOST_AUTO_TEST_CASE(EE_fib_pel_syl_integer) {
					auto result = ExpressionEvaluator().evaluate("fib(5)");
					BOOST_CHECK(get_value<Integer>(result) == 8);
					result = ExpressionEvaluator().evaluate("pel(3)");
					BOOST_CHECK(get_value<Integer>(result) == 5);
					result = ExpressionEvaluator().evaluate("syl(3)");
					BOOST_CHECK(get_value<Integer>(result) == 43);
				}
		#endif // TEST_INTEGER
		#if TEST_REAL
			BOOST_AUTO_TEST_CASE(EE_real_trig) {
				auto result = ExpressionEvaluator().evaluate("cos(0.0)");
				BOOST_CHECK(get_value<Real>(result) == Real::value_type("1.0"));

				result = ExpressionEvaluator().evaluate("arccos(1.0)");
				BOOST_CHECK(get_value<Real>(result) == Real::value_type("0.0"));

				result = ExpressionEvaluator().evaluate("sin(0.0)");
				BOOST_CHECK(get_value<Real>(result) == Real::value_type("0.0"));

				result = ExpressionEvaluator().evaluate("arcsin(1.0)");
				BOOST_CHECK(get_value<Real>(result) == boost::math::constants::half_pi<Real::value_type>());

				result = ExpressionEvaluator().evaluate("tan(0.0)");
				BOOST_CHECK(get_value<Real>(result) == Real::value_type("0.0"));

				result = ExpressionEvaluator().evaluate("arctan(0.0)");
				BOOST_CHECK(get_value<Real>(result) == Real::value_type("0.0"));
			}
			BOOST_AUTO_TEST_CASE(EE_abs) {
				auto result = ExpressionEvaluator().evaluate("abs(4.0)");
				BOOST_CHECK(round(result) == round(Real::value_type("4.0")));

				result = ExpressionEvaluator().evaluate("abs(-4.0)");
				BOOST_CHECK(round(result) == round(Real::value_type("4.0")));
			}
			BOOST_AUTO_TEST_CASE(EE_ceil) {
				auto result = ExpressionEvaluator().evaluate("ceil(4.3)");
				BOOST_CHECK(round(result) == round(Real::value_type("5.0")));
				result = ExpressionEvaluator().evaluate("ceil(-4.3)");
				BOOST_CHECK(round(result) == round(Real::value_type("-4.0")));
			}
			BOOST_AUTO_TEST_CASE(EE_exp) {
				auto result = ExpressionEvaluator().evaluate("exp(1.0)");
				BOOST_CHECK(get_value<Real>(result) == exp(Real::value_type("1.0")));
			}
			BOOST_AUTO_TEST_CASE(EE_floor) {
				auto result = ExpressionEvaluator().evaluate("floor(4.3)");
				BOOST_CHECK(round(result) == round(Real::value_type("4.0")));
				result = ExpressionEvaluator().evaluate("floor(-4.3)");
				BOOST_CHECK(round(result) == round(Real::value_type("-5.0")));
			}
			BOOST_AUTO_TEST_CASE(test_lb) {
				auto result = ExpressionEvaluator().evaluate("lb(8.0)");
				BOOST_CHECK(round(get_value<Real>(result)) == round(Real::value_type("3.0")));
			}
			BOOST_AUTO_TEST_CASE(test_ln) {
				auto result = ExpressionEvaluator().evaluate("ln(1.0)");
				BOOST_CHECK(round(get_value<Real>(result)) == boost::multiprecision::log(Real::value_type("1.0")));
			}
			BOOST_AUTO_TEST_CASE(test_sqrt) {
				auto result = ExpressionEvaluator().evaluate("sqrt(16.0)");
				BOOST_CHECK(round(get_value<Real>(result)) == round(Real::value_type("4.0")));
			}

		#endif // TEST_REAL
	#endif // TEST_SINGLE_ARG



#endif // TEST_FUNCTIONS

#if TEST_INTEGER && TEST_BINARY_OPERATOR && TEST_UNARY_OPERATOR
	BOOST_AUTO_TEST_CASE(EE_order_integer) {
		auto result = ExpressionEvaluator().evaluate("2*3+4");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("10"));
		result = ExpressionEvaluator().evaluate("21/3-5");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("2"));
		result = ExpressionEvaluator().evaluate("2+3*4");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("14"));
		result = ExpressionEvaluator().evaluate("2-32/4");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("-6"));

		#if TEST_RIGHT_ASSOCIATIVE_OPERATOR
			result = ExpressionEvaluator().evaluate("4**3**2");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("262144"));
		#endif // TEST_RIGHT_ASSOCIATIVE_OPERATOR

		result = ExpressionEvaluator().evaluate("4!!");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("620448401733239439360000"));
		result = ExpressionEvaluator().evaluate("2*4!-4");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("44"));

		result = ExpressionEvaluator().evaluate("20*3-32/4");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("52"));
		result = ExpressionEvaluator().evaluate("(21+5)/(7+6)");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("2"));
		result = ExpressionEvaluator().evaluate("(5+6*7)*(4+3)/(1+(5+6*7))");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("6"));
		result = ExpressionEvaluator().evaluate("(4 + 2 * 5) / (1 + 3 * 2)");
		BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("2"));
		#if TEST_NAMED_OPERATOR
			result = ExpressionEvaluator().evaluate("(15 mod 6)*3");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("9"));
		#endif // TEST_NAMED_OPERATOR
	}
#endif // TEST_INTEGER && TEST_BINARY_OPERATOR && TEST_UNARY_OPERATOR



#if TEST_REAL && TEST_BINARY_OPERATOR && TEST_UNARY_OPERATOR
	BOOST_AUTO_TEST_CASE(EE_order_real) {
		auto result = ExpressionEvaluator().evaluate("1.0/(1.0/32.0+1.0/48.0)");
		auto x = round(result);
		BOOST_CHECK(x == round(Real::value_type("19.2")));
		#if TEST_FUNCTION && TEST_SINGLE_ARG
			result = ExpressionEvaluator().evaluate("sin(1.0)**2+cos(1.0)**2");
			BOOST_CHECK(round(result) == round(Real::value_type("1.0")));
		#endif //TEST_FUNCTION && TEST_SINGLE_ARG
	}
#endif // TEST_REAL && TEST_BINARY_OPERATOR && TEST_UNARY_OPERATOR




#if TEST_BOOLEAN && TEST_UNARY_OPERATOR && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR
	BOOST_AUTO_TEST_CASE(EE_order_bool) {
	ExpressionEvaluator ee;
	auto result = ee.evaluate("true and not true");
	BOOST_CHECK(get_value<Boolean>(result) == false);

	result = ee.evaluate("true and false == not(not true or not false)");
	BOOST_CHECK(get_value<Boolean>(result) == true);
}
#endif // TEST_BOOLEAN && TEST_UNARY_OPERATOR && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR


#if TEST_BOOLEAN && TEST_RELATIONAL_OPERATOR && TEST_INTEGER && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR
	BOOST_AUTO_TEST_CASE(EE_relational) {
		ExpressionEvaluator ee;
		auto result = ee.evaluate("4 < 5 and 5 == 5");
		BOOST_CHECK(get_value<Boolean>(result) == true);
	}
#endif // TEST_BOOLEAN && TEST_RELATIONAL_OPERATOR && TEST_INTEGER && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR


#if TEST_VARIABLE && TEST_INTEGER && TEST_BINARY_OPERATOR
	BOOST_AUTO_TEST_CASE(EE_variable) {
		ExpressionEvaluator ee;
		auto result = ee.evaluate("x=4");
		auto var = convert<Variable>(result);
		auto val = var->get_value();
		BOOST_CHECK(get_value<Integer>(val) == Integer::value_type("4"));

		#if TEST_BOOLEAN && TEST_NAMED_OPERATOR && TEST_RELATIONAL_OPERATOR
			result = ee.evaluate("a = true");
			result = ee.evaluate("b = false");
			result = ee.evaluate("a and b == not(not a or not b)");
			BOOST_CHECK(get_value<Boolean>(result) == true);
		#endif // TEST_BOOLEAN && TEST_NAMED_OPERATOR && TEST_RELATIONAL_OPERATOR
	}

	#if TEST_MIXED
		BOOST_AUTO_TEST_CASE(EE_variable_mixed) {
			ExpressionEvaluator ee;
			auto result = ee.evaluate("x=12");
			result = ee.evaluate("y=12.0");
			result = ee.evaluate("x * 3 / (4+x)");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("2"));

			result = ee.evaluate("y*3/(4+y)");
			BOOST_CHECK(get_value<Real>(result) == Real::value_type("2.25"));
		}
	#endif // TEST_MIXED

	#if TEST_RESULT
		BOOST_AUTO_TEST_CASE(express_result) {
			resultTypes.clear();
			ExpressionEvaluator ee;
			auto result = ee.evaluate("1+1");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("2"));
			result = ee.evaluate("2+2");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("4"));
			result = ee.evaluate("result(1)*result(2)");
			BOOST_CHECK(get_value<Integer>(result) == Integer::value_type("8"));
		}
	#endif // TEST_RESULT
#endif // TEST_VARIABLE

#endif // TEST_EXPRESSION_EVALUATOR

/*=============================================================

Revision History

Version 1.1.0: 2017-11-23
Added Python-style power operator '**'.

Version 1.0.1: 2014-11-21
Improved round() - reduced float point conversion errors.

Version 1.0.0: 2014-11-03
Visual C++ 2013
Removed bit operations.
Added boost::multiprecision

Version 0.2.0: 2012-11-16
Added tests for Bit operators

Version 0.1.0: 2012-11-15
Added XNumericOverflow.
Added tests for BinaryInteger, Binary <function>

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
