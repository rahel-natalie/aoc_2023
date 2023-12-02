#include <fstream>
#include <iostream>
#include <sstream>
#include <string>



bool possible(unsigned int red, unsigned int green, unsigned int blue)
{
	constexpr unsigned int max_red = 12;
	constexpr unsigned int max_green = 13;
	constexpr unsigned int max_blue = 14;
	
	return (red <= max_red) && (green <= max_green) && (blue <= max_blue);
}

int main()
{
	std::ifstream input{"input_02.txt"};
	
	unsigned int sum = 0;
	
	std::string line{};
	while(std::getline(input, line))
	{
		std::stringstream linestream(line);
		unsigned int red{}, green{}, blue{};
		
		bool no_cheaty_games = true;
		
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
				if(!possible(red, green, blue))
					no_cheaty_games = false;
				
				red = green = blue = 0;
			}
		}
		if(no_cheaty_games)
			sum += game_id;
	}	
	std::cout << sum << '\n';
	
	return 0;
}
