#ifndef GUARD_tokenizer_hpp20091125_
#define GUARD_tokenizer_hpp20091125_

/** @file: tokenizer.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.1.0
	@date 2012-11-15
	@note Compiles under Visual C++ v110
	@implemented by Sabrina Tessier on 2018-11-10

	@brief Tokenizer class declaration for Expression Evaulator.
	*/

#include "token.hpp"
#include <map>
#include <string>
#include <boost/noncopyable.hpp>


class Tokenizer : boost::noncopyable {
// types
public:
	typedef std::string string_type;

	class XTokenizer : public std::exception {
		string_type	expression_;
		size_t location_;
	public:
		XTokenizer(string_type const& expression, size_t location, char const* msg)
			: std::exception(msg)
			, expression_( expression )
			, location_( location )
		{ }

		/**	Gets the expression string containing the bad character. */
		string_type	get_expression() const { return expression_; }

		/** Gets the location of the bad character in the expression string. */
		size_t get_location() const { return location_; }
	};

	/** Bad character exception class. */
	class XBadCharacter : public XTokenizer {
	public:
		XBadCharacter(string_type const& expression, size_t location)
			: XTokenizer(expression, location, "Tokenizer::Bad character in expression.") { }
	};

	/**	Numeric overflow exception class. */
	class XNumericOverflow : public XTokenizer {
	public:
		XNumericOverflow(string_type const& expression, size_t location)
			: XTokenizer(expression, location, "Tokenizer::Too many digits in number.") { }
	};

private:
	using dictionary_type = std::map<string_type, Token::pointer_type>;

// Data
private:
	dictionary_type keywords_;
	dictionary_type variables_;

// Methods
public:
	Tokenizer();
	TokenList tokenize(string_type const& expression);

private:
	Token::pointer_type _get_identifier(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression);
	Token::pointer_type _get_number(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression);
};

#endif // GUARD_tokenizer_hpp20091125_
