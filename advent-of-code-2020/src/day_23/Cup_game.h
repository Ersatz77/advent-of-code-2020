#ifndef DAY_23_CUP_GAME_H
#define DAY_23_CUP_GAME_H

#include <iostream>
#include <list>
#include <unordered_map>

class Cup_game
{
public:
	Cup_game(const std::list<int>& initial_cups);

	// Plays cup game for N rounds
	void play(const int num_rounds);

	// Rotates the cup list clockwise until 1 is at the beginning and creates 
	// a string of all cup values with no spaces between them
	std::string to_string() const;

	// Returns the product of the next 2 cups after 1
	int64_t cups_after_one() const;

private:
	friend std::ostream& operator<<(std::ostream& os, const Cup_game& cup_game);

	std::list<int> m_cups;
	std::unordered_map<int, std::list<int>::const_iterator> m_iterator_table;

	int m_lowest_cup_value;
	int m_highest_cup_value;
};

#endif // !DAY_23_CUP_GAME_H