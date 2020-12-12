#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

enum class Cell
{
	FLOOR = 0,
	EMPTY,
	OCCUPIED
};

std::vector<std::vector<Cell>> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<std::vector<Cell>> grid;
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<Cell> temp;
		for (const char c : line)
		{
			switch (c)
			{
				case '.':
					temp.push_back(Cell::FLOOR);
					break;
				case 'L':
					temp.push_back(Cell::EMPTY);
					break;
			}
		}

		grid.push_back(temp);
	}

	return grid;
}

int num_occupied_around_pos(const int x, const int y, const std::vector<std::vector<Cell>>& grid)
{
	static const std::vector<int> s_deltas = { -1, -1, 0, -1, 1, -1, -1, 0, 1, 0, -1, 1, 0, 1, 1, 1 };
	int count = 0;
	for (size_t i = 1; i < s_deltas.size(); i += 2)
	{
		int dx = x + s_deltas[i - 1];
		int dy = y + s_deltas[i];
		if (dx >= 0 && dx < grid.front().size() && dy >= 0 && dy < grid.size() && grid[dy][dx] == Cell::OCCUPIED)
		{
			++count;
		}
	}

	return count;
}

int num_occupied_around_pos_2(const int x, const int y, const std::vector<std::vector<Cell>>& grid)
{
	static const std::vector<int> s_deltas = { -1, -1, 0, -1, 1, -1, -1, 0, 1, 0, -1, 1, 0, 1, 1, 1 };
	int count = 0;
	for (size_t i = 1; i < s_deltas.size(); i += 2)
	{
		int dx = x + s_deltas[i - 1];
		int dy = y + s_deltas[i];
		while (dx >= 0 && dx < grid.front().size() && dy >= 0 && dy < grid.size())
		{
			if (grid[dy][dx] == Cell::EMPTY || grid[dy][dx] == Cell::OCCUPIED)
			{
				if (grid[dy][dx] == Cell::OCCUPIED)
				{
					++count;
				}

				break;
			}

			dx += s_deltas[i - 1];
			dy += s_deltas[i];
		}
	}

	return count;
}

void day_11_part_1()
{
	std::vector<std::vector<Cell>> grid = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_11.txt");
	
	const size_t max_x = grid.front().size();
	const size_t max_y = grid.size();

	int changed_seats = 1;
	while (changed_seats > 0)
	{
		changed_seats = 0;
		std::vector<std::vector<Cell>> temp_grid = grid;
		for (int y = 0; y < max_y; ++y)
		{
			for (int x = 0; x < max_x; ++x)
			{
				if (grid[y][x] == Cell::EMPTY && num_occupied_around_pos(x, y, grid) == 0)
				{
					temp_grid[y][x] = Cell::OCCUPIED;
					++changed_seats;
				}
				else if (grid[y][x] == Cell::OCCUPIED && num_occupied_around_pos(x, y, grid) >= 4)
				{
					temp_grid[y][x] = Cell::EMPTY;
					++changed_seats;
				}
			}
		}

		// Move temp grid into grid vector instead of making a bunch of copies right before we delete the temp_grid
		grid = std::move(temp_grid);
	}

	// Count number of occupied seats
	int64_t occupied_seats = 0;
	for (const std::vector<Cell>& v : grid)
	{
		occupied_seats += std::count_if(v.begin(), v.end(), [](Cell c) { return (c == Cell::OCCUPIED); });
	}

	std::cout << "Day 11 part 1 | Number of occupied seats: " << occupied_seats << '\n';
}

void day_11_part_2()
{
	std::vector<std::vector<Cell>> grid = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_11.txt");

	const size_t max_x = grid.front().size();
	const size_t max_y = grid.size();

	int changed_seats = 1;
	while (changed_seats > 0)
	{
		changed_seats = 0;
		std::vector<std::vector<Cell>> temp_grid = grid;
		for (int y = 0; y < max_y; ++y)
		{
			for (int x = 0; x < max_x; ++x)
			{
				if (grid[y][x] == Cell::EMPTY && num_occupied_around_pos_2(x, y, grid) == 0)
				{
					temp_grid[y][x] = Cell::OCCUPIED;
					++changed_seats;
				}
				else if (grid[y][x] == Cell::OCCUPIED && num_occupied_around_pos_2(x, y, grid) >= 5)
				{
					temp_grid[y][x] = Cell::EMPTY;
					++changed_seats;
				}
			}
		}

		// Move temp grid into grid vector instead of making a bunch of copies right before we delete the temp_grid
		grid = std::move(temp_grid);
	}

	// Count number of occupied seats
	int64_t occupied_seats = 0;
	for (const std::vector<Cell>& v : grid)
	{
		occupied_seats += std::count_if(v.begin(), v.end(), [](Cell c) { return (c == Cell::OCCUPIED); });
	}

	std::cout << "Day 11 part 2 | Number of occupied seats: " << occupied_seats << '\n';
}