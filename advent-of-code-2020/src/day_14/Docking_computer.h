#ifndef DAY_14_DOCKING_COMPUTER_H
#define DAY_14_DOCKING_COMPUTER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>

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

	// Only used with operations that set the mask
	std::string next_mask;
};

class Docking_computer
{
public:
	Docking_computer(const std::vector<Docking_instruction>& instructions);

	// Runs instructions
	void run_v1();
	void run_v2();

	// Returns sum of all values in memory
	uint64_t sum_memory() const;

private:
	std::bitset<36> mask_value(std::bitset<36> value) const;
	void mask_address(const std::string& address, const std::bitset<36>& value, std::string mask);

	std::vector<Docking_instruction> m_instructions;
	std::string m_mask;

	std::unordered_map<uint64_t, std::bitset<36>> m_memory;
};

#endif // !DAY_14_DOCKING_COMPUTER_H
