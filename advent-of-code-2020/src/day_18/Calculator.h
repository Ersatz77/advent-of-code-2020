#ifndef DAY_18_CALCULATOR_H
#define DAY_18_CALCULATOR_H

#include <iostream>
#include <sstream>
#include <string>

enum class Calculator_operation
{
	VALUE = 0,
	END,
	ADD,
	MULTIPLY,
	OPENED_PARENTHESES,
	CLOSED_PARENTHESES
};

struct Token
{
	Calculator_operation op;
	int64_t value;
};

class Calculator
{
public:
	Calculator();
	int64_t calculate_v1(const std::string& expression_str);
	int64_t calculate_v2(const std::string& expression_str);

private:
	int64_t expression_v1();
	int64_t primary_v1();

	int64_t expression_v2();
	int64_t term_v2();
	int64_t primary_v2();

	Token get_token();
	void put_back_token(const Token& token);

	Token m_token_buffer;
	bool m_buffer_full;

	std::istringstream m_stream;
};

#endif // !DAY_18_CALCULATOR_H
