#include "day_24.h"

#include "Floor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

std::vector<std::vector<Step_direction>> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<std::vector<Step_direction>> directions;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream line_stream(line);
		std::vector<Step_direction> temp_directions;
		while (line_stream)
		{
			char first_ch = ' ';
			char second_ch = ' ';
			line_stream >> first_ch;

			if (first_ch == 'e')
			{
				temp_directions.push_back(Step_direction::EAST);
			}
			else if (first_ch == 'w')
			{
				temp_directions.push_back(Step_direction::WEST);
			}
			else if (first_ch == 'n')
			{
				line_stream >> second_ch;
				switch (second_ch)
				{
					case 'e':
						temp_directions.push_back(Step_direction::NORTHEAST);
						break;
					case 'w':
						temp_directions.push_back(Step_direction::NORTHWEST);
						break;
				}
			}
			else if (first_ch == 's')
			{
				line_stream >> second_ch;
				switch (second_ch)
				{
					case 'e':
						temp_directions.push_back(Step_direction::SOUTHEAST);
						break;
					case 'w':
						temp_directions.push_back(Step_direction::SOUTHWEST);
						break;
				}
			}
		}

		directions.push_back(temp_directions);
	}

	return directions;
}

void day_24_part_1(const std::string& input_path)
{
	std::vector<std::vector<Step_direction>> all_directions = parse_input(input_path + "day_24.txt");
	Floor floor(all_directions);

	std::cout << "Day 24 part 1 | Number of black tiles: " << floor.get_num_black_tiles() << '\n';
}

void day_24_part_2(const std::string& input_path)
{
	std::vector<std::vector<Step_direction>> all_directions = parse_input(input_path + "day_24.txt");
	Floor floor(all_directions);

	constexpr int num_days = 100;
	for (int i = 0; i < num_days; ++i)
	{
		floor.step();
	}

	std::cout << "Day 24 part 2 | Number of black tiles: " << floor.get_num_black_tiles() << '\n';
}