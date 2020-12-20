#include "day_17.h"

#include "Cube_3d.h"
#include "Grid_3d.h"

#include "Cube_4d.h"
#include "Grid_4d.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>


template<typename T>
std::vector<T> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<T> active_cubes;

	std::string line;
	int y = 0;
	while (std::getline(file, line))
	{
		for (int x = 0; x < line.length(); ++x)
		{
			if (line[x] == '#')
			{
				active_cubes.push_back(T{ x, y });
			}
		}

		++y;
	}

	return active_cubes;
}

void day_17_part_1(const std::string& input_path)
{
	std::vector<Cube_3d> initial_active_cubes = parse_input<Cube_3d>(input_path + "day_17.txt");

	Grid_3d grid(initial_active_cubes);
	for (int i = 0; i < 6; ++i)
	{
		grid.step();
	}

	std::cout << "Day 17 part 1 | Active cubes: " << grid.num_active() << '\n';
}

void day_17_part_2(const std::string& input_path)
{
	std::vector<Cube_4d> initial_active_cubes = parse_input<Cube_4d>(input_path + "day_17.txt");

	Grid_4d grid(initial_active_cubes);
	for (int i = 0; i < 6; ++i)
	{
		grid.step();
	}

	std::cout << "Day 17 part 2 | Active cubes: " << grid.num_active() << '\n';
}