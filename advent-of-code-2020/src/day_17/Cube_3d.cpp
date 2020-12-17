#include "Cube_3d.h"

bool operator==(const Cube_3d& lhs, const Cube_3d& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}