#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


std::vector<long> build_pyramid_base(const std::string& line)
{
	std::vector<long> history{};
	
	std::stringstream linestream(line);
	long val;
	while(linestream >> val)
		history.push_back(val);
	
	return history;
}

std::vector<long> predict_next_sequence(const std::vector<long>& predecessor)
{
	std::vector<long> prediction(predecessor.size() - 1);
	
	for(std::size_t i=0; i<prediction.size(); ++i)
		prediction[i] = predecessor[i+1] - predecessor[i];
	
	return prediction;
}

bool not_all_zeros(const std::vector<long>& line)
{
	if(std::find_if_not(line.begin(), line.end(), [](long val){ return val == 0; }) != line.end())
		return true;
	
	return false;
}

long extrapolate_value(const std::vector<std::vector<long>>& downwards_pyramid)
{
	long extrapolated_value = 0;
	
	for(const auto& line: downwards_pyramid)
	{
		if(line.size() == 0) break;
		extrapolated_value += line.back();
	}
		
	return extrapolated_value;
}

int main()
{
	long sum = 0;
	
	std::ifstream input{"input_09.txt"};
	std::string line;
	while(std::getline(input,line))
	{
		std::vector<std::vector<long>> downwards_pyramid{build_pyramid_base(line)};
		
		do
		{
			auto next_line = predict_next_sequence(downwards_pyramid.back());
			downwards_pyramid.push_back(next_line);
		}while(not_all_zeros(downwards_pyramid.back()));

		sum += extrapolate_value(downwards_pyramid);
	}
	
	std::cout << sum << '\n';
	return 0;
}
