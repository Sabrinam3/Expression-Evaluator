#if !defined(GUARD_function_hpp20091126_)
#define GUARD_function_hpp20091126_

/**@file: function.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visual C++ v120
	@implemented by Sabrina Tessier on 2018-11-10

	@brief function token declarations.
	*/

#include "operation.hpp"
#include "operator.hpp"
#include "integer.hpp"

/** brief Function token base class. */

class Function : public Operation { 
	Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override
	{
		Operand::pointer_type result = nullptr;
		return result;
	}
};
		/** One argument function token base class. */
		class OneArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 1; }	
		};

		/*Two argument function token base class*/
		class TwoArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 2; }
		};

		/** Absolute value function token. */
		class Abs : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Arccos value function token*/
		class Arccos : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Arcsin value function token*/
		class Arcsin : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Arctan function token*/
		class Arctan : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Ceil function token*/
		class Ceil : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Floor function token*/
		class Floor : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Cos function token*/
		class Cos : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Exp function token*/
		class Exp : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Lb function token*/
		class Lb : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Ln function token*/
		class Ln : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Log function token*/
		class Log : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Result function token*/
		class Result : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Sin function token*/
		class Sin : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Sqrt function token*/
		class Sqrt : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Tan function token*/
		class  Tan : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Fib function token*/
		class Fib : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Pel function token*/
		class Pel : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Syl function token*/
		class Syl : public OneArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Arctan2 function token*/
		class Arctan2 : public TwoArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Max function token*/
		class Max : public TwoArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Min function token*/
		class Min : public TwoArgFunction {
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

		/*Pow function token*/
		class Pow : public TwoArgFunction{
		public:
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
			void raiseTooFewParametersException() override;
		};

/*=============================================================

Revision History

Version 1.0.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.0.2: 2014-10-30
Removed binary function

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
#endif // GUARD_function_hpp20091126_
