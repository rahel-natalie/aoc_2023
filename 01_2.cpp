#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <cctype>


int main()
{
	std::ifstream input{"input_01.txt"};
	
	std::map<std::string, unsigned int> number_name_to_value{};
	number_name_to_value["zero"] = 0;
	number_name_to_value["one"] = 1;
	number_name_to_value["two"] = 2;
	number_name_to_value["three"] = 3;
	number_name_to_value["four"] = 4;
	number_name_to_value["five"] = 5;
	number_name_to_value["six"] = 6;
	number_name_to_value["seven"] = 7;
	number_name_to_value["eight"] = 8;
	number_name_to_value["nine"] = 9;
	
	
	unsigned int sum = 0;
	
	std::string line{};
	while(std::getline(input,line))
	{
		int first{};
		int second{};
		
		std::size_t smol_pos = line.size() - 1;
		std::size_t biggy_pos = 0;
		for(const auto& [name,value]: number_name_to_value)
		{
			if(std::size_t pos = line.find(name); pos != std::string::npos)
			{
				if(pos <= smol_pos)
				{
					smol_pos = pos;
					first = value;
				}
				if(pos >= biggy_pos)
				{
					biggy_pos = pos;
					second = value;
				}
			}
				
			if(std::size_t pos = line.rfind(name); pos != std::string::npos)
			{
				if(pos <= smol_pos)
				{
					smol_pos = pos;
					first = value;
				}
				if(pos >= biggy_pos)
				{
					biggy_pos = pos;
					second = value;
				}
			}	
		}
		
		for(unsigned int i=0; i<line.size(); ++i)
		{
			char c = line[i];
			
			if(std::isdigit(c))
			{
				if(i <= smol_pos)
				{
					smol_pos = i;
					first = c - '0';
				}
				if(i >= biggy_pos)
				{
					biggy_pos = i;
					second = c - '0';
				}
			}	
		}
		
		int	num = (first * 10) + second;
		
		sum += num;
	}
	
	std::cout << sum << '\n';
	
	return 0;
}
