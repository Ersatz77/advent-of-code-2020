#include "day_14.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

enum class Docking_operation
{
	SET_MASK = 0,
	SET_VALUE
};

struct Docking_instruction
{
	Docking_operation op;

	uint64_t address;
	uint64_t value;

	std::string mask;
};

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
			std::reverse(mask.begin(), mask.end());
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

void mask_value(const uint64_t address, uint64_t value, const std::string& mask, std::unordered_map<uint64_t, uint64_t>& memory)
{
	for (size_t i = 0; i < mask.length(); ++i)
	{
		if (mask[i] == '1')
		{
			value |= (1ULL << i);
		}
		if (mask[i] == '0')
		{
			value &= ~(1ULL << i);
		}
	}

	memory[address] = value;
}

void mask_address(uint64_t address, const uint64_t value, std::string mask, std::unordered_map<uint64_t, uint64_t>& memory)
{
	// Check if the mask still has X's in it
	size_t x = mask.find('X');

	// If X wasn't found, then set this memory address and return
	if (x == std::string::npos)
	{
		memory[address] = value;
		return;
	}

	// If an X still exists, replace it so further recursions levels don't find it
	mask[x] = '_';

	// Apply floating bit values
	uint64_t address_1 = address | (1ULL << x);
	uint64_t address_2 = address & ~(1ULL << x);

	// Apply the rest of the mask rules
	for (size_t i = 0; i < mask.length(); ++i)
	{
		if (mask[i] == '1')
		{
			address_1 |= (1ULL << i);
			address_2 |= (1ULL << i);
		}
	}

	// Find the rest of the bit values
	mask_address(address_1, value, mask, memory);
	mask_address(address_2, value, mask, memory);
}

void day_14_part_1()
{
	std::vector<Docking_instruction> instructions = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_14.txt");

	// Run program
	std::unordered_map<uint64_t, uint64_t> memory;
	std::string mask;
	for (const Docking_instruction& instruction : instructions)
	{
		switch (instruction.op)
		{
			case Docking_operation::SET_MASK:
				mask = instruction.mask;
				break;
			case Docking_operation::SET_VALUE:
				mask_value(instruction.address, instruction.value, mask, memory);
				break;
		}
	}

	// Sum memory values
	uint64_t sum = 0;
	for (const auto& [address, value] : memory)
	{
		sum += value;
	}
	
	std::cout << "Day 14 part 1 | Memory sum: " << sum << '\n';
}

void day_14_part_2()
{
	std::vector<Docking_instruction> instructions = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_14.txt");

	// Run program
	std::unordered_map<uint64_t, uint64_t> memory;
	std::string mask;
	for (const Docking_instruction& instruction : instructions)
	{
		switch (instruction.op)
		{
			case Docking_operation::SET_MASK:
				mask = instruction.mask;
				break;
			case Docking_operation::SET_VALUE:
				mask_address(instruction.address, instruction.value, mask, memory);
				break;
		}
	}

	// Sum memory values
	uint64_t sum = 0;
	for (const auto& [address, value] : memory)
	{
		sum += value;
	}

	std::cout << "Day 14 part 2 | Memory sum: " << sum << '\n';
}