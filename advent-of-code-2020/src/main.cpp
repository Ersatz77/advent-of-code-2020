#include "utility/Timer.h"
#include "utility/Scoped_timer.h"

#include <iostream>
#include <stdexcept>

// Forward declare functions for each day
void day_1_part_1();
void day_1_part_2();

void day_2_part_1();
void day_2_part_2();

void day_3_part_1();
void day_3_part_2();

void day_4_part_1();
void day_4_part_2();

void day_5_part_1();
void day_5_part_2();
void day_5_v2();

void day_6_part_1();
void day_6_part_2();

void day_7_part_1();
void day_7_part_2();

void day_8_part_1();
void day_8_part_2();

void day_9_part_1();
void day_9_part_2();

void day_10_part_1();
void day_10_part_2();

void day_11_part_1();
void day_11_part_2();

int main()
{
	try
	{
		
		day_1_part_1();
		day_1_part_2();

		day_2_part_1();
		day_2_part_2();

		day_3_part_1();
		day_3_part_2();

		day_4_part_1();
		day_4_part_2();

		day_5_part_1();
		day_5_part_2();

		day_6_part_1();
		day_6_part_2();

		day_7_part_1();
		day_7_part_2();

		day_8_part_1();
		day_8_part_2();

		day_9_part_1();
		day_9_part_2();

		day_10_part_1();
		day_10_part_2();

		day_11_part_1();
		day_11_part_2();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}