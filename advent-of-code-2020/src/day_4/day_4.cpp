#include "Passport.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

static std::vector<Passport> create_passports(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<Passport> passports;
	Passport current_passport;

	// Parse input
	while (file)
	{
		std::string line;
		std::getline(file, line);

		// If line isn't empty, continue creating new passport with it's data.
		if (!line.empty())
		{
			std::istringstream line_stream(line);
			std::string kv_pair;
			while (line_stream >> kv_pair)
			{
				size_t key_end = kv_pair.find(':');
				current_passport.set_field(kv_pair.substr(0, key_end), kv_pair.substr(key_end + 1, kv_pair.length() - key_end));
				//std::cout << kv_pair.substr(0, key_end) << " | " << kv_pair.substr(key_end + 1, kv_pair.length() - key_end) << '\n';
			}

		}
		// If line was empty, that marks the end of this passport so we add it to the vector
		else
		{
			passports.push_back(current_passport);
			current_passport.reset();
			//std::cout << "===================================================\n";
		}
	}

	return passports;
}

void day_4_part_1()
{
	std::vector<Passport> passports = create_passports("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_4.txt");
	
	int valid_passports = 0;
	for (const Passport& p : passports)
	{
		if (p.is_valid())
		{
			//std::cout << p << '\n';
			++valid_passports;
		}
	}

	std::cout << "Day 4 part 1 | Number of valid passports: " << valid_passports << '\n';
}

void day_4_part_2()
{
	std::vector<Passport> passports = create_passports("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_4.txt");

	int valid_passports = 0;
	for (const Passport& p : passports)
	{
		if (p.is_valid_strict())
		{
			//std::cout << p << '\n';
			++valid_passports;
		}
	}

	std::cout << "Day 4 part 2 | Number of valid passports: " << valid_passports << '\n';
}