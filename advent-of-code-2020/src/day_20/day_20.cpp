#include "day_20.h"

#include "Tile.h"
#include "Image.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

std::vector<Tile> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<Tile> tiles;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("Tile") != std::string::npos)
		{
			// Get number from tile
			std::istringstream line_stream(line);
			line_stream.ignore(5);
			int id = 0;
			line_stream >> id;

			// Get borders
			std::vector<std::string> lines;
			while (std::getline(file, line))
			{
				if (line.empty())
				{
					break;
				}

				lines.push_back(line);
			}

			// Create every possible rotation of this tile
			Tile tile(id, lines);
			tiles.push_back(tile);

			tile.rotate();
			tiles.push_back(tile);

			tile.rotate();
			tiles.push_back(tile);

			tile.rotate();
			tiles.push_back(tile);

			tile.rotate();
			tile.flip_hoizontal();
			tiles.push_back(tile);

			tile.rotate();
			tiles.push_back(tile);

			tile.rotate();
			tiles.push_back(tile);

			tile.rotate();
			tiles.push_back(tile);
		}
	}

	return tiles;
}

void remove_all_with_id(const int id, std::vector<Tile>& tiles)
{
	tiles.erase(std::remove_if(tiles.begin(), tiles.end(), [&id](const Tile& t) { return t.get_id() == id; }), tiles.end());
}

Tile get_next_tile_matching_border(std::string border, const int border_index, std::vector<Tile>& tiles)
{
	Tile next_tile(-1, { "" });
	int next_tile_id = 0;
	for (const Tile& t : tiles)
	{
		if (t.get_borders()[border_index] == border)
		{
			next_tile_id = t.get_id();
			next_tile = t;
			break;
		}
	}

	// Remove all instances of this tile
	remove_all_with_id(next_tile_id, tiles);

	return next_tile;
}

// Returns a vector of images in the correct order
std::vector<Tile> assemble_image(std::vector<Tile> tiles, const int image_tile_width)
{
	std::vector<Tile> image_tiles;

	// Hardcode top left corner
	image_tiles.push_back(tiles[273]);
	remove_all_with_id(1663, tiles);

	while (true)
	{
		// copy bottom border of previous tile for use in finding the next starting tile
		std::string bottom_border = image_tiles[image_tiles.size() - 1].get_borders()[2];

		// Find tiles for this row
		for (size_t i = 1; i < image_tile_width; ++i)
		{
			std::string right_border = image_tiles.back().get_borders()[1];
			image_tiles.push_back(get_next_tile_matching_border(right_border, 3, tiles));
		}

		// Break out of loop if there's no more tiles left
		if (tiles.empty())
		{
			break;
		}

		// Get next starting tile
		image_tiles.push_back(get_next_tile_matching_border(bottom_border, 0, tiles));
	}

	return image_tiles;
}

void day_20_part_1(const std::string& input_path)
{
	std::vector<Tile> tiles = parse_input(input_path + "day_20.txt");
	std::vector<Tile> image_tiles = assemble_image(tiles, 12);

	uint64_t product = 1;
	product *= image_tiles[0].get_id();
	product *= image_tiles[11].get_id();
	product *= image_tiles[132].get_id();
	product *= image_tiles[143].get_id();

	std::cout << "Day 20 part 1 | Product of corner IDs: " << product << '\n';
}

void day_20_part_2(const std::string& input_path)
{
	std::vector<Tile> tiles = parse_input(input_path + "day_20.txt");
	std::vector<Tile> image_tiles = assemble_image(tiles, 12);

	// trim edges off each image tile
	std::for_each(image_tiles.begin(), image_tiles.end(), [](Tile& t) { t.trim_edges(); });

	// Find sea monsters
	Image image(image_tiles, 12, 8);
	image.flip_hoizontal();
	uint64_t water_count = image.get_water_count() - image.get_sea_monster_count();

	std::cout << "Day 20 part 2 | Number of water tiles without sea monsters: " <<  water_count  << '\n';
}