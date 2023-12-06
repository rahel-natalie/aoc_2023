#include <array>
#include <fstream>
#include <iostream>
#include <string>


unsigned int number_of_ways_to_win(unsigned long race_time, unsigned long record_time)
{
	unsigned int sum = 0;
	
	for(unsigned int i=1; i<race_time; ++i)
		if(i*(race_time-i) > record_time)
			++sum;
	
	return sum;
}

int main()
{		
	std::ifstream input{"input_06.txt"};
	std::string skip;
	input >> skip;
	
	std::string part_1, part_2, part_3, part_4;
	input >> part_1 >> part_2 >> part_3 >> part_4;
	std::string race_info = part_1 + part_2 + part_3 + part_4;
	auto race_time = std::stol(race_info);

	input >> skip;
	input >> part_1 >> part_2 >> part_3 >> part_4;
	std::string record_info = part_1 + part_2 + part_3 + part_4;
	auto record_time = std::stol(record_info);
	
	std::cout << number_of_ways_to_win(race_time, record_time) << '\n';
	return 0;
}
