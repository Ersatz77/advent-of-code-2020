#ifndef DAY_22_DECK_H
#define DAY_22_DECK_H

#include <iostream>
#include <string>
#include <vector>

class Deck
{
public:
	Deck(const std::string& name, const std::vector<int>& cards);

	// Draws the top card from the deck
	int draw();

	// Adds a card to the bottom of the deck
	void add(const int card);

	// Returns the score of this deck
	uint64_t get_score() const;

	// Returns all cards in this deck
	std::vector<int> get_cards() const { return m_cards; }

	// Returns the number of cards in the deck
	size_t get_number_cards() const { return m_cards.size(); }

	// Returns the name of who owns this deck
	std::string get_name() const { return m_name; }

	// Get current deck state as a string with no spaces
	std::string to_string() const;

private:
	std::string m_name;

	// Deck is reversed. index 0 is actually the bottom of the card.
	std::vector<int> m_cards;
};

std::ostream& operator<<(std::ostream& os, const Deck& deck);

#endif // !DAY_22_DECK_H