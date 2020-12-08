#include "Console.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

Instruction::Instruction(const Operation& operation, int value) :
	m_operation(operation),
	m_value(value),
	m_executions(0)
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

	return os << op << ' ' << ins.get_value() << ' ' << ins.get_executions();
}

Console::Console(const std::vector<Instruction>& instructions) :
	m_instructions(instructions),
	m_accumulator(0),
	m_running(false),
	m_has_looped(false)
{
}

// Runs instructions and returns the value in the accumulator before the execution loops 
int Console::run()
{
	//std::cout << "Num instructions: " << m_instructions.size() << "\n\n";

	int instruction_ptr = 0;
	m_running = true;
	while (m_running)
	{
		Instruction& ins = m_instructions[instruction_ptr];
		if (ins.get_executions() == 0)
		{
			switch (ins.get_operation())
			{
				case Operation::ACC:
					m_accumulator += ins.get_value();
					++instruction_ptr;
					break;

				case Operation::JMP:
					instruction_ptr += ins.get_value();
					break;

				case Operation::NOP:
					++instruction_ptr;
					break;

				default:
					throw std::runtime_error("Unknown operation");
					break;
			}

			// If we got this far, we can increment the execution count
			ins.increment_executions();

			// Stop loop if the instruction pointer would be out of range
			if (instruction_ptr > m_instructions.size() - 1)
			{
				m_running = false;
			}
		}
		else
		{
			m_has_looped = true;
			m_running = false;
		}

		//std::cout << ins << '\n' << "ACC: " << m_accumulator << '\n' << "Next ptr: " << instruction_ptr << "\n-------------------------------------\n";
	}

	return m_accumulator;
}