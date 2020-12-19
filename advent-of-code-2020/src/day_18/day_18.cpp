#include "day_18.h"

#include "Calculator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

std::vector<std::string> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<std::string> expressions;
	std::string line;
	while (std::getline(file, line))
	{
		expressions.push_back(line);
	}

	return expressions;
}

void day_18_part_1()
{
	std::vector<std::string> expressions = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_18.txt");
	Calculator calc;

	int64_t sum = 0;
	for (const std::string& expression : expressions)
	{
		sum += calc.calculate_v1(expression);
	}

	std::cout << "Day 18 part 1 | Sum: " << sum << '\n';
}

void day_18_part_2()
{
	std::vector<std::string> expressions = parse_input("D:\\Repositories\\advent-of-code-2020\\advent-of-code-2020\\input\\day_18.txt");
	Calculator calc;

	int64_t sum = 0;
	for (const std::string& expression : expressions)
	{
		sum += calc.calculate_v2(expression);
	}

	std::cout << "Day 18 part 2 | Sum: " << sum << '\n';
}