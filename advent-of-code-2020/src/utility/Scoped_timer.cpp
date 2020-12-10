#include "Scoped_timer.h"

#include <iostream>
#include <chrono>

Scoped_timer::Scoped_timer()
{
	m_begin = std::chrono::high_resolution_clock::now();
}

Scoped_timer::~Scoped_timer()
{
	m_end = std::chrono::high_resolution_clock::now();
	std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_begin).count() << " microseconds\n";
}