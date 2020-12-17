#ifndef DAY_17_CUBE_4D_H
#define DAY_17_CUBE_4D_H

#include <unordered_set>

struct Cube_4d
{
    int x = 0;
    int y = 0;
    int z = 0;
    int w = 0;
};

bool operator==(const Cube_4d& lhs, const Cube_4d& rhs);

namespace std
{
    template <>
    struct hash<Cube_4d>
    {
        size_t operator()(const Cube_4d& c) const
        {
            size_t res = 17;
            res = res * 31 + hash<int>()(c.x);
            res = res * 31 + hash<int>()(c.y);
            res = res * 31 + hash<int>()(c.z);
            res = res * 31 + hash<int>()(c.w);
            return res;
        }
    };
}

#endif // !DAY_17_CUBE_4D_H