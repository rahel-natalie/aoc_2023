#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <cctype>


int main()
{
	std::ifstream input{"input_01.txt"};
	
	
	unsigned int sum = 0;
	
	std::string line{};
	while(std::getline(input,line))
	{
		int first = 0;
		int second = 0;
		
		bool first_set = false;
		bool second_set = false;
		
		for(char c: line)
		{
			if(std::isdigit(c))
			{
				if(!first_set)
				{
					first = c - '0';
					first_set = true;
				}
				else
				{
					second = c - '0';
					second_set = true;
				}
			}	
		}
		
		int num{};
		if(second_set)
			num = (first * 10) + second;
		else
			num = (first * 10) + first;
		
		sum += num;
	}
	
	std::cout << sum << '\n';
	
	return 0;
}
