#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>

// Returns true if we're at the end of the file
static bool end_of_file(std::ifstream& ifs)
{
	char c = ' ';
	ifs >> c;
	if (ifs)
	{
		ifs.unget();
		return false;
	}
	else
	{
		return true;
	}
}

void day_2_part_1()
{
	std::string path = "D:\\Repositories\\advent-of-code-2020\\input\\day_2.txt";
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	// If file has been opened and is in a good state, parse text
	int valid_passwords = 0;
	while (file)
	{
		// Format: 4-7 z: zzzfzlzzz
		int min = 0;
		int max = 0;
		char letter = ' ';
		std::string password;

		file >> min;
		file.ignore(1);
		file >> max;
		file >> letter;
		file.ignore(1);
		file >> password;

		int64_t occurrences = std::count(password.begin(), password.end(), letter);
		if (occurrences >= min && occurrences <= max)
		{
			//std::cout << password << ' ' << letter << ' ' << min << ' ' << max << " | " << occurrences << '\n';
			++valid_passwords;
		}

		if (end_of_file(file))
		{
			break;
		}
	}

	std::cout << "Day 2 part 1 | Number of valid passwords: " << valid_passwords << '\n';
}

void day_2_part_2()
{
	std::string path = "D:\\Repositories\\advent-of-code-2020\\input\\day_2.txt";
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	int valid_passwords = 0;
	while (file)
	{
		// Format: 4-7 z: zzzfzlzzz
		size_t index_1 = 0;
		size_t index_2 = 0;
		char letter = ' ';
		std::string password;

		file >> index_1;
		file.ignore(1);
		file >> index_2;
		file >> letter;
		file.ignore(1);
		file >> password;

		// Check if either of the indexs contain the letter
		// The indexs aren't 0 based, so we need to correct them
		--index_1;
		--index_2;
		if ((password[index_1] == letter && password[index_2] != letter) || (password[index_1] != letter && password[index_2] == letter))
		{
			//std::cout << password << ' ' << letter << ' ' << index_1 - 1 << ' ' << index_2 - 1 << '\n';
			++valid_passwords;
		}

		if (end_of_file(file))
		{
			break;
		}
	}

	std::cout << "Day 2 part 2 | Number of valid passwords: " << valid_passwords << '\n';
}