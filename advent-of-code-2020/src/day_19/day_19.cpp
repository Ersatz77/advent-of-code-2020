#include "day_19.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <regex>
#include <stdexcept>

void parse_input(const std::string& path, std::unordered_map<int, std::string>& rule_map, std::vector<std::string>& messages)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	// Read rules
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			break;
		}

		// Get position of colon
		size_t colon_pos = line.find_first_of(':');

		// Get rule number
		int rule_number = std::stoi(line.substr(0, colon_pos));

		// Get rest of rule
		std::string rule = line.substr(colon_pos + 2);
		rule.erase(std::remove(rule.begin(), rule.end(), '\"'), rule.end());
		rule_map[rule_number] = rule;
	}

	// Read messages
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			break;
		}

		messages.push_back(line);
	}
}


std::string generate_regex(const std::unordered_map<int, std::string>& rule_map, const int current_rule)
{
	std::string regex;
	std::istringstream subrule_stream(rule_map.at(current_rule));
	for (std::string subrule; subrule_stream >> subrule; )
	{
		if (std::isdigit(subrule.front()))
		{
			regex += generate_regex(rule_map, std::stoi(subrule));
		}
		else
		{
			regex += subrule;
		}
	}

	return '(' + regex + ')';
}

void day_19_part_1(const std::string& input_path)
{
	std::unordered_map<int, std::string> rule_map;
	std::vector<std::string> messages;
	parse_input(input_path + "day_19.txt", rule_map, messages);

	// Create regex from string
	std::regex regex(generate_regex(rule_map, 0));

	// Count number of messages that match the regex
	int count = 0;
	for (const std::string& message : messages)
	{
		count += std::regex_match(message, regex);
	}

	std::cout << "Day 19 part 1 | Number of messages that match rules: " << count << '\n';
}

void day_19_part_2(const std::string& input_path)
{
	std::unordered_map<int, std::string> rule_map;
	std::vector<std::string> messages;
	parse_input(input_path + "day_19.txt", rule_map, messages);

	// Override rules in rule map :wtfix:
	rule_map[8] = "42 +";
	rule_map[11] = "42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 ( 42 31 | 42 31 ) 31 ) 31 ) 31 ) 31 ) 31 ) 31 ) 31 ) 31 ) 31 ) 31";

	// Create regex from string
	std::regex regex(generate_regex(rule_map, 0));

	// Count number of messages that match the regex
	int count = 0;
	for (const std::string& message : messages)
	{
		count += std::regex_match(message, regex);
	}

	std::cout << "Day 19 part 2 | Number of messages that match rules: " << count << '\n';
}