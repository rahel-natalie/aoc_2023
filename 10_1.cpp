#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>


struct point
{
	unsigned int x, y;
};

struct node
{
	point id{};
	std::vector<node> neighbors{};
};


bool operator==(const point& lhs, const point& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
	
auto read_input()
{
	struct return_type
	{
		std::vector<std::vector<char>> field{};
		node start{};
	};
	
	
	std::vector<std::vector<char>> field{};
	node start{};
	
	std::ifstream input{"input_10.txt"};
	std::string line;
	for(std::size_t y=0; std::getline(input,line); ++y)
	{
		std::vector<char> row{};
		
		std::stringstream linestream(line);
		char tile_info;
		for(std::size_t x=0; linestream >> tile_info; ++x)
		{
			row.push_back(tile_info);
			
			if(tile_info == 'S')
			{
				start.id.x = x;
				start.id.y = y;
			}
		}
		field.push_back(row);
	}
	return return_type{field, start};
}

bool right_neighbor_reachable(const node& pos, const std::vector<std::vector<char>>& field)
{
	const auto width = field[0].size();
	bool exists = pos.id.x + 1 < width;
	
	if(!exists) return false;
	
	auto node_val = field[pos.id.y][pos.id.x + 1];
	bool relevant = node_val != '.';
	bool connected = (node_val == '-') || (node_val == 'J') || (node_val == '7') || (node_val == 'S');
	
	return relevant && connected;
}

bool left_neighbor_reachable(const node& pos, const std::vector<std::vector<char>>& field)
{
	bool exists = pos.id.x > 0;
	
	if(!exists) return false;
	
	auto node_val = field[pos.id.y][pos.id.x - 1];
	bool relevant = node_val != '.';
	bool connected = (node_val == '-') || (node_val == 'F') || (node_val == 'L') || (node_val == 'S');
	
	return relevant && connected;
}

bool bottom_neighbor_reachable(const node& pos, const std::vector<std::vector<char>>& field)
{
	const auto height = field.size();
	bool exists = pos.id.y + 1 < height;
	
	if(!exists) return false;
	
	auto node_val = field[pos.id.y + 1][pos.id.x];
	bool relevant = node_val != '.';
	bool connected = (node_val == '|') || (node_val == 'J') || (node_val == 'L') || (node_val == 'S');
	
	return relevant && connected;
}

bool top_neighbor_reachable(const node& pos, const std::vector<std::vector<char>>& field)
{
	bool exists = pos.id.y > 0;
	
	if(!exists) return false;
	
	auto node_val = field[pos.id.y - 1][pos.id.x];
	bool relevant = node_val != '.';
	bool connected = (node_val == '|') || (node_val == 'F') || (node_val == '7') || (node_val == 'S');
	
	return relevant && connected;
}

void collect_neighbors(node& pos, const std::vector<std::vector<char>>& field, char kind_of_pipe)
{
	switch(kind_of_pipe)
	{
		case '-':
		{
			if(right_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x + 1, pos.id.y}, {}});
			if(left_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x - 1, pos.id.y},{}});	
			break;
		}
		case '|':
		{
			if(bottom_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x, pos.id.y + 1},{}});
			if(top_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x, pos.id.y - 1},{}});	
			break;
		}
		case 'L':
		{
			if(right_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x + 1, pos.id.y}, {}});		
			if(top_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x, pos.id.y - 1},{}});	
			break;
		}
		case 'J':
		{
			if(left_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x - 1, pos.id.y},{}});			
			if(top_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x, pos.id.y - 1},{}});		
			break;
		}
		case '7':
		{
			if(left_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x - 1, pos.id.y},{}});	
			if(bottom_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x, pos.id.y + 1},{}});			
			break;
		}
		case 'F':
		{
			if(right_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x + 1, pos.id.y}, {}});			
			if(bottom_neighbor_reachable(pos, field))
				pos.neighbors.push_back({{pos.id.x, pos.id.y + 1},{}});
			break;
		}
	}
}

std::optional<unsigned int> path_length(node& pos, const node& previous, const node& start, const std::vector<std::vector<char>>& field)
{
	if(pos.id == start.id) 
		return 0;
	
	char pipe = field[pos.id.y][pos.id.x];
	collect_neighbors(pos, field, pipe);
	
	node next_neighbor{};
	for(auto& neighbor: pos.neighbors)
	{
		if(neighbor.id == previous.id)
			continue;
		next_neighbor = neighbor;
	}
	
	auto result = path_length(next_neighbor, pos, start, field);
	if(result)
		return 1 + result.value();
	return std::nullopt;
}

int main()
{
	auto [field, start] = read_input();
	
	for(char pipe: {'-','|','L','J','7','F'})
		collect_neighbors(start, field, pipe);
	
	for(auto& neighbor: start.neighbors)
	{
		auto current_path_length = path_length(neighbor, start, start, field);
		if(current_path_length != std::nullopt)
		{
			auto farthest_point_in_steps = (current_path_length.value() + 1) / 2;
			std::cout << farthest_point_in_steps << '\n';
			
			break;
		}
	}
	
	return 0;
}
