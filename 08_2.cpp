#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>


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

unsigned int steps_to_z(std::string& current_pos, std::unordered_map<std::string,connected_nodes>& network, const std::string& instruction)
{		
	unsigned int iterations_counter = 0;

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
	}while(current_pos.back() != 'Z');
	
	unsigned int number_of_steps = instruction.size() * iterations_counter;
	return number_of_steps;
}

int main()
{
	std::ifstream input{"input_08.txt"};
	std::string instruction{};
	input >> instruction;
	
	std::unordered_map<std::string,connected_nodes> network = read_network_from(input);
	
	
	std::vector<unsigned int> step_collection{};
	for(auto& [node, neighbors]: network)
	{
		if(node.back() == 'A')
		{
			std::string current_node = node;
			step_collection.push_back(steps_to_z(current_node, network, instruction));	
		}
	}
	
	unsigned long lowest_common_multiple = step_collection[0];
	for(unsigned int i=1; i<step_collection.size(); ++i)
		lowest_common_multiple = std::lcm(step_collection[i], lowest_common_multiple);
	
	std::cout << lowest_common_multiple << '\n';
	return 0;
}
