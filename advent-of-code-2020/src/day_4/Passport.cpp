#include "Passport.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

void Passport::set_field(const std::string& field, const std::string& value)
{
	if (field == "pid")
	{
		pid = value;
	}

	if (field == "cid")
	{
		cid = value;
	}

	if (field == "byr")
	{
		byr = value;
	}

	if (field == "iyr")
	{
		iyr = value;
	}

	if (field == "eyr")
	{
		eyr = value;
	}

	if (field == "hgt")
	{
		hgt = value;
	}

	if (field == "hcl")
	{
		hcl = value;
	}

	if (field == "ecl")
	{
		ecl = value;
	}
}

void Passport::reset()
{
	pid.clear();
	cid.clear();
	byr.clear();
	iyr.clear();
	eyr.clear();
	hgt.clear();
	hcl.clear();
	ecl.clear();
}

// Returns true if all fields are present (cid is optional)
bool Passport::is_valid() const
{
	return (!pid.empty() && !byr.empty() && !iyr.empty() && !eyr.empty() && !hgt.empty() && !hcl.empty() && !ecl.empty());
}

// Returns true if all fields are present with valid values
bool Passport::is_valid_strict() const
{
	try
	{
		return valid_pid() && valid_range(byr, 4, 1920, 2002) && valid_range(iyr, 4, 2010, 2020) && valid_range(eyr, 4, 2020, 2030) && valid_height() && valid_hair_color() && valid_eye_color();
	}
	catch (...)
	{
		return false;
	}
}

bool Passport::valid_pid() const
{
	bool valid_characters = true;
	for (const char c : pid)
	{
		if (!std::isdigit(c))
		{
			valid_characters = false;
		}
	}

	return (pid.length() == 9 && valid_characters);
}

// Returns true if the field has a valid range (inclusive)
bool Passport::valid_range(const std::string& field, const int num_digits, const int min, const int max) const
{
	int value = std::stoi(field);
	return field.length() == num_digits && value >= min && value <= max;
}

bool Passport::valid_height() const
{
	std::istringstream is(hgt);
	int height = 0;
	std::string measurement_type;
	is >> height >> measurement_type;

	if (measurement_type == "cm")
	{
		return height >= 150 && height <= 193;
	}
	else if (measurement_type == "in")
	{
		return height >= 59 && height <= 76;
	}
	else
	{
		return false;
	}
}

bool Passport::valid_hair_color() const
{
	if (hcl.length() == 7 && hcl[0] == '#')
	{
		for (int i = 1; i <= 6; ++i)
		{
			if (!std::isxdigit(hcl[i]))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool Passport::valid_eye_color() const
{
	return ecl == "amb" || ecl == "blu" || ecl == "brn" || ecl == "gry" || ecl == "grn" || ecl == "hzl" || ecl == "oth";
}

std::ostream& operator<<(std::ostream& os, const Passport& passport)
{
	return os << passport.get_pid()
		<< ' ' << passport.get_cid()
		<< ' ' << passport.get_byr()
		<< ' ' << passport.get_iyr()
		<< ' ' << passport.get_eyr()
		<< ' ' << passport.get_hgt()
		<< ' ' << passport.get_hcl()
		<< ' ' << passport.get_ecl();
}