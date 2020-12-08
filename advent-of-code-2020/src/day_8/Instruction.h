#ifndef DAY_8_INSTRUCTION_H
#define DAY_8_INSTRUCTION_H

#include <iostream>

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
Instruction& operator++(Instruction& ins);

#endif // !DAY_8_INSTRUCTION_H