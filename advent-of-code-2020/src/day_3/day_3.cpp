#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

struct Coord
{
	int x;
	int y;
	bool has_tree;
};

// Parse file to create a vector of all coordinate points
std::vector<Coord> create_coords(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<Coord> coords;
	int coord_y = 0;
	for (std::string line; std::getline(file, line); )
	{
		for (int coord_x = 0; coord_x < line.length(); ++coord_x)
		{
			coords.push_back(Coord{ coord_x, coord_y, (line[coord_x] == '.') ? false : true });
		}

		++coord_y;
	}

	return coords;
}

// Finds a coord in a vector that matches the X and Y of the arguments and returns true if there's a tree there
bool has_tree_at_pos(const std::vector<Coord>& coords, int x, int y)
{
	for (const Coord& c : coords)
	{
		if (c.x == x && c.y == y)
		{
			return c.has_tree;
		}
	}

	return false;
}

// Calculates the number of trees in a given slope
int num_trees_for_slope(const std::vector<Coord>& coords, int step_x, int step_y)
{
	constexpr int max_x = 30;
	constexpr int max_y = 322;
	int x = 0;
	int y = 0;
	int num_trees = 0;

	// Follow slope and increment tree count if there's a tree at the current pos
	while (y <= max_y)
	{
		if (has_tree_at_pos(coords, x, y))
		{
			++num_trees;
		}

		//std::cout << x << ' ' << y << " | " << num_trees << '\n';

		x = (x + step_x) % (max_x + 1);
		y += step_y;
	}

	return num_trees;
}

void day_3_part_1()
{
	std::vector<Coord> coords = create_coords("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_3.txt");

	std::cout << "Day 3 part 1 | Number of trees in path: " << num_trees_for_slope(coords, 3, 1) << '\n';
}

void day_3_part_2()
{
	std::vector<Coord> coords = create_coords("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_3.txt");

	int slope_1 = num_trees_for_slope(coords, 1, 1);
	int slope_2 = num_trees_for_slope(coords, 3, 1);
	int slope_3 = num_trees_for_slope(coords, 5, 1);
	int slope_4 = num_trees_for_slope(coords, 7, 1);
	int slope_5 = num_trees_for_slope(coords, 1, 2);
	unsigned int tree_product = slope_1 * slope_2 * slope_3 * slope_4 * slope_5;

	//std::cout << slope_1 << ' ' << slope_2 << ' ' << slope_3 << ' ' << slope_4 << ' ' << slope_5 << ' ' << tree_product << '\n';

	std::cout << "Day 3 part 2 | Product of trees in 5 different slopes: " << tree_product << '\n';
}