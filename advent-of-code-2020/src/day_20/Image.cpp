#include "Image.h"

#include "Tile.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Image::Image(std::vector<Tile> image_tiles, const size_t image_tile_width, const size_t tile_width)
{
	// Convert tiles into a vector of strings
	for (size_t i = 0; i < image_tile_width * image_tile_width; i += image_tile_width)
	{
		for (size_t j = 0; j < tile_width; ++j)
		{
			std::string line;
			for (size_t k = i; k < i + image_tile_width; ++k)
			{
				line += image_tiles[k].get_lines()[j];
			}
			m_lines.push_back(line);
		}
	}
}

// Initialize sea monster static member
std::vector<std::string> Image::m_sea_monster = { "                  # ",
                                                  "#    ##    ##    ###", 
                                                  " #  #  #  #  #  #   " };

uint64_t Image::get_sea_monster_count() const
{
	// Get sea monster width and height
	static const size_t sea_monster_width = m_sea_monster.front().length();
	static const size_t sea_monster_height = m_sea_monster.size();

	static const size_t x_line_difference = (m_lines.front().length() - sea_monster_width) + 1;
	static const size_t y_line_difference = (m_lines.size() - sea_monster_height) + 1;

	int sea_monster_tiles = 0;
	for (size_t y = 0; y < y_line_difference; ++y)
	{
		for (size_t x = 0; x < x_line_difference; ++x)
		{
			// Get the next 3 lines
			std::string window_1 = m_lines[y].substr(x, sea_monster_width);
			std::string window_2 = m_lines[y + 1].substr(x, sea_monster_width);
			std::string window_3 = m_lines[y + 2].substr(x, sea_monster_width);

			// Check lines if they match any of the characters in the sea monster
			if (window_1[18] == '#' &&
				window_2[0] == '#' && window_2[5] == '#' && window_2[6] == '#' && window_2[11] == '#' && window_2[12] == '#' && window_2[17] == '#' && window_2[18] == '#' && window_2[19] == '#' &&
				window_3[1] == '#' && window_3[4] == '#' && window_3[7] == '#' && window_3[10] == '#' && window_3[13] == '#' && window_3[16] == '#'
			)
			{
				//std::cout << window_1 << '\n';
				//std::cout << window_2 << '\n';
				//std::cout << window_3 << "\n\n";
				sea_monster_tiles += 15;
			}
		}
	}

	return sea_monster_tiles;
}

uint64_t Image::get_water_count() const
{
	uint64_t count = 0;
	for (const std::string& line : m_lines)
	{
		count += std::count(line.begin(), line.end(), '#');
	}
	return count;
}

void Image::rotate()
{
	std::vector<std::string> new_lines;

	for (size_t i = 0; i < m_lines.front().length(); ++i)
	{
		std::string line;
		for (size_t j = 0; j < m_lines.front().length(); ++j)
		{
			line += m_lines[j][i];
		}

		std::reverse(line.begin(), line.end());

		new_lines.push_back(line);
	}

	m_lines = new_lines;
}

void Image::flip_hoizontal()
{
	for (std::string& line : m_lines)
	{
		std::reverse(line.begin(), line.end());
	}
}

std::ostream& operator<<(std::ostream& os, const Image& image)
{
	for (size_t i = 0; i < image.m_lines.size(); ++i)
	{
		os << image.m_lines[i];
		if (i < image.m_lines.size() - 1)
		{
			os << '\n';
		}
	}

	return os;
}