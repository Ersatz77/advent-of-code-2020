#include "day_5.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

int binary_search(const std::string& bsp_string, int min, int max)
{
	for (const char c : bsp_string)
	{
		switch (c)
		{
			case 'B':
			case 'R':
				min = std::ceil((min + max) / 2.0f);
				break;

			case 'F':
			case 'L':
				max = std::floor((min + max) / 2.0f);
				break;
		}

		//std::cout << c << ' ' << min << ' ' << max << '\n';
	}

	return min >= 0 ? min : -1;
}

std::vector<int> get_seat_ids(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	// Parse each BSP group to find seat row and column
	constexpr int row_min = 0;
	constexpr int row_max = 127;
	constexpr int column_min = 0;
	constexpr int column_max = 7;

	std::vector<int> seat_ids;
	std::string line;
	while (std::getline(file, line))
	{
		// Read line and separate it into it's parts for rows and columns
		std::string input_row = line.substr(0, 7);
		std::string input_column = line.substr(7, 3);

		//std::cout << bsp_row << ' ' << bsp_column << '\n';

		// Use separated strings to find row and column of seat
		int row = binary_search(input_row, row_min, row_max);
		int column = binary_search(input_column, column_min, column_max);

		//std::cout << row << ' ' << column << '\n';

		// Calculate seat ID and add it to the vector
		int seat_id = (row * 8) + column;
		seat_ids.push_back(seat_id);

		//std::cout << "ID: " << seat_id << '\n' << "=============================================\n";
	}

	return seat_ids;
}

void day_5_part_1(const std::string& input_path)
{
	std::vector<int> seat_ids = get_seat_ids(input_path + "day_5.txt");

	int highest_seat_id = std::numeric_limits<int>::min();
	for (const int id : seat_ids)
	{
		if (id > highest_seat_id)
		{
			highest_seat_id = id;
		}
	}

	std::cout << "Day 5 part 1 | Highest seat ID: " << highest_seat_id << '\n';
}

void day_5_part_2(const std::string& input_path)
{
	std::vector<int> seat_ids = get_seat_ids(input_path + "day_5.txt");

	std::sort(seat_ids.begin(), seat_ids.end());

	int seat = -1;
	for (size_t i = 1; i < seat_ids.size() - 1; ++i)
	{
		int prev = seat_ids[i - 1];
		int next = seat_ids[i + 1];

		if (next - prev != 2)
		{
			// We should land on the seat right before ours, so we need to add one to the value at the current index
			seat = seat_ids[i] + 1;
			break;
		}
	}

	std::cout << "Day 5 part 2 | ID for our seat: " << seat << '\n';
}

void day_5_v2(const std::string& input_path)
{
	std::string path = input_path + "day_5.txt";
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<unsigned int> ids;
	unsigned int highest_id = std::numeric_limits<unsigned int>::min();

	std::string line;
	while (std::getline(file, line))
	{
		unsigned int id = 0;
		for (size_t i = 0; i < line.size(); ++i)
		{
			switch (line[i])
			{
				case 'F':
				case 'L':
					id = (id << 1) | 0;
					break;

				case 'B':
				case 'R':
					id = (id << 1) | 1;
					break;
			}
		}

		ids.push_back(id);
		if (id > highest_id)
		{
			highest_id = id;
		}
	}

	std::sort(ids.begin(), ids.end());
	int seat_id = -1;
	for (size_t i = 0; i < ids.size() - 1; ++i)
	{
		if (ids[i + 1] - ids[i] != 1)
		{
			seat_id = ids[i] + 1;
			break;
		}
	}

	std::cout << "Day 5 part 1 (v2) | Highest seat ID: " << highest_id << '\n'
			  << "Day 5 part 2 (v2) | ID for our seat: " << seat_id << '\n';
}