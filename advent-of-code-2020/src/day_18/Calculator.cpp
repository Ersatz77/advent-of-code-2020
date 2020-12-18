#include "Calculator.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

Calculator::Calculator() :
	m_token_buffer(Token{Calculator_operation::VALUE, -1}),
	m_buffer_full(false)
{
}

int64_t Calculator::calculate_v1(const std::string& expression_str)
{
	// Initialize string stream and result
	m_stream = std::istringstream(expression_str);
	return expression_v1();
}

int64_t Calculator::calculate_v2(const std::string& expression_str)
{
	// Initialize string stream and result
	m_stream = std::istringstream(expression_str);
	return expression_v2();
}

int64_t Calculator::expression_v1()
{
	int64_t left = primary_v1();
	Token t = get_token();

	while (true)
	{
		if (t.op == Calculator_operation::ADD)
		{
			left += primary_v1();
			t = get_token();
		}
		else if (t.op == Calculator_operation::MULTIPLY)
		{
			left *= primary_v1();
			t = get_token();
		}
		else if (t.op == Calculator_operation::END)
		{
			return left;
		}
		else
		{
			put_back_token(t);
			return left;
		}
	}
}

int64_t Calculator::primary_v1()
{
	Token t = get_token();
	if (t.op == Calculator_operation::OPENED_PARENTHESES)
	{
		int64_t result = expression_v1();

		t = get_token();
		if (t.op != Calculator_operation::CLOSED_PARENTHESES)
		{
			throw std::runtime_error("Expected ')'");
		}

		return result;
	}
	else if (t.op == Calculator_operation::VALUE)
	{
		return t.value;
	}
	else
	{
		put_back_token(t);
		throw std::runtime_error("Expected a primary");
	}
}

int64_t Calculator::expression_v2()
{
	int64_t left = term_v2();
	Token t = get_token();

	while (true)
	{
		if (t.op == Calculator_operation::MULTIPLY)
		{
			left *= term_v2();
			t = get_token();
		}
		else if (t.op == Calculator_operation::END)
		{
			return left;
		}
		else
		{
			put_back_token(t);
			return left;
		}
	}
}

int64_t Calculator::term_v2()
{
	int64_t left = primary_v2();
	Token t = get_token();

	while (true)
	{
		if (t.op == Calculator_operation::ADD)
		{
			left += primary_v2();
			t = get_token();
		}
		else
		{
			put_back_token(t);
			return left;
		}
	}
}

int64_t Calculator::primary_v2()
{
	Token t = get_token();
	if (t.op == Calculator_operation::OPENED_PARENTHESES)
	{
		int64_t result = expression_v2();

		t = get_token();
		if (t.op != Calculator_operation::CLOSED_PARENTHESES)
		{
			throw std::runtime_error("Expected ')'");
		}

		return result;
	}
	else if (t.op == Calculator_operation::VALUE)
	{
		return t.value;
	}
	else
	{
		put_back_token(t);
		throw std::runtime_error("Expected a primary");
	}
}

Token Calculator::get_token()
{
	// If buffer is full, return the value stored in it
	if (m_buffer_full)
	{
		m_buffer_full = false;
		return m_token_buffer;
	}

	// If buffer wasn't full, create a new token
	char c = ' ';
	m_stream >> c;

	// Return an end token if stream is at the end of the stream
	if (m_stream.eof())
	{
		return Token{ Calculator_operation::END, -1 };
	}

	// Create tokens for operations
	if (std::isdigit(c))
	{
		m_stream.unget();
		int64_t value = 0;
		m_stream >> value;
		return Token{ Calculator_operation::VALUE, value };
	}
	else if (c == '+')
	{
		return Token{ Calculator_operation::ADD, -1 };
	}
	else if (c == '*')
	{
		return Token{ Calculator_operation::MULTIPLY, -1 };
	}
	else if (c == '(')
	{
		return Token{ Calculator_operation::OPENED_PARENTHESES, -1 };
	}
	else if (c == ')')
	{
		return Token{ Calculator_operation::CLOSED_PARENTHESES, -1 };
	}
	else
	{
		std::cout << "Unknown operation";
		throw std::runtime_error("Unknown operation: " + c);
	}
}

void Calculator::put_back_token(const Token& token)
{
	if (!m_buffer_full)
	{
		m_token_buffer = token;
		m_buffer_full = true;
	}
	else
	{
		throw std::runtime_error("Unable to put token back into a full buffer");
	}
}