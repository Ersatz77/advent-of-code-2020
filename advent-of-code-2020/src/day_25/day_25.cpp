#include "day_25.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

std::vector<int64_t> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<int64_t> keys;
	int64_t key = 0;
	while (file >> key)
	{
		keys.push_back(key);
	}

	return keys;
}

constexpr int64_t g_initial_subject_number = 7;
constexpr int64_t g_dividend = 20201227;

int64_t get_loop_size(const int64_t key)
{
	int64_t value = g_initial_subject_number;
	int64_t loop_size = 1;
	while (true)
	{
		value *= g_initial_subject_number;
		value %= g_dividend;
		++loop_size;

		if (value == key)
		{
			break;
		}
	}

	return loop_size;
}

int64_t transform_number(const uint64_t key, const int64_t loop_size)
{
	int64_t value = key;
	for (int64_t i = 1; i < loop_size; ++i)
	{
		value *= key;
		value %= g_dividend;
	}

	return value;
}

void day_25_part_1(const std::string& input_path)
{
	std::vector<int64_t> keys = parse_input(input_path + "day_25.txt");

	std::cout << "Day 25 part 1 | Encryption key: " << transform_number(keys[0], get_loop_size(keys[1])) << '\n';
}

void day_25_part_2(const std::string& input_path)
{
	std::cout << "Day 25 part 2 | You paid the deposit\n";
}