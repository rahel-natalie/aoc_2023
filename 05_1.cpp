#include <fstream>
#include <istream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>


struct triple
{
	long long destination{};
	long long source{};
	long long range{};
};

struct gardening_instruction
{
	std::vector<triple> maps{};
};


std::vector<long long> read_seeds_from(std::ifstream& input)
{
	std::vector<long long> seeds{};
	
	std::string seed_list;
	std::getline(input, seed_list);
		
	std::stringstream seed_list_stream(seed_list);
	std::string skip_title;
	seed_list_stream >> skip_title;
	
	long long seed;
	while(seed_list_stream >> seed)
		seeds.push_back(seed);
		
	return seeds;
}

gardening_instruction read_instruction_list_from(std::ifstream& input)
{	
	std::string skip_title;
	input >> skip_title >> skip_title >> std::ws;
	
	gardening_instruction instruction{};
	
	std::string line;
	while(std::getline(input,line))
	{
		if(line.empty()) break;
		
		std::stringstream linestream(line);
		std::string destination, source, range;
		linestream >> destination >> source >> range;
		
		instruction.maps.push_back({std::stoll(destination), std::stoll(source), std::stoll(range)});
	}	
	return instruction;
}

unsigned int location_number(long long seed, const std::vector<gardening_instruction>& process_chain)
{
	for(const auto& instruction: process_chain)
	{
		for(const auto& [destination, source, range]: instruction.maps)
		{
			const bool seed_number_listed = seed >= source && seed <= source + range-1;
			if(seed_number_listed)
			{
				const auto mapped_value = seed + (destination - source);
				seed = mapped_value;
				
				break;
			}
		}
	}
	return seed;
}

int main()
{	
	std::ifstream input{"input_05.txt"};
	const auto seeds = read_seeds_from(input);


	std::vector<gardening_instruction> process_chain{};
	
	constexpr unsigned int number_of_maps = 7;
	for(unsigned int i=0; i<number_of_maps; ++i)
		process_chain.push_back(read_instruction_list_from(input));

	
	unsigned int lowest_location_number = std::numeric_limits<unsigned int>::max();
	for(const auto& seed: seeds)
	{
		if(const unsigned int current_location_number = location_number(seed, process_chain); current_location_number < lowest_location_number)
			lowest_location_number = current_location_number;
	}
	
	std::cout << lowest_location_number << '\n';
	return 0;
}
