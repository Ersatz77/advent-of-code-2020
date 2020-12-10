#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>

std::vector<int> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<int> adapters = { 0 };
	int adapter = 0;
	while (file >> adapter)
	{
		adapters.push_back(adapter);
	}

	std::sort(adapters.begin(), adapters.end());
	adapters.push_back(adapters[adapters.size() - 1] + 3);

	return adapters;
}

void day_10_part_1()
{
	std::vector<int> adapters = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_10.txt");
	std::vector<int> diff(adapters.size());

	std::adjacent_difference(adapters.begin(), adapters.end(), diff.begin());
	
	size_t diff_1 = std::count(diff.begin(), diff.end(), 1);
	size_t diff_3 = std::count(diff.begin(), diff.end(), 3);

	std::cout << "Day 10 part 1 | Product of Jolt differences: " << diff_1 * diff_3 << '\n';
}

void day_10_part_2()
{
	std::vector<int> adapters = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_10.txt");

	std::vector<uint64_t> combinations(adapters.size());
	combinations[0] = 1;
	for (size_t i = 1; i < adapters.size(); ++i)
	{
		// We need to cast i from size_t to int so the comparisons actually become negative
		int idx = static_cast<int>(i);

		// Count how many previous adapters the current one can plug into
		int count = 0;
		if (idx - 1 >= 0 && adapters[i] - adapters[i - 1] <= 3)
		{
			++count;
		}

		if (idx - 2 >= 0 && adapters[i] - adapters[i - 2] <= 3)
		{
			++count;
		}

		if (idx - 3 >= 0 && adapters[i] - adapters[i - 3] <= 3)
		{
			++count;
		}
		
		// Add up the number of previous combinations and store them at the current index
		switch (count)
		{
			case 1:
				combinations[i] = combinations[i - 1];
				break;
			case 2:
				combinations[i] = combinations[i - 1] + combinations[i - 2];
				break;
			case 3:
				combinations[i] = combinations[i - 1] + combinations[i - 2] + combinations[i - 3];
				break;
		}
	}

	std::cout << "Day 10 part 2 | Number of adapter combinations: " << combinations.back() << '\n';
}