#include "day_6.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <stdexcept>

void day_6_part_1(const std::string& input_path)
{
	std::string path = input_path + "day_6.txt";
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	int sum = 0;
	std::string line;
	std::unordered_set<char> answers;
	while (file)
	{
		std::getline(file, line);
		if (!line.empty())
		{
			for (const char c : line)
			{
				answers.insert(c);
			}
		}
		else
		{
			sum += answers.size();
			answers.clear();
		}
	}

	std::cout << "Day 6 part 1 | Sum of questions anyone answered: " << sum << '\n';
}

void day_6_part_2(const std::string& input_path)
{
	std::string path = input_path + "day_6.txt";
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	int sum = 0;
	std::string line;
	std::string group_answers;
	std::unordered_set<char> unique_answers;
	int group_size = 0;
	while (file)
	{
		std::getline(file, line);

		if (!line.empty())
		{
			for (const char c : line)
			{
				unique_answers.insert(c);
			}

			group_answers += line;
			++group_size;
		}
		else
		{
			// For each unique answer, compare it to the string containing all answers
			// If the number of answers equals the group size, increment the sum
			for (const char c : unique_answers)
			{
				if (std::count(group_answers.begin(), group_answers.end(), c) == group_size)
				{
					++sum;
				}
			}

			group_answers.clear();
			unique_answers.clear();
			group_size = 0;
		}
	}

	std::cout << "Day 6 part 2 | Sum of questions everyone answered: " << sum << '\n';
}