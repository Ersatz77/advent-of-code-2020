#include "Instruction.h"

#include <iostream>
#include <string>

Instruction::Instruction(const Operation& operation, int value) :
	m_operation(operation),
	m_value(value)
{
}

std::ostream& operator<<(std::ostream& os, const Instruction& ins)
{
	std::string op;
	switch (ins.get_operation())
	{
		case Operation::ACC:
			op = "acc";
			break;

		case Operation::JMP:
			op = "jmp";
			break;

		case Operation::NOP:
			op = "nop";
			break;
	}

	return os << op << ' ' << ins.get_value();
}