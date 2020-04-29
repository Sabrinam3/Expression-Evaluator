#if !defined(GUARD_token_hpp20091125_)
#define GUARD_token_hpp20091125_

/** @file: token.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2015-11-03
	@version 0.3.0
	@note Compiles under Visual C++ v110
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Token class declaration for Expression Evaluator project.
	*/

#include <memory>
#include <boost/noncopyable.hpp>
#include <string>
#include <typeinfo>
#include <vector>
#include <iostream>



/** Defines the appropriate type of smart pointer used in this system. */
#define DEF_POINTER_TYPE(_TT) using pointer_type = std::shared_ptr<_TT>;

/** Token base class. */
class Token : boost::noncopyable {
public:
	DEF_POINTER_TYPE(Token)
	using string_type = std::string;
	virtual ~Token() = default;
	virtual string_type	to_string() const;
};

/** Make a new smart-pointer managed Token object. */
template<typename T>
inline Token::pointer_type make(){
	return Token::pointer_type(new T());
}

/** Make a new smart-pointer managed Token object with constructor parameter. */
template<typename T, typename U>
inline Token::pointer_type make(U obj) {
	return Token::pointer_type(new T(obj));
}

/** Compare two tokens for same value. */
inline bool operator ==(Token::pointer_type const& lhs, Token::pointer_type const& rhs)
{
	return lhs->to_string() == rhs->to_string();
}

/** Test for family membership. */
template <typename T, typename U>
inline bool is(U const& tkn)
{
	return dynamic_pointer_cast<T>(tkn) != nullptr;
}


/** Test for family membership. */
template <typename T, typename U>
inline bool is(U const * tknptr)
{
	return dynamic_cast<T const *>(tknptr) != nullptr;
}

/** Convert to subclass type. */
template<typename T, typename U>
inline std::shared_ptr<T> convert(U obj)
{
	return dynamic_pointer_cast<T>(obj);
}

/** Container of tokens. */
using TokenList = std::vector<Token::pointer_type>;

/** stream operators */
inline std::ostream& operator << (std::ostream& os, Token const& token) {
	return os << token.to_string();
}

inline std::ostream& operator << (std::ostream& os, Token::pointer_type const& token) {
	return os << token->to_string();
}

/*=============================================================

Revision History

Version 0.2.1: 2012-11-13
C++ 11 cleanup

Version 0.2.0: 2010-11-20
Changed parameter of is_convertable_from to const&

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
#endif // GUARD_token_hpp20091125_
