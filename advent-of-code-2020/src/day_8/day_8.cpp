#include "day_8.h"

#include "Instruction.h"
#include "Console.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

std::vector<Instruction> create_instructions(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<Instruction> instructions;

	std::string line;
	std::string operation_str;
	Operation op = Operation::NOP;
	int value = 0;

	while (std::getline(file, line))
	{
		std::istringstream line_stream(line);
		line_stream >> operation_str >> value;
		if (operation_str == "acc")
		{
			op = Operation::ACC;
		}
		else if (operation_str == "jmp")
		{
			op = Operation::JMP;
		}
		else if (operation_str == "nop")
		{
			op = Operation::NOP;
		}

		// Add instruction to vector
		instructions.push_back(Instruction(op, value));
	}

	return instructions;
}

void day_8_part_1(const std::string& input_path)
{
	std::vector<Instruction> instructions = create_instructions(input_path + "day_8.txt");

	Console console(instructions);
	console.run();

	std::cout << "Day 8 part 1 | Accumulator before program loops: " << console.get_accumulator() << '\n';
}

void day_8_part_2(const std::string& input_path)
{
	std::vector<Instruction> original_instructions = create_instructions(input_path + "day_8.txt");
	int accumulator = 0;

	// Change JMP or NOP instructions until the program terminates
	for (int corruption_ptr = 0; corruption_ptr < original_instructions.size(); ++corruption_ptr)
	{
		std::vector<Instruction> instructions = original_instructions;
		Instruction& ins = instructions[corruption_ptr];

		// Change corrupted instruction
		switch (ins.get_operation())
		{
			case Operation::JMP:
				ins.set_operation(Operation::NOP);
				break;

			case Operation::NOP:
				ins.set_operation(Operation::JMP);
				break;
		}

		Console console(instructions);
		console.run();
		accumulator = console.get_accumulator();

		//std::cout << "\n================================================\n";

		// Break if the console terminated
		if (console.get_status() == Console_status::TERMINATED)
		{
			break;
		}
	}

	std::cout << "Day 8 part 2 | Accumulator after program terminates: " << accumulator << '\n';
}