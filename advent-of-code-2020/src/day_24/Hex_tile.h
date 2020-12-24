#ifndef DAY_24_HEX_TILE_H
#define DAY_24_HEX_TILE_H

#include <unordered_set>

struct Hex_tile
{
	int q;
	int r;
};

bool operator==(const Hex_tile& lhs, const Hex_tile& rhs);

namespace std
{
	template <>
	struct hash<Hex_tile>
	{
		size_t operator()(const Hex_tile& t) const
		{
			size_t res = 17;
			res = res * 31 + hash<int>()(t.q);
			res = res * 31 + hash<int>()(t.r);
			return res;
		}
	};
}

#endif // !DAY_24_HEX_TILE_H