#if !defined(GUARD_operation_hpp20091210_)
#define GUARD_operation_hpp20091210_

/**@file: operation.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.1.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110
	@brief Operation class declaration. 
	@	implemented by Sabrina Tessier on 2019-11-10
	*/


#include "operand.hpp"
#include "integer.hpp"
#include "real.hpp"
#include <stack>


/** Operation token base class. */

class Operation : public Token {
public:
	DEF_POINTER_TYPE(Operation)

	virtual unsigned number_of_args() const = 0;
	virtual Operand::pointer_type perform(std::stack<Operand::pointer_type> &valueStack) = 0;

	/*@Brief- raises the too few parameters exception*/
	virtual void raiseTooFewParametersException() = 0;
};




/*=============================================================

Revision History
Version 1.0.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.1.1: 2012-11-13
C++ cleanup.

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

Version 0.0.0: 2009-12-10
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
#endif // GUARD_operation_hpp20091210_
