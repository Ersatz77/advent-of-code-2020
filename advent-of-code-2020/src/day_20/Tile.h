#ifndef DAY_20_TILE_H
#define DAY_20_TILE_H

#include <iostream>
#include <string>
#include <vector>

class Tile
{
public:
	Tile(const int id, const std::vector<std::string>& lines);

	int get_id() const { return m_id; }
	std::vector<std::string> get_lines() const { return m_lines; }
	std::vector<std::string> get_borders() const;

	// Rotates tile 90 degrees to the right
	void rotate();

	// Flips tile horizontally
	void flip_hoizontal();

	// Trims edges off tile
	void trim_edges();

private:
	int m_id;
	std::vector<std::string> m_lines;
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);

#endif // !DAY_20_TILE_H