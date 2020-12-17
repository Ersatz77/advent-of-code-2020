#ifndef DAY_17_GRID_4D_H
#define DAY_17_GRID_4D_H

#include "Cube_4d.h"

#include <vector>
#include <unordered_set>

class Grid_4d
{
public:
	Grid_4d(const std::vector<Cube_4d>& initial_cubes);

	size_t num_active() const { return m_active_cubes.size(); }

	void step();

private:
	bool should_be_active(const Cube_4d& cube) const;
	std::vector<Cube_4d> get_neighbors(const Cube_4d& center) const;

	std::unordered_set<Cube_4d> m_active_cubes;
};

#endif // !DAY_17_GRID_4D_H