#include "Tile.h"

#include <string>
#include <vector>
#include <algorithm>

Tile::Tile(const int id, const std::vector<std::string>& lines) :
	m_id(id),
	m_lines(lines)
{
}

std::vector<std::string> Tile::get_borders() const
{
	std::vector<std::string> borders;
	
	std::string east;
	std::string west;
	for (const std::string& line : m_lines)
	{
		west += line.front();
		east += line.back();
	}

	borders.push_back(m_lines.front());
	borders.push_back(east);
	borders.push_back(m_lines.back());
	borders.push_back(west);

	return borders;
}

void Tile::rotate()
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

void Tile::flip_hoizontal()
{
	for (std::string& line : m_lines)
	{
		std::reverse(line.begin(), line.end());
	}
}

void Tile::trim_edges()
{
	std::vector<std::string> new_lines;
	for (size_t i = 1; i < 9; ++i)
	{
		new_lines.push_back(m_lines[i].substr(1, 8));
	}

	m_lines = new_lines;
}

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
	const std::vector<std::string> lines = tile.get_lines();
	for (size_t i = 0; i < lines.size(); ++i)
	{
		os << lines[i];
		if (i < lines.size() - 1)
		{
			os << '\n';
		}
	}

	return os;
}