#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


int main()
{
	unsigned int sum = 0;
	
	std::ifstream input{"input_04.txt"};	
	std::string line{};
	while(std::getline(input, line))
	{
		if(line.empty()) break;
		std::stringstream linestream(line);
		std::string val{}, skip{};
		
		std::array<bool,100> winning{false};
		linestream >> skip >> skip;
		while(linestream >> val)
		{
			if(val == "|") break;
			
			unsigned int number = std::stoi(val);
			winning[number] = true;
		}
		
		int winners_counter = 0;
		while(linestream >> val)
		{
			unsigned int number = std::stoi(val);
			
			if(winning[number]) ++winners_counter;
		}
		
		unsigned int power_of_two = 1;
		for(int i=0; i<winners_counter-1; ++i)
			power_of_two *= 2;
			
		sum += (winners_counter == 0) ? 0 : power_of_two;
	}
	
	std::cout << sum << '\n';
	return 0;
}
