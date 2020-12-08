#include "Instruction.h"
#include "Console.h"

#include <iostream>
#include <vector>

Console::Console(const std::vector<Instruction>& instructions) :
	m_instructions(instructions),
	m_accumulator(0),
	m_has_looped(false)
{
}

// Runs instructions and either returns the value in the accumulator before the instructions or
// returns the value in the accumulator after the program terminates
int Console::run()
{
	//std::cout << "Num instructions: " << m_instructions.size() << "\n\n";

	m_has_looped = false;
	int instruction_ptr = 0;

	while (true)
	{
		// Break if the instruction pointer is out of range
		if (instruction_ptr > m_instructions.size() - 1)
		{
			break;
		}

		Instruction& ins = m_instructions[instruction_ptr];

		// Break if the current instruction has already been executed
		if (ins.get_executions() > 0)
		{
			m_has_looped = true;
			break;
		}

		// Perform operation and increment execution
		switch (ins.get_operation())
		{
			case Operation::ACC:
				++ins;
				m_accumulator += ins.get_value();
				++instruction_ptr;
				break;

			case Operation::JMP:
				++ins;
				instruction_ptr += ins.get_value();
				break;

			case Operation::NOP:
				++ins;
				++instruction_ptr;
				break;
		}

		//std::cout << ins << '\n' << "ACC: " << m_accumulator << '\n' << "Next ptr: " << instruction_ptr << "\n-------------------------------------\n";
	}

	return m_accumulator;
}