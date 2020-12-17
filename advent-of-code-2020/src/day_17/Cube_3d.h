#ifndef DAY_17_CUBE_3D_H
#define DAY_17_CUBE_3D_H

#include <unordered_set>

struct Cube_3d
{
	int x = 0;
	int y = 0;
	int z = 0;
};

bool operator==(const Cube_3d& lhs, const Cube_3d& rhs);

namespace std
{
    template <>
    struct hash<Cube_3d>
    {
        size_t operator()(const Cube_3d& c) const
        {
            size_t res = 17;
            res = res * 31 + hash<int>()(c.x);
            res = res * 31 + hash<int>()(c.y);
            res = res * 31 + hash<int>()(c.z);
            return res;
        }
    };
}

#endif // !DAY_17_CUBE_3D_H