#ifndef SCOPED_TIMER_H

#include <iostream>
#include <chrono>

// Prints time as soon as it goes out of scope
class Scoped_timer
{
public:
	Scoped_timer();
	~Scoped_timer();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
};

#endif // !SCOPED_TIMER_H