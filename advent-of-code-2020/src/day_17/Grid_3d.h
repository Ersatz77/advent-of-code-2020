#ifndef DAY_17_GRID_3D_H
#define DAY_17_GRID_3D_H

#include "Cube_3d.h"

#include <vector>
#include <unordered_set>

class Grid_3d
{
public:
	Grid_3d(const std::vector<Cube_3d>& initial_cubes);

	size_t num_active() const { return m_active_cubes.size(); }

	void step();

private:
	std::vector<Cube_3d> get_neighbors(const Cube_3d& center) const;
	bool should_be_active(const Cube_3d& cube) const;

	std::unordered_set<Cube_3d> m_active_cubes;
};

#endif // !DAY_17_GRID_3D_H