#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

static std::vector<int> get_input(const std::string& path)
{
	// Create input file stream
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	// Read everything from file and store it in a vector
	std::vector<int> input;
	for (int i = 0; file >> i; )
	{
		input.push_back(i);
	}

	return input;
}

void day_1_part_1()
{
	// Get input from file
	std::vector<int> input = get_input("D:\\Repositories\\advent-of-code-2020\\input\\day_1.txt");

	// Brute force adding values until we find 2 that add up to 2020
	bool found_solution = false;
	for (int i = 0; i < input.size() && !found_solution; ++i)
	{
		for (int j = 0; j < input.size() && !found_solution; ++j)
		{
			if (i != j && input[i] + input[j] == 2020)
			{
				found_solution = true;
				std::cout << "Day 1 part 1 | " << input[i] * input[j] << '\n';
			}
		}
	}
}

void day_1_part_2()
{
	// Get input from file
	std::vector<int> input = get_input("D:\\Repositories\\advent-of-code-2020\\input\\day_1.txt");

	// Brute force adding values until we find 3 that add up to 2020
	bool found_solution = false;
	for (int i = 0; i < input.size() && !found_solution; ++i)
	{
		for (int j = 0; j < input.size() && !found_solution; ++j)
		{
			for (int k = 0; k < input.size() && !found_solution; ++k)
			{
				if (i != j && j != k && input[i] + input[j] + input[k] == 2020)
				{
					found_solution = true;
					std::cout << "Day 1 part 2 | " << input[i] * input[j] * input[k] << '\n';
				}
			}
		}
	}
}