#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


int main()
{
	constexpr unsigned int number_of_cards = 213;
	std::array<int,number_of_cards> copies{};
	
	std::ifstream input{"input_04.txt"};	
	std::string line{};
	while(std::getline(input, line))
	{
		if(line.empty()) break;
		std::stringstream linestream(line);
		std::string val{}, skip{};
		
		std::array<bool,100> winning{false};
		linestream >> skip >> val;
		
		val.pop_back();
		unsigned int card_number = std::stoi(val);
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
		
		
		++copies[card_number];
		unsigned int affected_card_number = card_number;
		for(int i=0; i<winners_counter; ++i)
		{
			++affected_card_number;
			copies[affected_card_number] += copies[card_number];
		}
	}
	
	unsigned int sum = 0;
	for(auto card_entry: copies)
		sum += card_entry;
		
	std::cout << sum << '\n';
	return 0;
}
