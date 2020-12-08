#ifndef DAY_8_CONSOLE_H
#define DAY_8_CONSOLE_H

#include <iostream>
#include <vector>

enum class Operation
{
	ACC = 0,
	JMP,
	NOP
};

class Instruction
{
public:
	Instruction(const Operation& operation, int value);

	Operation get_operation() const { return m_operation; }
	int get_value() const { return m_value; }
	int get_executions() const { return m_executions; }

	void set_operation(const Operation& operation) { m_operation = operation; }
	void set_value(int value) { m_value = value; }

	void increment_executions() { ++m_executions; }

private:
	Operation m_operation;
	int m_value;
	int m_executions;
};

// Operators
std::ostream& operator<<(std::ostream& os, const Instruction& ins);


class Console
{
public:
	Console(const std::vector<Instruction>& instructions);

	// Runs instructions and returns the value in the accumulator before the execution loops
	int run();

	// returns true if the instructions cause an infinite loop
	bool has_looped() const { return m_has_looped; }

private:
	std::vector<Instruction> m_instructions;
	int m_accumulator;
	bool m_running;
	bool m_has_looped;
};

#endif // !DAY_8_CONSOLE_H