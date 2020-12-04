#ifndef DAY_4_PASSPORT_H
#define DAY_4_PASSPORT_H

#include <iostream>
#include <string>

class Passport
{
public:
	Passport() = default;

	// Getters for the different member variables

	std::string get_pid() const { return pid; }
	std::string get_cid() const { return cid; }
	std::string get_byr() const { return byr; }
	std::string get_iyr() const { return iyr; }
	std::string get_eyr() const { return eyr; }
	std::string get_hgt() const { return hgt; }
	std::string get_hcl() const { return hcl; }
	std::string get_ecl() const { return ecl; }

	// Sets field to value given
	void set_field(const std::string& field, const std::string& value);

	// Resets all fields to empty strings
	void reset();

	// Returns true if all fields are present (cid is optional)
	bool is_valid() const;
	
	// Returns true if all fields are present with valid values (cid is optional)
	bool is_valid_strict() const;

private:
	bool valid_pid() const;
	bool valid_range(const std::string& field, const int num_digits, const int min, const int max) const;
	bool valid_height() const;
	bool valid_hair_color() const;
	bool valid_eye_color() const;

	std::string pid;
	std::string cid;
	std::string byr;
	std::string iyr;
	std::string eyr;
	std::string hgt;
	std::string hcl;
	std::string ecl;
};

// Operators
std::ostream& operator<<(std::ostream& os, const Passport& passport);

#endif // !DAY_4_PASSPORT_H