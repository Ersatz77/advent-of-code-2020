#include "day_21.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stdexcept>

void parse_input(const std::string& path, std::map<std::string, std::set<std::string>>& allergens_map, std::vector<std::string>& all_ingredients)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::string line;
	std::string ingredient;
	std::string allergen;
	while (std::getline(file, line))
	{
		std::istringstream line_stream(line);
		std::set<std::string> current_ingredients;
		std::set<std::string> current_allergens;

		// Read in all ingredients until we reach '('
		while (line_stream >> ingredient)
		{
			if (ingredient[0] == '(')
			{
				break;
			}

			current_ingredients.insert(ingredient);
		}

		// Add all current ingredients to all ingredients vector
		std::for_each(current_ingredients.begin(), current_ingredients.end(), [&all_ingredients](const std::string& i) { all_ingredients.push_back(i); });

		// Read in all allergens while also trimming off the last character
		while (line_stream >> allergen)
		{
			allergen.erase(allergen.end() - 1);
			current_allergens.insert(allergen);

			// If this allergen hasn't been added, add a new entry in the allergen map with all the current ingredients
			if (allergens_map.count(allergen) == 0)
			{
				allergens_map[allergen] = current_ingredients;
			}
			else
			{
				// If it did exist, remove all ingredients that aren't the same between the current ingredients 
				// and the ingredients already stored in the map entry
				std::set<std::string>& ingredients_at_allergen = allergens_map[allergen];
				std::set<std::string> intersection;
				std::set_intersection(ingredients_at_allergen.begin(), ingredients_at_allergen.end(), current_ingredients.begin(), current_ingredients.end(), std::inserter(intersection, intersection.begin()));
				ingredients_at_allergen = intersection;
			}
		}
	}
}

std::map<std::string, std::string> find_confirmed_allergens(std::map<std::string, std::set<std::string>> allergen_map)
{
	std::map<std::string, std::string> confirmed_allergens;

	// Loop while any allergen's ingredient list isn't empty
	while (std::any_of(allergen_map.begin(), allergen_map.end(), [](const auto& kv) { return !kv.second.empty(); }))
	{
		// Find allergen with only 1 ingredient
		for (auto& [allergen, ingredients] : allergen_map)
		{
			// If this allergen has an ingredients list of 1, it's ingredient is confirmed to cause the allergen
			if (ingredients.size() == 1)
			{
				std::string allergic_ingredient = *ingredients.begin();
				confirmed_allergens[allergen] = allergic_ingredient;

				// Remove that ingredient from all allergens
				for (auto& [key, value] : allergen_map)
				{
					value.erase(allergic_ingredient);
				}

				break;
			}
		}
	}

	return confirmed_allergens;
}

void day_21_part_1(const std::string& input_path)
{
	std::map<std::string, std::set<std::string>> allergen_map;
	std::vector<std::string> all_ingredients;
	parse_input(input_path + "day_21.txt", allergen_map, all_ingredients);

	// Filter allergen map until we have a map of all confirmed allergens
	std::map<std::string, std::string> confirmed_allergens = find_confirmed_allergens(allergen_map);

	// Remove all allergens from all ingredients
	for (const auto& [key, value] : confirmed_allergens)
	{
		all_ingredients.erase(std::remove(all_ingredients.begin(), all_ingredients.end(), value), all_ingredients.end());
	}

	std::cout << "Day 21 part 1 | Total ingredients without allergens: " << all_ingredients.size() << '\n';
}

void day_21_part_2(const std::string& input_path)
{
	std::map<std::string, std::set<std::string>> allergen_map;
	std::vector<std::string> all_ingredients;
	parse_input(input_path + "day_21.txt", allergen_map, all_ingredients);

	// Filter allergen map until we have a map of all confirmed allergens
	std::map<std::string, std::string> confirmed_allergens = find_confirmed_allergens(allergen_map);

	// Create a comma separated string of all allergens
	std::string allergen_str;
	for (const auto& [key, value] : confirmed_allergens)
	{
		allergen_str += value + ',';
	}

	allergen_str.erase(allergen_str.end() - 1);

	std::cout << "Day 21 part 2 | Canonical dangerous ingredient list: " << allergen_str << '\n';
}