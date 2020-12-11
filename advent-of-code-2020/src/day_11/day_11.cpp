#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

enum class Seat_state
{
	INVALID = 0,
	FLOOR,
	AVAILABLE,
	OCCUPIED
};

struct Seat
{
	int x;
	int y;
	Seat_state state;
};

constexpr int g_grid_width = 90;
constexpr int g_grid_height = 93;

std::vector<Seat> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<Seat> seats;
	std::string line;
	for (int y = 0; std::getline(file, line); ++y)
	{
		for (int x = 0; x < line.length(); ++x)
		{
			Seat seat{ x, y, Seat_state::FLOOR };
			if (line[x] == 'L')
			{
				seat.state = Seat_state::AVAILABLE;
			}

			seats.push_back(seat);
		}
	}

	return seats;
}

Seat& get_seat_at_pos(const int x, const int y, std::vector<Seat>& seats)
{
	for (Seat& seat : seats)
	{
		if (seat.x == x && seat.y == y)
		{
			return seat;
		}
	}

	static Seat s{ -1,-1, Seat_state::INVALID };
	return s;
}

int seats_occupied_around_pos(const int x, const int y, std::vector<Seat>& seats)
{
	int count = 0;
	if (get_seat_at_pos(x - 1, y - 1, seats).state == Seat_state::OCCUPIED)
	{
		++count;
	}
		
	if (get_seat_at_pos(x, y - 1, seats).state == Seat_state::OCCUPIED)
	{
		++count;
	}

	if (get_seat_at_pos(x + 1, y - 1, seats).state == Seat_state::OCCUPIED)
	{
		++count;
	}

	if (get_seat_at_pos(x - 1, y, seats).state == Seat_state::OCCUPIED)
	{
		++count;
	}

	if (get_seat_at_pos(x + 1, y, seats).state == Seat_state::OCCUPIED)
	{
		++count;
	}

	if (get_seat_at_pos(x - 1, y + 1, seats).state == Seat_state::OCCUPIED)
	{
		++count;
	}

	if (get_seat_at_pos(x, y + 1, seats).state == Seat_state::OCCUPIED)
	{
		++count;
	}

	if (get_seat_at_pos(x + 1, y + 1, seats).state == Seat_state::OCCUPIED)
	{
		++count;
	}

	return count;
}

int first_seats_occupied_around_pos(const int x, const int y, std::vector<Seat>& seats)
{
	int count = 0;

	// Up
	for (int offset = 1; offset < g_grid_height; ++offset)
	{
		const Seat& s = get_seat_at_pos(x, y - offset, seats);
		if (s.state != Seat_state::INVALID && s.state != Seat_state::FLOOR)
		{
			if (s.state == Seat_state::OCCUPIED)
			{
				++count;
			}
			break;
		}
	}

	// Down
	for (int offset = 1; offset < g_grid_height; ++offset)
	{
		const Seat& s = get_seat_at_pos(x, y + offset, seats);
		if (s.state != Seat_state::INVALID && s.state != Seat_state::FLOOR)
		{
			if (s.state == Seat_state::OCCUPIED)
			{
				++count;
			}
			break;
		}
	}

	// Left
	for (int offset = 1; offset < g_grid_width; ++offset)
	{
		const Seat& s = get_seat_at_pos(x - offset, y, seats);
		if (s.state != Seat_state::INVALID && s.state != Seat_state::FLOOR)
		{
			if (s.state == Seat_state::OCCUPIED)
			{
				++count;
			}
			break;
		}
	}

	// Right
	for (int offset = 1; offset < g_grid_width; ++offset)
	{
		const Seat& s = get_seat_at_pos(x + offset, y, seats);
		if (s.state != Seat_state::INVALID && s.state != Seat_state::FLOOR)
		{
			if (s.state == Seat_state::OCCUPIED)
			{
				++count;
			}
			break;
		}
	}

	// Top Left
	for (int offset = 1; offset < g_grid_height; ++offset)
	{
		const Seat& s = get_seat_at_pos(x - offset, y - offset, seats);
		if (s.state != Seat_state::INVALID && s.state != Seat_state::FLOOR)
		{
			if (s.state == Seat_state::OCCUPIED)
			{
				++count;
			}
			break;
		}
	}

	// Top Right
	for (int offset = 1; offset < g_grid_height; ++offset)
	{
		const Seat& s = get_seat_at_pos(x + offset, y - offset, seats);
		if (s.state != Seat_state::INVALID && s.state != Seat_state::FLOOR)
		{
			if (s.state == Seat_state::OCCUPIED)
			{
				++count;
			}
			break;
		}
	}

	// Bottom Left
	for (int offset = 1; offset < g_grid_height; ++offset)
	{
		const Seat& s = get_seat_at_pos(x - offset, y + offset, seats);
		if (s.state != Seat_state::INVALID && s.state != Seat_state::FLOOR)
		{
			if (s.state == Seat_state::OCCUPIED)
			{
				++count;
			}
			break;
		}
	}

	// Bottom Right
	for (int offset = 1; offset < g_grid_height; ++offset)
	{
		const Seat& s = get_seat_at_pos(x + offset, y + offset, seats);
		if (s.state != Seat_state::INVALID && s.state != Seat_state::FLOOR)
		{
			if (s.state == Seat_state::OCCUPIED)
			{
				++count;
			}
			break;
		}
	}

	return count;
}

void day_11_part_1()
{
	std::vector<Seat> seats = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_11.txt");
	std::vector<Seat> temp_seats = seats;

	int changed_seats = -1;
	while (changed_seats != 0)
	{
		changed_seats = 0;
		for (int i = 0; i < seats.size(); ++i)
		{
			int x = seats[i].x;
			int y = seats[i].y;
			if (seats[i].state == Seat_state::AVAILABLE && seats_occupied_around_pos(x, y, seats) == 0)
			{
				temp_seats[i].state = Seat_state::OCCUPIED;
				++changed_seats;
			}
			else if (seats[i].state == Seat_state::OCCUPIED && seats_occupied_around_pos(x, y, seats) >= 4)
			{
				temp_seats[i].state = Seat_state::AVAILABLE;
				++changed_seats;
			}
		}

		seats = temp_seats;
	}

	int occupied_seats = 0;
	std::for_each(seats.begin(), seats.end(), [&occupied_seats](const Seat& s) { if (s.state == Seat_state::OCCUPIED) { ++occupied_seats; }});

	std::cout << "Day 11 part 1 | Number of occupied seats: " << occupied_seats << '\n';
}

void day_11_part_2()
{
	std::vector<Seat> seats = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_11.txt");
	std::vector<Seat> temp_seats = seats;

	int changed_seats = -1;
	while (changed_seats != 0)
	{
		changed_seats = 0;
		for (int i = 0; i < seats.size(); ++i)
		{
			int x = seats[i].x;
			int y = seats[i].y;
			if (seats[i].state == Seat_state::AVAILABLE && first_seats_occupied_around_pos(x, y, seats) == 0)
			{
				temp_seats[i].state = Seat_state::OCCUPIED;
				++changed_seats;
			}
			else if (seats[i].state == Seat_state::OCCUPIED && first_seats_occupied_around_pos(x, y, seats) >= 5)
			{
				temp_seats[i].state = Seat_state::AVAILABLE;
				++changed_seats;
			}
		}

		seats = temp_seats;
	}

	int occupied_seats = 0;
	std::for_each(seats.begin(), seats.end(), [&occupied_seats](const Seat& s) { if (s.state == Seat_state::OCCUPIED) { ++occupied_seats; }});

	std::cout << "Day 11 part 2 | Number of occupied seats: " << occupied_seats << '\n';
}