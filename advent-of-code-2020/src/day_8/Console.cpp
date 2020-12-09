#include "Instruction.h"
#include "Console.h"

#include <iostream>
#include <vector>

Console::Console(const std::vector<Instruction>& instructions) :
	m_instructions(instructions),
	m_instruction_ptr(0),
	m_accumulator(0),
	m_status(Console_status::WAITING)
{
}

// Runs instructions and either returns the value in the accumulator before the instructions or
// returns the value in the accumulator after the program terminates
void Console::run()
{
	//std::cout << "Num instructions: " << m_instructions.size() << "\n\n";

	m_status = Console_status::RUNNING;

	while (true)
	{
		// Break if the instruction pointer is out of range
		if (m_instruction_ptr > m_instructions.size() - 1)
		{
			m_status = Console_status::TERMINATED;
			break;
		}

		// Get instruction at ptr
		const Instruction& ins = m_instructions[m_instruction_ptr];

		// Break if the current instruction has already been executed
		if (std::count(m_visited_addresses.begin(), m_visited_addresses.end(), m_instruction_ptr))
		{
			m_status = Console_status::LOOPED;
			break;
		}

		// Add address to visited addresses and preform operation
		m_visited_addresses.push_back(m_instruction_ptr);
		switch (ins.get_operation())
		{
			case Operation::ACC:
				m_accumulator += ins.get_value();
				++m_instruction_ptr;
				break;

			case Operation::JMP:
				m_instruction_ptr += ins.get_value();
				break;

			case Operation::NOP:
				++m_instruction_ptr;
				break;
		}

		//std::cout << ins << '\n' << "ACC: " << m_accumulator << '\n' << "Next ptr: " << instruction_ptr << "\n-------------------------------------\n";
	}
}