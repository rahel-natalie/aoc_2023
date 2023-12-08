#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>


struct connected_nodes
{
	std::string left{}, right{};
};


std::unordered_map<std::string,connected_nodes> read_network_from(std::ifstream& input)
{
	std::unordered_map<std::string,connected_nodes> network{};
	
	std::string node, left_node, right_node;
	char skip;
	while(input >> node)
	{
		input >> skip >> skip;
		input >> left_node >> right_node;
		
		left_node.pop_back();
		right_node.pop_back();
		
		network[node] = connected_nodes{left_node, right_node};
	}
	return network;
}

int main()
{
	std::ifstream input{"input_08.txt"};
	std::string instruction{};
	input >> instruction;
	
	std::unordered_map<std::string,connected_nodes> network = read_network_from(input);
	
	
	unsigned int iterations_counter = 0;
	std::string current_pos = "AAA";
	do
	{
		for(auto next_move: instruction)
		{
			if(next_move == 'L')
				current_pos = network[current_pos].left;
			if(next_move == 'R')
				current_pos = network[current_pos].right;	
		}
		++iterations_counter;
	}while(current_pos != "ZZZ");
	
	unsigned int number_of_steps = instruction.size() * iterations_counter;
	std::cout << number_of_steps << '\n';
	
	return 0;
}
