#include "day_7.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

struct Bag
{
	std::string name;
	int amount;
};

using Rules = std::unordered_map<std::string, std::vector<Bag>>;

Rules parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	Rules rules;

	std::string line;
	std::string junk;

	std::string adjective;
	std::string color;
	std::string inner_adjective;
	std::string inner_color;

	while (std::getline(file, line))
	{
		std::istringstream line_stream(line);
		line_stream >> adjective >> color >> junk >> junk;
		while (line_stream)
		{
			int amount = 0;
			if (line_stream >> amount >> inner_adjective >> inner_color >> junk)
			{
				rules[adjective + ' ' + color].push_back(Bag{ inner_adjective + ' ' + inner_color, amount });
			}
		}
	}

	return rules;
}

bool contains_shiny_gold_bag(const std::string& starting_bag, const Rules& rules)
{
	//std::cout << starting_bag << '\n';

	if (rules.count(starting_bag) > 0)
	{
		// Check if this bag contains a shiny gold bag
		for (const Bag& bag : rules.at(starting_bag))
		{
			// If this bag has a shiny gold bag, return true
			if (bag.name == "shiny gold")
			{
				return true;
			}

			// If it didn't have a shiny gold bag, recursively check what bags can fit into the current bag
			if (contains_shiny_gold_bag(bag.name, rules))
			{
				return true;
			}
		}
	}

	return false;
}

int bags_in_shiny_gold_bag(const std::string& starting_bag, const Rules& rules)
{
	//std::cout << starting_bag << '\n';

	// We initialize count at 1 becuase we need to include the current bag
	int count = 1;

	// Only check rules for this bag if this bag can contain other bags (map key exists)
	if (rules.count(starting_bag) > 0)
	{
		for (const Bag& bag : rules.at(starting_bag))
		{
			count += (bag.amount * bags_in_shiny_gold_bag(bag.name, rules));
		}
	}

	return count;
}

void day_7_part_1(const std::string& input_path)
{
	Rules rules = parse_input(input_path + "day_7.txt");

	// Count number of bags that will eventually have a shiny gold bag
	int count = 0;
	for (Rules::iterator it = rules.begin(); it != rules.end(); ++it)
	{
		if (contains_shiny_gold_bag(it->first, rules))
		{
			++count;
		}
	}


	std::cout << "Day 7 part 1 | Bags that eventually contain a shiny gold bag: " << count << '\n';
}

void day_7_part_2(const std::string& input_path)
{
	Rules rules = parse_input(input_path + "day_7.txt");

	std::cout << "Day 7 part 2 | Bags inside a shiny gold bag: " << bags_in_shiny_gold_bag("shiny gold", rules) - 1 << '\n';
}