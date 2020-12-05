#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

int find_bsp_value(const std::string& bsp_string, int min, int max)
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
		std::string bsp_row = line.substr(0, 7);
		std::string bsp_column = line.substr(7, 3);

		//std::cout << bsp_row << ' ' << bsp_column << '\n';

		// Use separated strings to find row and column of seat
		int row = find_bsp_value(bsp_row, row_min, row_max);
		int column = find_bsp_value(bsp_column, column_min, column_max);

		//std::cout << row << ' ' << column << '\n';

		// Calculate seat ID and add it to the vector
		int seat_id = (row * 8) + column;
		seat_ids.push_back(seat_id);

		//std::cout << "ID: " << seat_id << '\n' << "=============================================\n";
	}

	return seat_ids;
}

void day_5_part_1()
{
	std::vector<int> seat_ids = get_seat_ids("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_5.txt");

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

void day_5_part_2()
{
	std::vector<int> seat_ids = get_seat_ids("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_5.txt");

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