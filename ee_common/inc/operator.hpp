#if !defined(GUARD_operator_hpp20091126_)
#define GUARD_operator_hpp20091126_

/**
@file: operator.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-16
	@version 0.2.0
	@note Compiles under Visual C++ v110	
	@Implemented by Sabrina Tessier on 2018-11-10

	@brief Operator class declarations
	*/

#include "operation.hpp"
#include "operand.hpp"
#include "boolean.hpp"
#include "RPNEvaluator.hpp"
#include "variable.hpp"


/** Operator Precedence values. */
typedef enum { MIN = 0,
	ASSIGNMENT, LOGOR, LOGXOR, LOGAND, BITOR, BITXOR, BITAND, EQUALITY, RELATIONAL, BITSHIFT, ADDITIVE, MULTIPLICATIVE,  POWER, UNARY, POSTFIX,
	MAX } precedence_type;

inline Operand::pointer_type handleMixedOperands(std::stack<Operand::pointer_type> &valueStack)
{
	Operand::pointer_type firstOperand = valueStack.top();
	valueStack.pop();
	Operand::pointer_type secondOperand = valueStack.top();
	valueStack.push(firstOperand);
	/*Return the operand with higher precedence*/
	if (firstOperand->get_operand_precedence() >= secondOperand->get_operand_precedence())
		return firstOperand;
	return secondOperand;

}

//Can call get_precedence method on every class that puts DEF_PRECEDENCE..... replaces DEF_PRECEDENCE with this method
/** Defines a precedence category method.  Used inside a class declaration. */
#define DEF_PRECEDENCE(category)	public: precedence_type get_precedence() const override { return category; }


/** Operator token base class. */
class Operator : public Operation {
public:
	DEF_POINTER_TYPE(Operator)
	virtual precedence_type get_precedence() const = 0;
};

	/** Binary operator token base class. */
	class BinaryOperator : public Operator {
		public:
			virtual unsigned number_of_args() const override { return 2; }
	};
	/** Unary operator token base class. */
	class UnaryOperator : public Operator {
	public:
		virtual unsigned number_of_args() const override { return 1; }
	};
	/** Right-associative operator base class. */
	class RAssocOperator : public BinaryOperator {};

	/*Left-associative operator base class*/
	class LAssocOperator : public BinaryOperator {};

	/*Non Associative operator base class*/
	class NonAssociative : public UnaryOperator {}; 

	/*Postfix operator base class*/
	class PostfixOperator : public NonAssociative {
		DEF_PRECEDENCE(POSTFIX)
			Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override { return nullptr; }
			void raiseTooFewParametersException() override {}
	};

	/** Power token. */
	class Power : public RAssocOperator {
			DEF_PRECEDENCE(POWER)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Assignment Token*/
	class Assignment : public RAssocOperator {
		DEF_PRECEDENCE(ASSIGNMENT)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Addition Class*/ 
	class Addition : public LAssocOperator {
		DEF_PRECEDENCE(ADDITIVE)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*And Class*/
	class And : public LAssocOperator {
		DEF_PRECEDENCE(LOGAND)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Division Class*/
	class Division : public LAssocOperator {
		DEF_PRECEDENCE(MULTIPLICATIVE)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Equality class*/
	class Equality : public LAssocOperator {
		DEF_PRECEDENCE(EQUALITY)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Inequality class*/
	class Inequality : public LAssocOperator {
		DEF_PRECEDENCE(RELATIONAL)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Greater class*/
	class Greater : public LAssocOperator {
		DEF_PRECEDENCE(RELATIONAL)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*GreaterEqual class*/
	class GreaterEqual : public LAssocOperator {
		DEF_PRECEDENCE(RELATIONAL)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Less class*/
	class Less : public LAssocOperator {
		DEF_PRECEDENCE(RELATIONAL)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*LessEqual class*/
	class LessEqual : public LAssocOperator {
		DEF_PRECEDENCE(RELATIONAL)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Modulus class*/
	class Modulus : public LAssocOperator {
		DEF_PRECEDENCE(MULTIPLICATIVE)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Multiplication class*/
	class Multiplication : public LAssocOperator {
		DEF_PRECEDENCE(MULTIPLICATIVE)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Nand class*/
	class Nand : public LAssocOperator {
		DEF_PRECEDENCE(LOGAND)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Nor class*/
	class Nor : public LAssocOperator {
		DEF_PRECEDENCE(LOGOR)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Or class*/
	class Or : public LAssocOperator {
		DEF_PRECEDENCE(LOGOR)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override; 
		void raiseTooFewParametersException() override;
	};

	/*Subtraction class*/
	class Subtraction : public LAssocOperator {
		DEF_PRECEDENCE(ADDITIVE)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Xnor class*/
	class Xnor : public LAssocOperator {
		DEF_PRECEDENCE(LOGXOR)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Xor class*/
	class Xor : public LAssocOperator {
		DEF_PRECEDENCE(LOGXOR)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Negation class*/
	class Negation : public NonAssociative {
		DEF_PRECEDENCE(UNARY)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*identity class*/
	class Identity : public NonAssociative {
		DEF_PRECEDENCE(UNARY)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Not class*/
	class Not : public NonAssociative {
		DEF_PRECEDENCE(UNARY)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*Factorial class*/
	class Factorial : public PostfixOperator {
		DEF_PRECEDENCE(POSTFIX)
	public:
		Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) override;
		void raiseTooFewParametersException() override;
	};

	/*=============================================================

Revision History
Version 1.0.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.3.0: 2014-10-30
Removed bitwise operators.

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

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
#endif // GUARD_operator_hpp20091126_
