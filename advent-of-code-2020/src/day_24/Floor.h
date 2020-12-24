#ifndef DAY_24_FLOOR_H
#define DAY_24_FLOOR_H

#include "Hex_tile.h"

#include <string>
#include <vector>
#include <unordered_set>

enum class Step_direction
{
	EAST = 0,
	NORTHEAST,
	NORTHWEST,
	WEST,
	SOUTHWEST,
	SOUTHEAST
};

class Floor
{
public:
	Floor(const std::vector<std::vector<Step_direction>>& all_directions);

	// Changes bhack tiles based on some rules
	void step();

	// Returns number of black tiles on floor
	size_t get_num_black_tiles() const { return m_black_tiles.size(); };

private:
	// Returns a vector of every tile adjacent to the center
	std::vector<Hex_tile> get_adjacent(const Hex_tile& center) const;

	// Returns the number of black tiles around the center (center is checked against tiles in m_black_tiles)
	int num_adjacent_black_tiles(const Hex_tile& center) const;

	// Returns true if a tile should be black after we step
	bool will_turn_black(const Hex_tile& tile) const;

	std::unordered_set<Hex_tile> m_black_tiles;
	static constexpr int m_deltas[2][6][2] = { { {+1, +0}, {+0, -1}, {-1, -1}, {-1, +0}, {-1, +1}, {+0, +1} },
								               { {+1, +0}, {+1, -1}, {+0, -1}, {-1, +0}, {+0, +1}, {+1, +1} } };
};
#endif // !DAY_24_FLOOR_H