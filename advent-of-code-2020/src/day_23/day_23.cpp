#include "day_23.h"

#include "Cup_game.h"

#include <iostream>
#include <string>
#include <list>

void day_23_part_1(const std::string& input_path)
{
	std::list<int> cups = { 1, 8, 6, 5, 2, 4, 9, 7, 3 };
	Cup_game cup_game(cups);

	// Play game for n moves
	cup_game.play(100);

	std::cout << "Day 23 part 1 | Final order: " << cup_game.to_string() << '\n';
}

void day_23_part_2(const std::string& input_path)
{
	std::list<int> cups = { 1, 8, 6, 5, 2, 4, 9, 7, 3 };
	for (int i = 10; i <= 1000000; ++i)
	{
		cups.push_back(i);
	}

	Cup_game cup_game(cups);

	// Play game for n moves
	cup_game.play(10000000);

	std::cout << "Day 23 part 2 | Product of the 2 cups after 1: " << cup_game.cups_after_one() << '\n';
}