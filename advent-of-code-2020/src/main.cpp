#include <iostream>
#include <stdexcept>

// Forward declare functions for each day
void day_1_part_1();
void day_1_part_2();
void day_2_part_1();
void day_2_part_2();
void day_3_part_1();
void day_3_part_2();

int main()
{
	try
	{
		//day_1_part_1();
		//day_1_part_2();
		//day_2_part_1();
		//day_2_part_2();
		day_3_part_1();
		day_3_part_2();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}