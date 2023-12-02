#include <fstream>
#include <iostream>
#include <sstream>
#include <string>



int main()
{
	std::ifstream input{"input_02.txt"};
	
	unsigned int sum = 0;
	
	std::string line{};
	while(std::getline(input, line))
	{
		std::stringstream linestream(line);
		unsigned int min_needed_red = 0;
		unsigned int min_needed_green = 0;
		unsigned int min_needed_blue = 0;
		
		unsigned int red{}, green{}, blue{};
		
		std::string label{};
		unsigned int game_id{};
		unsigned int val{};
		char nomnom{};
		
		linestream >> label >> game_id >> nomnom;
		while(linestream >> val >> label)
		{
			//when you know your bug but you don't know the solution
			if(label=="red" || label == "red," || label == "red;") red = val;
			if(label=="green" || label == "green," || label == "green;") green = val;
			if(label=="blue" || label == "blue," || label == "blue;") blue = val;
			
			if(label.back()==';' || linestream.eof())
			{
				if(red > min_needed_red) min_needed_red = red;
				if(green > min_needed_green) min_needed_green = green;
				if(blue > min_needed_blue) min_needed_blue = blue;
			}
		}
		unsigned int power = min_needed_red * min_needed_green * min_needed_blue;
		sum += power;
	}	
	std::cout << sum << '\n';
	
	return 0;
}
