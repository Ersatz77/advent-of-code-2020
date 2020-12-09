#ifndef DAY_8_CONSOLE_H
#define DAY_8_CONSOLE_H

#include "Instruction.h"

#include <iostream>
#include <vector>

enum class Console_status
{
	TERMINATED = 0,
	RUNNING,
	WAITING,
	LOOPED
};

class Console
{
public:
	Console(const std::vector<Instruction>& instructions);

	// Runs instructions and sets status depending on execution
	void run();

	Console_status get_status() const { return m_status; }
	int get_accumulator() const { return m_accumulator; }

private:
	std::vector<Instruction> m_instructions;
	std::vector<int> m_visited_addresses;
	int m_instruction_ptr;
	int m_accumulator;

	Console_status m_status;
};

#endif // !DAY_8_CONSOLE_H