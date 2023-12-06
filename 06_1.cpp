#include <array>
#include <fstream>
#include <iostream>
#include <string>


unsigned int number_of_ways_to_win(unsigned int race_time, unsigned int record_time)
{
	unsigned int sum = 0;
	
	for(unsigned int i=1; i<race_time; ++i)
		if(i*(race_time-i) > record_time)
			++sum;
	
	return sum;
}

int main()
{	
	std::array<int,4> race_times{};
	std::array<int,4> record_times{};
	
	std::ifstream input{"input_06.txt"};
	std::string skip;
	input >> skip;
	input >> race_times[0] >> race_times[1] >> race_times[2] >> race_times[3];

	input >> skip;
	input >> record_times[0] >> record_times[1] >> record_times[2] >> record_times[3];
	
	
	unsigned int total_number_of_ways_to_win = 1;
	for(unsigned int i=0; i<race_times.size(); ++i)
		total_number_of_ways_to_win *= number_of_ways_to_win(race_times[i], record_times[i]);
	
	std::cout << total_number_of_ways_to_win << '\n';
	return 0;
}
