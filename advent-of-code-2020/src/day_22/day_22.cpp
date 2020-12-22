#include "day_22.h"

#include "Deck.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stdexcept>

std::vector<Deck> parse_input(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::vector<Deck> decks;

	std::string line;
    std::string name;
	std::string card;
	while (std::getline(file, line))
	{
		if (line.find("Player") != std::string::npos)
		{
			name = line;
			name.erase(name.end() - 1);

			std::vector<int> cards;
			
			while (std::getline(file, card))
			{
				if (card.empty())
				{
					break;
				}

				cards.push_back(std::stoi(card));
			}

			// Reverse cards so it's in the proper order and add it to the vector
			std::reverse(cards.begin(), cards.end());
			decks.push_back(Deck(name, cards));
		}
	}

	return decks;
}

Deck combat(Deck player_1, Deck player_2)
{
	while (player_1.get_number_cards() != 0 && player_2.get_number_cards() != 0)
	{
		// Each player draws a card
		int p1_card = player_1.draw();
		int p2_card = player_2.draw();

		if (p1_card > p2_card)
		{
			player_1.add(p1_card);
			player_1.add(p2_card);
		}
		else
		{
			player_2.add(p2_card);
			player_2.add(p1_card);
		}
	}

	// Return deck of winning player
	if (player_1.get_number_cards() == 0)
	{
		return player_2;
	}
	else
	{
		return player_1;
	}
}

Deck recursive_combat(Deck player_1, Deck player_2)
{
	std::unordered_set<std::string> previous_decks;

	while (player_1.get_number_cards() != 0 && player_2.get_number_cards() != 0)
	{
		// Check if the current decks on both players has already been played
		std::string current_decks = player_1.to_string() + '|' + player_2.to_string();
		if (previous_decks.find(current_decks) != previous_decks.end())
		{
			return player_1;
		}

		// Add current deck states to set
		previous_decks.insert(current_decks);

		// Each player draws a card
		int p1_card = player_1.draw();
		int p2_card = player_2.draw();

		// Start a subgame if both players have at least as many cards as the value they just drew
		if (player_1.get_number_cards() >= p1_card && player_2.get_number_cards() >= p2_card)
		{
			// Create decks for subgame
			const std::vector<int>& player_1_cards = player_1.get_cards();
			const std::vector<int>& player_2_cards = player_2.get_cards();

			Deck p1_subgame_deck(player_1.get_name(), std::vector<int>(player_1_cards.end() - p1_card, player_1_cards.end()));
			Deck p2_subgame_deck(player_2.get_name(), std::vector<int>(player_2_cards.end() - p2_card, player_2_cards.end()));

			// Play subgame and determine winner
			Deck winning_subgame_deck = recursive_combat(p1_subgame_deck, p2_subgame_deck);
			if (winning_subgame_deck.get_name() == player_1.get_name())
			{
				player_1.add(p1_card);
				player_1.add(p2_card);
			}
			else
			{
				player_2.add(p2_card);
				player_2.add(p1_card);
			}
		}
		else
		{
			// One player must not have had enough cards to recurse
			if (p1_card > p2_card)
			{
				player_1.add(p1_card);
				player_1.add(p2_card);
			}
			else
			{
				player_2.add(p2_card);
				player_2.add(p1_card);
			}
		}
	}

	// Return deck of winning player
	if (player_1.get_number_cards() == 0)
	{
		return player_2;
	}
	else
	{
		return player_1;
	}
}

void day_22_part_1(const std::string& input_path)
{
	std::vector<Deck> decks = parse_input(input_path + "day_22.txt");
	Deck player_1 = decks[0];
	Deck player_2 = decks[1];

	std::cout << "Day 22 part 1 | Score: " << combat(player_1, player_2).get_score() << '\n';
}

void day_22_part_2(const std::string& input_path)
{
	std::vector<Deck> decks = parse_input(input_path + "day_22.txt");
	Deck player_1 = decks[0];
	Deck player_2 = decks[1];

	std::cout << "Day 22 part 2 | Score: " << recursive_combat(player_1, player_2).get_score() << '\n';
}