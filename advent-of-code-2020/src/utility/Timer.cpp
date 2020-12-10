#include "Timer.h"

#include <chrono>

std::ostream& operator<<(std::ostream& os, const Timer& time)
{
	return os << std::chrono::duration_cast<std::chrono::microseconds>(time.m_end - time.m_begin).count() << " microseconds";
}