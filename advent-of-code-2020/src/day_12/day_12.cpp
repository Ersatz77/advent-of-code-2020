#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <stdexcept>

enum class Action
{
	N = 0,
	S,
	E,
	W,
	L,
	R,
	F,
};

struct Instruction
{
	Action action;
	int value;
};

std::vector<Instruction> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<Instruction> instructions;
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream line_stream(line);
		Action action = Action::E;
		char action_ch = ' ';
		int value = 0;

		line_stream >> action_ch >> value;

		switch (action_ch)
		{
			case 'N':
				action = Action::N;
				break;
			case 'S':
				action = Action::S;
				break;
			case 'E':
				action = Action::E;
				break;
			case 'W':
				action = Action::W;
				break;
			case 'L':
				action = Action::L;
				break;
			case 'R':
				action = Action::R;
				break;	
			case 'F':
				action = Action::F;
				break;
		}

		instructions.push_back(Instruction{ action, value });
	}

	return instructions;
}

void move_forwards(const int value, int& x, int& y, const int current_rotation)
{
	switch ((current_rotation % 360 + 360) % 360)
	{
		case 0:
			x += value;
			break;
		case 90:
			y -= value;
			break;
		case 180:
			x -= value;
			break;
		case 270:
			y += value;
			break;
	}
}

int manhattan_distance(const int x1, const int x2, const int y1, const int y2)
{
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void rotate_around(int& point_x, int& point_y, const int origin_x, const int origin_y, const double angle)
{
	constexpr double pi = 3.14159265358979323846;
	double angle_radians = angle * (pi / 180);

	int x1 = point_x - origin_x;
	int y1 = point_y - origin_y;

	double x2 = (x1 * std::cos(angle_radians)) - (y1 * std::sin(angle_radians));
	double y2 = (x1 * std::sin(angle_radians)) + (y1 * std::cos(angle_radians));

	point_x = static_cast<int>(std::round(x2 + origin_x));
	point_y = static_cast<int>(std::round(y2 + origin_y));
}

void day_12_part_1()
{
	std::vector<Instruction> instructions = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_12.txt");

	int x = 0;
	int y = 0;
	int rotation = 0;
	for (const Instruction& instruction : instructions)
	{
		switch (instruction.action)
		{
			case Action::N:
				y -= instruction.value;
				break;
			case Action::S:
				y += instruction.value;
				break;
			case Action::E:
				x += instruction.value;
				break;
			case Action::W:
				x -= instruction.value;
				break;
			case Action::L:
				rotation += instruction.value;
				break;
			case Action::R:
				rotation -= instruction.value;
				break;
			case Action::F:
				move_forwards(instruction.value, x, y, rotation);
				break;
		}
	}

	std::cout << "Day 12 part 1 | Manhattan distance: " << manhattan_distance(0, x, 0, y) << '\n';
}

void day_12_part_2()
{
	std::vector<Instruction> instructions = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_12.txt");

	int ship_x = 0;
	int ship_y = 0;
	int waypoint_x = 10;
	int waypoint_y = -1;
	for (const Instruction& instruction : instructions)
	{
		switch (instruction.action)
		{
			case Action::N:
				waypoint_y -= instruction.value;
				break;
			case Action::S:
				waypoint_y += instruction.value;
				break;
			case Action::E:
				waypoint_x += instruction.value;
				break;
			case Action::W:
				waypoint_x -= instruction.value;
				break;
			case Action::L:
				rotate_around(waypoint_x, waypoint_y, 0, 0, 360.0 - instruction.value);
				break;
			case Action::R:
				rotate_around(waypoint_x, waypoint_y, 0, 0, instruction.value);
				break;
			case Action::F:
				ship_x += waypoint_x * instruction.value;
				ship_y += waypoint_y * instruction.value;
				break;
		}
	}

	std::cout << "Day 12 part 2 | Manhattan distance: " << manhattan_distance(0, ship_x, 0, ship_y) << '\n';
}