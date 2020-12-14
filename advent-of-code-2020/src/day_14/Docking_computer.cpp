#include "Docking_computer.h"

#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <numeric>

Docking_computer::Docking_computer(const std::vector<Docking_instruction>& instructions) :
	m_instructions(instructions)
{
}

void Docking_computer::run_v1()
{
	for (const Docking_instruction& instruction : m_instructions)
	{
		// Perform operations
		switch (instruction.op)
		{
			case Docking_operation::SET_MASK:
				m_mask = instruction.next_mask;
				break;
			case Docking_operation::SET_VALUE:
				m_memory[instruction.address] = mask_value(std::bitset<36>(instruction.value));
				break;
		}
	}
}

void Docking_computer::run_v2()
{
	for (const Docking_instruction& instruction : m_instructions)
	{
		// Perform operations
		switch (instruction.op)
		{
			case Docking_operation::SET_MASK:
				m_mask = instruction.next_mask;
				break;
			case Docking_operation::SET_VALUE:
				mask_address(std::bitset<36>(instruction.address).to_string(), instruction.value, m_mask);
				break;
		}
	}
}

std::bitset<36> Docking_computer::mask_value(std::bitset<36> value) const
{
	std::string temp_mask = m_mask;
	std::reverse(temp_mask.begin(), temp_mask.end());
	for (size_t i = 0; i < temp_mask.size(); ++i)
	{
		switch (temp_mask[i])
		{
			case '1':
				value[i] = true;
				break;
			case '0':
				value[i] = false;
				break;
		}
	}

	return value;
}

void Docking_computer::mask_address(const std::string& address, const std::bitset<36>& value, std::string mask)
{
	// Check if mask still has an X in it
	size_t x = mask.find('X');

	// If there's no X, assign value to memory address
	if (x == std::string::npos)
	{
		m_memory[std::bitset<36>(address).to_ullong()] = value;
		return;
	}

	// Set the X we found to a different character so it's not found again
	mask[x] = '_';

	std::string address_str_1 = address;
	std::string address_str_2 = address;
	address_str_1[x] = '0';
	address_str_2[x] = '1';

	for (size_t i = 0; i < mask.size(); ++i)
	{
		if (mask[i] == '1')
		{
			address_str_1[i] = '1';
			address_str_2[i] = '1';
		}
	}

	mask_address(address_str_1, value, mask);
	mask_address(address_str_2, value, mask);
}

uint64_t Docking_computer::sum_memory() const
{
	uint64_t sum = 0;
	for (const auto& [address, value] : m_memory)
	{
		sum += value.to_ullong();
	}

	return sum;
}