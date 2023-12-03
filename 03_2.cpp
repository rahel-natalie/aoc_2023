#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

#include <cctype>


auto relevant(int i, int length, const std::vector<std::vector<char>>& engine_schematic, int row_number)
{	
	struct return_type
	{
		bool relevant;
		int star_id;
	};
	
	const auto& row = engine_schematic[row_number];
	int last_pos = row.size()-1;
	
	if(i-1 >= 0 && row[i-1] == '*') return return_type{true,(row_number*1000)+(i-1)};
	if(i+length <= last_pos && row[i+length] == '*') return return_type{true,(row_number*1000)+(i+length)};
	
	int pos = i==0 ? i : i-1;
	int end = i+length > last_pos ? i+length-1 : i+length;
	for( ; pos <= end; ++pos)
	{		
		if(row_number-1 >= 0)
		{
			const auto& upper_row = engine_schematic[row_number-1];
			if(upper_row[pos] == '*') return return_type{true,((row_number-1)*1000)+pos};
		}
		
		if(row_number+1 < (int)engine_schematic.size())
		{
			const auto& lower_row = engine_schematic[row_number+1];
			if(lower_row[pos] == '*') return return_type{true,((row_number+1)*1000)+pos};
		}
	}	
	return return_type{false,0};
}

auto piece_number_together(unsigned int pos, const std::vector<char>& row)
{
	struct return_type
	{
		unsigned int value{};
		int length{};
	};
	
	unsigned int value = 0;
	int length = 0;
	for( ; isdigit(row[pos]); ++pos)
	{
		value *= 10;
		value += row[pos] - '0';
		++length;
	}
	
	return return_type{value,length};
}

std::unordered_map<int,std::vector<int>> collect_potential_gears(const std::vector<std::vector<char>>& engine_schematic)
{
	std::unordered_map<int,std::vector<int>> star_to_neighbors{};
	
	for(int row_number = 0; row_number < (int)engine_schematic.size(); ++row_number)
	{
		const auto& row = engine_schematic[row_number];
		for(int i=0; i < (int)row.size(); ++i)
		{
			if(isdigit(row[i]))
			{
				auto number_start_pos = i;
				auto number_info = piece_number_together(number_start_pos, row);
				if(const auto& info=relevant(number_start_pos, number_info.length, engine_schematic, row_number); info.relevant)
					star_to_neighbors[info.star_id].push_back(number_info.value);
					
				i += number_info.length-1;
			}	
		}
	}
	return star_to_neighbors;
}


int main()
{
	std::ifstream input{"input_03.txt"};
	std::vector<std::vector<char>> engine_schematic{};

	std::string line{};
	while(std::getline(input, line))
	{
		std::vector<char> row{};
		for(auto character: line)
			row.push_back(character);
		
		engine_schematic.push_back(row);
	}
	
	unsigned int sum = 0;
	const auto potential_gears = collect_potential_gears(engine_schematic);
	for(const auto& [star_id,neighbors]: potential_gears)
	{
		if(neighbors.size()!=2) continue;
		
		sum += neighbors[0] * neighbors[1];
	}
	std::cout << sum << '\n';
	
	return 0;
}
