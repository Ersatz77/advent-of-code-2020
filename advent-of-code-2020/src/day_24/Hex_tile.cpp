#include "Hex_tile.h"

bool operator==(const Hex_tile& lhs, const Hex_tile& rhs)
{
	return lhs.q == rhs.q && lhs.r == rhs.r;
}