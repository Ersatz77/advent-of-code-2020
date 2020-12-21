#ifndef DAY_20_IMAGE_H
#define DAY_20_IMAGE_H

#include "Tile.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Image
{
public:
	Image(std::vector<Tile> image_tiles, const size_t image_tile_width, const size_t tile_width);

	// Gets number of sea monsters for the current orientation
	uint64_t get_sea_monster_count() const;

	// Returns the number of '#' characters
	uint64_t get_water_count() const;

	// Rotates tile 90 degrees to the right
	void rotate();

	// Flips tile horizontally
	void flip_hoizontal();

private:
	friend std::ostream& operator<<(std::ostream& os, const Image& image);

	std::vector<std::string> m_lines;

	static std::vector<std::string> m_sea_monster;
};

#endif // !DAY_20_IMAGE_H