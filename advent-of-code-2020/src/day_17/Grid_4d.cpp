#include "Cube_4d.h"
#include "Grid_4d.h"

#include <vector>
#include <unordered_set>

Grid_4d::Grid_4d(const std::vector<Cube_4d>& initial_cubes)
{
	for (const Cube_4d& c : initial_cubes)
	{
		m_active_cubes.insert(c);
	}
}

void Grid_4d::step()
{
	std::unordered_set<Cube_4d> next_active_cubes;
	for (const Cube_4d& cube : m_active_cubes)
	{
		// Check if this cube should be activated
		if (should_be_active(cube))
		{
			next_active_cubes.insert(cube);
		}

		// Check if neighbors should be activated
		for (const Cube_4d& neighbor : get_neighbors(cube))
		{
			if (should_be_active(neighbor))
			{
				next_active_cubes.insert(neighbor);
			}
		}
	}

	m_active_cubes = next_active_cubes;
}

bool Grid_4d::should_be_active(const Cube_4d& cube) const
{
	// Count active neighbors
	std::vector<Cube_4d> neighbors = get_neighbors(cube);
	int num_active_neighbors = 0;
	for (const Cube_4d neighbor : neighbors)
	{
		if (m_active_cubes.count(neighbor) == 1)
		{
			++num_active_neighbors;
		}
	}

	// Return based on rules
	if (m_active_cubes.count(cube) == 1)
	{
		return (num_active_neighbors == 2 || num_active_neighbors == 3);
	}
	else
	{
		return (num_active_neighbors == 3);
	}
}

std::vector<Cube_4d> Grid_4d::get_neighbors(const Cube_4d& center) const
{
	std::vector<Cube_4d> neighbors;
	for (int dw = -1; dw <= 1; ++dw)
	{
		for (int dz = -1; dz <= 1; ++dz)
		{
			for (int dy = -1; dy <= 1; ++dy)
			{
				for (int dx = -1; dx <= 1; ++dx)
				{
					// Only add neighbor if any of the deltas are not 0 (Doesn't include center)
					if (dx != 0 || dy != 0 || dz != 0 || dw != 0)
					{
						neighbors.push_back(Cube_4d{ center.x + dx, center.y + dy, center.z + dz, center.w +  dw });
					}
				}
			}
		}
	}
	
	return neighbors;
}