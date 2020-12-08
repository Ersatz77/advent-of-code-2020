#ifndef DAY_8_CONSOLE_H
#define DAY_8_CONSOLE_H

#include "Instruction.h"

#include <iostream>
#include <vector>

class Console
{
public:
	Console(const std::vector<Instruction>& instructions);

	// Runs instructions and either returns the value in the accumulator before the instructions or
	// returns the value in the accumulator after the program terminates
	int run();

	// returns true if the instructions cause an infinite loop
	bool has_looped() const { return m_has_looped; }

private:
	std::vector<Instruction> m_instructions;
	int m_accumulator;
	bool m_has_looped;
};

#endif // !DAY_8_CONSOLE_H