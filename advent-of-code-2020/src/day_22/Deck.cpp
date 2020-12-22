#include "Deck.h"

#include <iostream>
#include <vector>
#include <algorithm>

Deck::Deck(const std::string& name, const std::vector<int>& cards) :
	m_name(name),
	m_cards(cards)
{
}

int Deck::draw()
{
	// Get card at the end of the vector and remove it
	int card = m_cards.back();
	m_cards.pop_back();

	return card;
}

void Deck::add(const int card)
{
	m_cards.insert(m_cards.begin(), card);
}

uint64_t Deck::get_score() const
{
	// Check if this deck is empty
	if (m_cards.empty())
	{
		return 0;
	}

	uint64_t score = 0;
	for (size_t i = 0; i < m_cards.size(); ++i)
	{
		score += m_cards[i] * (i + 1);
	}

	return score;
}

std::string Deck::to_string() const
{
	std::string str = m_name;
	for (const int i : m_cards)
	{
		str += i;
	}

	return str;
}

std::ostream& operator<<(std::ostream& os, const Deck& deck)
{
	os << deck.get_name() << " | Cards: ";
	const std::vector<int>& cards = deck.get_cards();
	for (size_t i = 0; i < cards.size(); ++i)
	{
		os << cards[i];
		if (i < cards.size() - 1)
		{
			os << ", ";
		}
	}

	return os;
}