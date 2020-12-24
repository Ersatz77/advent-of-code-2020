#include "utility/Timer.h"
#include "utility/Scoped_timer.h"

#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include "day_4/day_4.h"
#include "day_5/day_5.h"
#include "day_6/day_6.h"
#include "day_7/day_7.h"
#include "day_8/day_8.h"
#include "day_9/day_9.h"
#include "day_10/day_10.h"
#include "day_11/day_11.h"
#include "day_12/day_12.h"
#include "day_13/day_13.h"
#include "day_14/day_14.h"
#include "day_15/day_15.h"
#include "day_16/day_16.h"
#include "day_17/day_17.h"
#include "day_18/day_18.h"
#include "day_19/day_19.h"
#include "day_20/day_20.h"
#include "day_21/day_21.h"
#include "day_22/day_22.h"
#include "day_23/day_23.h"
#include "day_24/day_24.h"
#include "day_25/day_25.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[])
{
	// If no arguments were passed, print a message an return
	if (argc == 1)
	{
		std::cout << "No input directory specified!\n";
		return 0;
	}

	// Get input path from argv
	std::string input_path = argv[argc - 1];

	try
	{
		//day_1_part_1(input_path);
		//day_1_part_2(input_path);

		//day_2_part_1(input_path);
		//day_2_part_2(input_path);

		//day_3_part_1(input_path);
		//day_3_part_2(input_path);

		//day_4_part_1(input_path);
		//day_4_part_2(input_path);

		//day_5_part_1(input_path);
		//day_5_part_2(input_path);

		//day_6_part_1(input_path);
		//day_6_part_2(input_path);

		//day_7_part_1(input_path);
		//day_7_part_2(input_path);

		//day_8_part_1(input_path);
		//day_8_part_2(input_path);

		//day_9_part_1(input_path);
		//day_9_part_2(input_path);

		//day_10_part_1(input_path);
		//day_10_part_2(input_path);

		//day_11_part_1(input_path);
		//day_11_part_2(input_path);

		//day_12_part_1(input_path);
		//day_12_part_2(input_path);

		//day_13_part_1(input_path);
		//day_13_part_2(input_path);

		//day_14_part_1(input_path);
		//day_14_part_2(input_path);

		//day_15_part_1(input_path);
		//day_15_part_2(input_path);

		//day_16_part_1(input_path);
		//day_16_part_2(input_path);

		//day_17_part_1(input_path);
		//day_17_part_2(input_path);

		//day_18_part_1(input_path);
		//day_18_part_2(input_path);

		//day_19_part_1(input_path);
		//day_19_part_2(input_path);

		//day_20_part_1(input_path);
		//day_20_part_2(input_path);

		//day_21_part_1(input_path);
		//day_21_part_2(input_path);

		//day_22_part_1(input_path);
		//day_22_part_2(input_path);

		//day_23_part_1(input_path);
		//day_23_part_2(input_path);

		//day_24_part_1(input_path);
		//day_24_part_2(input_path);

		day_25_part_1(input_path);
		day_25_part_2(input_path);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}