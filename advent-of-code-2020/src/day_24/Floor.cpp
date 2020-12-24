#include "Floor.h"

#include "Hex_tile.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

Floor::Floor(const std::vector<std::vector<Step_direction>>& all_directions)
{
	// Initialize black tiles using directions
	for (const std::vector<Step_direction>& directions : all_directions)
	{
		int q = 0;
		int r = 0;
		for (const Step_direction& dir : directions)
		{
			// Add deltas
			int is_odd = r & 1;
			q += m_deltas[is_odd][static_cast<size_t>(dir)][0];
			r += m_deltas[is_odd][static_cast<size_t>(dir)][1];
		}

		// Flip tile
		Hex_tile tile{ q, r };
		std::unordered_set<Hex_tile>::iterator it = m_black_tiles.find(tile);
		if (it != m_black_tiles.end())
		{
			// Erase tile if it already exists
			m_black_tiles.erase(it);
		}
		else
		{
			// Add it if it doesn't exist
			m_black_tiles.insert(tile);
		}
	}
}

void Floor::step()
{
	// Expand current black tiles by getting every tile adjacent to every black tile
	std::unordered_set<Hex_tile> potential_black_tiles;
	for (const Hex_tile& tile : m_black_tiles)
	{
		std::vector<Hex_tile> adjacent_tiles = get_adjacent(tile);
		potential_black_tiles.insert(adjacent_tiles.begin(), adjacent_tiles.end());
	}

	// Add to next black tiles if this tile will turn black
	std::unordered_set<Hex_tile> next_black_tiles;
	for (const Hex_tile& tile : potential_black_tiles)
	{
		if (will_turn_black(tile))
		{
			next_black_tiles.insert(tile);
		}
	}

	m_black_tiles = next_black_tiles;
}

std::vector<Hex_tile> Floor::get_adjacent(const Hex_tile& center) const
{
	std::vector<Hex_tile> adjacent;
	for (size_t i = 0; i < 6; ++i)
	{
		int q = center.q;
		int r = center.r;

		int is_odd = r & 1;
		q += m_deltas[is_odd][static_cast<size_t>(i)][0];
		r += m_deltas[is_odd][static_cast<size_t>(i)][1];

		adjacent.push_back(Hex_tile{ q, r });
	}

	return adjacent;
}

int Floor::num_adjacent_black_tiles(const Hex_tile& center) const
{
	int count = 0;
	for (const Hex_tile& tile : get_adjacent(center))
	{
		if (m_black_tiles.find(tile) != m_black_tiles.end())
		{
			++count;
		}
	}

	return count;
}

bool Floor::will_turn_black(const Hex_tile& tile) const
{
	int num_adjacent_black = num_adjacent_black_tiles(tile);
	if (std::count(m_black_tiles.begin(), m_black_tiles.end(), tile) > 0)
	{
		if (num_adjacent_black == 0 || num_adjacent_black > 2)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return (num_adjacent_black == 2);
	}
}