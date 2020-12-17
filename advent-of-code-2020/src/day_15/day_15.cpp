#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int find_nth_in_sequence(const std::vector<int>& starting_sequence, const int turns)
{
	// Construct map from starting sequence
	std::unordered_map<int, std::vector<int>> numbers;
	for (size_t i = 0; i < starting_sequence.size(); ++i)
	{
		numbers[starting_sequence[i]].push_back(static_cast<int>(i + 1));
	}

	int previous_number = starting_sequence.back();
	for (size_t i = numbers.size() + 1; i <= turns; ++i)
	{
		// Check if the previous number has only been seen once
		if (numbers[previous_number].size() == 1)
		{
			// Push back the current turn for the value 0 and set previous number to 0
			numbers[0].push_back(static_cast<int>(i));
			previous_number = 0;
		}
		else
		{
			// Get reference to turns for previous number and get the difference between the last 2 elements
			const std::vector<int>& turns = numbers[previous_number];
			int turn_difference = turns[turns.size() - 1] - turns[turns.size() - 2];

			// Push back the current turn for the turn difference and set previous number to the turn difference
			numbers[turn_difference].push_back(static_cast<int>(i));
			previous_number = turn_difference;
		}
	}

	return previous_number;
}

void day_15_part_1()
{
	std::vector<int> starting_sequence = { 17, 1, 3, 16, 19, 0 };
	std::cout << "Day 15 part 1 | 2020th value: " << find_nth_in_sequence(starting_sequence, 2020) << '\n';
}

void day_15_part_2()
{
	std::vector<int> starting_sequence = { 17, 1, 3, 16, 19, 0 };
	std::cout << "Day 15 part 2 | 30000000th value: " << find_nth_in_sequence(starting_sequence, 30000000) << '\n';
}