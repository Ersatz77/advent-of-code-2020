#include "day_9.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>

std::vector<uint64_t> get_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<uint64_t> input;
	uint64_t number = 0;
	while (file >> number)
	{
		input.push_back(number);
	}

	return input;
}

bool valid_next_number(const std::vector<uint64_t>& prev, uint64_t target)
{
	for (size_t i = 0; i < prev.size(); ++i)
	{
		for (size_t j = i + 1; j < prev.size(); ++j)
		{
			if (prev[i] != prev[j] && prev[i] + prev[j] == target)
			{
				return true;
			}
		}
	}

	return false;
}

uint64_t find_invalid_number(const std::vector<uint64_t> code, size_t range_min, size_t range_max)
{
	uint64_t invalid_number = 0;
	while (range_max + 1 < code.size() - 1)
	{
		std::vector<uint64_t> prev_range(code.begin() + range_min, code.begin() + range_max + 1);
		if (!valid_next_number(prev_range, code[range_max + 1]))
		{
			invalid_number = code[range_max + 1];
			break;
		}

		++range_min;
		++range_max;
	}

	return invalid_number;
}

void day_9_part_1()
{
	std::vector<uint64_t> code = get_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_9.txt");

	uint64_t invalid_number = find_invalid_number(code, 0, 24);

	std::cout << "Day 9 part 1 | Invalid number: " << invalid_number << '\n';
}

void day_9_part_2()
{
	std::vector<uint64_t> code = get_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_9.txt");

	// Get invalid number and it's index
	uint64_t invalid_number = find_invalid_number(code, 0, 24);
	size_t invalid_index = std::distance(code.begin(), std::find(code.begin(), code.end(), invalid_number));

	// Find contiguous set that adds up to the invalid number
	size_t range_min = 0;
	size_t range_max = 1;
	std::vector<uint64_t> range;
	while (range_max < invalid_index)
	{
		// Find sum for current range
		uint64_t sum = 0;
		range = std::vector<uint64_t>(code.begin() + range_min, code.begin() + range_max + 1);
		std::for_each(range.begin(), range.end(), [&sum](const uint64_t i) { sum += i; });

		if (sum == invalid_number)
		{
			break;
		}
		else if (sum < invalid_number)
		{
			++range_max;
		}
		else if (sum > invalid_number)
		{
			++range_min;
		}
	}

	//std::for_each(range.begin(), range.end(), [](const uint64_t i) { std::cout << i << '\n'; });

	uint64_t min = std::numeric_limits<uint64_t>::max();
	uint64_t max = std::numeric_limits<uint64_t>::min();
	for (const uint64_t i : range)
	{
		min = std::min(i, min);
		max = std::max(i, max);
	}

	std::cout << "Day 9 part 2 | Encryption weakness: " << min + max << '\n';
}