#include "Docking_computer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <stdexcept>

std::vector<Docking_instruction> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<Docking_instruction> instructions;

	std::string operation;
	std::string mask;
	uint64_t address = 0;
	uint64_t value = 0;
	while (file)
	{
		operation.clear();
		for (int i = 0; i < 4; ++i)
		{
			char c = ' ';
			file >> c;
			operation += c;
		}

		if (operation == "mask")
		{
			file.ignore(3);
			file >> mask;
			instructions.push_back(Docking_instruction{ Docking_operation::SET_MASK, 0, 0, mask });
		}
		else if (operation == "mem[")
		{
			file >> address;
			file.ignore(4);
			file >> value;
			instructions.push_back(Docking_instruction{ Docking_operation::SET_VALUE, address, value, "" });
		}
	}

	return instructions;
}

void day_14_part_1()
{
	std::vector<Docking_instruction> instructions = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_14.txt");
	Docking_computer computer(instructions);

	computer.run_v1();


	std::cout << "Day 14 part 1 | Memory sum: " << computer.sum_memory() << '\n';
}

void day_14_part_2()
{
	std::vector<Docking_instruction> instructions = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_14.txt");
	Docking_computer computer(instructions);

	computer.run_v2();

	std::cout << "Day 14 part 2 | Memory sum: " << computer.sum_memory() << '\n';
}