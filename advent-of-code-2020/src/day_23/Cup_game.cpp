#include "Cup_game.h"

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <limits>

Cup_game::Cup_game(const std::list<int>& initial_cups) :
	m_cups(initial_cups),
	m_lowest_cup_value(std::numeric_limits<int>::max()),
	m_highest_cup_value(std::numeric_limits<int>::min())
{
	// Fill lookup table with iterators to every cup node
	m_iterator_table.reserve(m_cups.size());
	for (std::list<int>::const_iterator it = m_cups.begin(); it != m_cups.end(); ++it)
	{
		m_iterator_table[*it] = it;
	}

	// Get lowest and highest cup values
	for (const int i : m_cups)
	{
		m_lowest_cup_value = std::min(m_lowest_cup_value, i);
	}

	for (const int i : m_cups)
	{
		m_highest_cup_value = std::max(m_highest_cup_value, i);
	}
}

void Cup_game::play(const int num_rounds)
{
	for (int i = 0; i < num_rounds; ++i)
	{
		// Splice next 3 node after first node into a temporary list
		std::list<int> removed_cups;
		removed_cups.splice(removed_cups.begin(), m_cups, std::next(m_cups.begin(), 1), std::next(m_cups.begin(), 4));

		// Get current cup value
		int current_cup = m_cups.front();

		// Get iterator to destination cup
		int destination_cup = current_cup - 1 < m_lowest_cup_value ? m_highest_cup_value : current_cup - 1;
		while (std::count(removed_cups.begin(), removed_cups.end(), destination_cup) > 0)
		{
			--destination_cup;

			if (destination_cup < m_lowest_cup_value)
			{
				destination_cup = m_highest_cup_value;
			}
		}

		const std::list<int>::const_iterator destination = m_iterator_table.find(destination_cup)->second;

		// Splice cups into their new destinations
		m_cups.splice(std::next(destination, 1), removed_cups);
		m_cups.splice(m_cups.end(), m_cups, m_cups.begin());
	}
}

std::string Cup_game::to_string() const
{
	// Rotate cups clockwise until the first element is a one
	std::list<int> temp_cups = m_cups;
	while (temp_cups.front() != 1)
	{
		std::rotate(temp_cups.rbegin(), std::next(temp_cups.rbegin(), 1), temp_cups.rend());
	}

	// Create string
	std::string str;
	for (size_t i = 1; i < temp_cups.size(); ++i)
	{
		str += std::to_string(*(std::next(temp_cups.begin(), i)));
	}

	return str;
}

int64_t Cup_game::cups_after_one() const
{
	int64_t product = 1;
	const std::list<int>::const_iterator it = std::find(m_cups.begin(), m_cups.end(), 1);
	product *= *(std::next(it, 1));
	product *= *(std::next(it, 2));

	return product;
}

std::ostream& operator<<(std::ostream& os, const Cup_game& cup_game)
{
	os << "[ ";
	for (const int i : cup_game.m_cups)
	{
		os << i << ' ';
	}

	return os << ']';
}