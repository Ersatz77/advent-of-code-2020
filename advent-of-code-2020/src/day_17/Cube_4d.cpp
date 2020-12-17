#include "Cube_4d.h"

bool operator==(const Cube_4d& lhs, const Cube_4d& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}