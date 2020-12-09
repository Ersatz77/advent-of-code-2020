#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

class Timer
{
public:
	Timer() = default;

	void begin() { m_begin = std::chrono::high_resolution_clock::now(); };
	void end() { m_end = std::chrono::high_resolution_clock::now(); };

	friend std::ostream& operator<<(std::ostream& os, const Timer& time);

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
};

std::ostream& operator<<(std::ostream& os, const Timer& time);

#endif // !TIMER_H