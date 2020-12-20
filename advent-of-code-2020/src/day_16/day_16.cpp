#include "day_16.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

struct Rule
{
	std::string name;
	int min_a;
	int max_a;
	int min_b;
	int max_b;
};

bool matches_any_rule(const int value, const std::vector<Rule>& rules)
{
	for (const Rule& rule : rules)
	{
		if ((value >= rule.min_a && value <= rule.max_a) || (value >= rule.min_b && value <= rule.max_b))
		{
			return true;
		}
	}

	return false;
}

void parse_input(const std::string& path, std::vector<Rule>& rules, std::vector<int>& my_ticket, std::vector<std::vector<int>>& tickets, uint64_t& error_rate)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::string junk_str;
	char junk_ch = ' ';

	int min_a = 0;
	int max_a = 0;
	int min_b = 0;
	int max_b = 0;
	std::string line;
	std::string field_name;
	std::string field_name_temp;

	while (std::getline(file, line))
	{
		// Break if there's nothing to input
		if (line.empty())
		{
			break;
		}

		std::istringstream line_stream(line);
		line_stream >> field_name;

		// Add rest of field name if it exists
		if (field_name.back() != ':')
		{
			field_name += ' ';
			line_stream >> field_name_temp;
			field_name += field_name_temp;

		}

		if (field_name.back() == ':')
		{
			field_name.pop_back();
		}

		line_stream >> min_a;
		line_stream.ignore(1, '-');
		line_stream >> max_a;
		line_stream.ignore(4);
		line_stream >> min_b;
		line_stream.ignore(1, '-');
		line_stream >> max_b;

		rules.push_back(Rule{ field_name, min_a, max_a, min_b, max_b });
	}

	// Get my ticket
	file >> junk_str >> junk_str;
	int my_ticket_value = 0;

	for (size_t i = 0; i < rules.size(); ++i)
	{
		file >> my_ticket_value;
		my_ticket.push_back(my_ticket_value);

		if (i < rules.size() - 1)
		{
			file >> junk_ch;
		}
	}

	// Get nearby tickets
	std::getline(file, junk_str);
	std::getline(file, junk_str);
	int nearby_ticket_value = 0;

	while (std::getline(file, line))
	{
		
		// Break if there's nothing to input
		if (line.empty())
		{
			break;
		}

		std::istringstream line_stream(line);
		std::vector<int> temp_ticket;
		bool valid_ticket = true;

		for (size_t i = 0; i < rules.size(); ++i)
		{
			line_stream >> nearby_ticket_value;
			temp_ticket.push_back(nearby_ticket_value);

			// Check if this ticket value is valid for any rule
			if (!matches_any_rule(nearby_ticket_value, rules))
			{
				error_rate += nearby_ticket_value;
				valid_ticket = false;
			}

			if (i < rules.size() - 1)
			{
				line_stream >> junk_ch;
			}
		}

		// Only add valid tickets
		if (valid_ticket)
		{
			tickets.push_back(temp_ticket);
		}
	}
}

void day_16_part_1(const std::string& input_path)
{
	std::vector<Rule> rules;
	std::vector<int> my_ticket;
	std::vector<std::vector<int>> tickets;
	uint64_t error_rate = 0;

	parse_input(input_path + "day_16.txt", rules, my_ticket, tickets, error_rate);

	std::cout << "Day 16 part 1 | Error rate: " << error_rate << '\n';
}

void day_16_part_2(const std::string& input_path)
{
	std::vector<Rule> rules;
	std::vector<int> my_ticket;
	std::vector<std::vector<int>> tickets;
	uint64_t error_rate = 0;

	parse_input(input_path + "day_16.txt", rules, my_ticket, tickets, error_rate);

	// Fill possible index vector with true values
	std::vector<std::vector<bool>> possible_indexes;
	for (size_t i = 0; i < rules.size(); ++i)
	{
		std::vector<bool> temp;
		for (size_t j = 0; j < tickets.front().size(); ++j)
		{
			temp.push_back(true);
		}

		possible_indexes.push_back(temp);
	}

	// Find what ticket indexes are valid for each rule
	for (const std::vector<int>& ticket : tickets)
	{
		for (size_t i = 0; i < ticket.size(); ++i)
		{
			for (size_t j = 0; j < rules.size(); ++j)
			{
				if (!((ticket[i] >= rules[j].min_a && ticket[i] <= rules[j].max_a) || (ticket[i] >= rules[j].min_b && ticket[i] <= rules[j].max_b)))
				{
					possible_indexes[j][i] = false;
				}
			}
		}
	}

	// Narrow down possibilities until we have all rules with only 1 index with true
	int rules_With_one_index = 0;
	while (rules_With_one_index < possible_indexes.size())
	{
		//std::for_each(possible_indexes.begin(), possible_indexes.end(), [](const std::vector<bool>& idx) { for (const bool b : idx) { std::cout << b << ' '; } std::cout << "\n"; });
		//std::cout << "===============================================================\n";

		rules_With_one_index = 0;
		for (size_t i = 0; i < possible_indexes.size(); ++i)
		{
			// Check if this rule would only have one index
			if (std::count(possible_indexes[i].begin(), possible_indexes[i].end(), true) == 1)
			{
				// Increment the count for rules with one index
				++rules_With_one_index;

				// Get the index what has the only true value
				size_t index = std::distance(possible_indexes[i].begin(), std::find(possible_indexes[i].begin(), possible_indexes[i].end(), true));

				// Remove all instances of this index in all other rules
				for (size_t j = 0; j < possible_indexes.size(); ++j)
				{
					if (j != i)
					{
						possible_indexes[j][index] = false;
					}
				}
			}
		}
	}

	// Get product of depart fields in my ticket
	uint64_t product = 1;
	for (size_t i = 0; i < possible_indexes.size(); ++i)
	{
		if (rules[i].name.find("depart") != std::string::npos)
		{
			size_t index = std::distance(possible_indexes[i].begin(), std::find(possible_indexes[i].begin(), possible_indexes[i].end(), true));
			product *= my_ticket[index];
		}
	}

	std::cout << "Day 16 part 2 | Product of depart fields: " << product << '\n';
}