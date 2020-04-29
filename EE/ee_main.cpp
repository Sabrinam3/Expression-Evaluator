/** @file: ee_main.cpp
	@author Sabrina Tessier
	@date Nov 20/2018
	@brief Expression Evaluator application.
	*/

#include "../ee_common/inc/expression_evaluator.hpp"

#include <iostream>
#include <string>
#include <boost/locale.hpp>
#include <boost/locale/format.hpp>
using namespace std;
int main() {
	cout << "Expression Evaluator, (c) 2018 Sabrina Tessier\n";
//Make an expression evaluator object
	ExpressionEvaluator ee;
	for (unsigned count = 0; ; ++count) {
		cout << "> ";
		string command;
		if (!getline(cin, command) || command.empty())
			break;
		try
		{
			Token::pointer_type result = ee.evaluate(command);
			cout << "[" << count << "] = " << result->to_string() << endl;
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
			continue;
		}	
		catch (...)
		{
			continue;
		}
	}//end for
	resultTypes.clear();
}//end main

