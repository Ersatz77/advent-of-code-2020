#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

struct Bus
{
	int id;
	int64_t time;
};
struct Schedule
{
	int earliest_depart_time;
	std::vector<Bus> busses;
};

Schedule parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	int earliest_depart_time = 0;
	std::vector<Bus> busses;

	file >> earliest_depart_time;

	while (file)
	{
		char temp = ' ';
		int bus_id = -1;
		file >> temp;
		if (std::isdigit(temp))
		{
			file.unget();
			file >> bus_id;
			
		}

		busses.push_back(Bus{ bus_id, 0 });
		file.ignore(1, ',');
	}

	return Schedule{ earliest_depart_time, busses };
}

int64_t multiplicative_inverse(int64_t a, int64_t b)
{
	int64_t b0 = b;
	int64_t t = 0; 
	int64_t q = 0 ;
	int64_t x0 = 0;
	int64_t x1 = 1;

	if (b == 1)
	{
		return 1;
	}

	while (a > 1)
	{
		q = a / b;
		t = b;
		b = a % b;
		a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}

	if (x1 < 0)
	{
		x1 += b0;
	}

	return x1;
}

int64_t chinese_remainder(const std::vector<int64_t>& n, const std::vector<int64_t>& a)
{
	int64_t product = 1;
	int64_t sum = 0;

	std::for_each(n.begin(), n.end(), [&product](const int64_t i) { product *= i; });

	for (size_t i = 0; i < n.size(); i++)
	{
		int64_t p = product / n[i];
		sum += a[i] * multiplicative_inverse(p, n[i]) * p;
	}

	return sum % product;
}

void day_13_part_1()
{
	Schedule schedule = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_13.txt");

	// Simulate busses
	Bus earliest_bus{ -1, std::numeric_limits<int64_t>::max() };
	for (Bus& bus : schedule.busses)
	{
		if (bus.id != -1)
		{
			while (bus.time <= schedule.earliest_depart_time)
			{
				bus.time += bus.id;
			}

			// Add this bus as the earliest bus if it arrives earlier
			if (bus.time < earliest_bus.time)
			{
				earliest_bus = bus;
			}
		}
	}

	std::cout << "Day 13 part 1 | Earliest bus: " << earliest_bus.id * (earliest_bus.time - schedule.earliest_depart_time) << '\n';
}

void day_13_part_2()
{
	Schedule schedule = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_13.txt");
	
	std::vector<int64_t> n;
	std::vector<int64_t> a;
	for (size_t i = 0; i < schedule.busses.size(); ++i)
	{
		if (schedule.busses[i].id != -1)
		{
			n.push_back(schedule.busses[i].id);
			a.push_back(((-static_cast<int64_t>(i)) + schedule.busses[i].id) % schedule.busses[i].id);
		}
	}

	std::cout << "Day 13 part 2 | Earliest bus: " << chinese_remainder(n, a) << '\n';
}