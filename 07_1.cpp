#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>


enum class card_type
{
	high_kind = 0,
	one_pair,
	two_pair,
	three_kind,
	full_house,
	four_kind, 
	five_kind
};

struct camel_card
{
	std::string hand{};
	int bid{};
};


card_type type_of(const std::string& hand)
{
	std::map<char, int> label_occurrences{};
	
	for(char c: hand)
		++label_occurrences[c];
	
	
	bool saw_pair = false;
	bool saw_three = false;
	for(const auto& [label, occurrences]: label_occurrences)
	{
		if(occurrences == 5) return card_type::five_kind;
		if(occurrences == 4) return card_type::four_kind;
		
		if(occurrences == 3 && saw_pair) return card_type::full_house;
		if(occurrences == 3 && !saw_pair) saw_three = true;
		
		if(occurrences == 2 && saw_three) return card_type::full_house;
		if(occurrences == 2 && saw_pair) return card_type::two_pair;
		if(occurrences == 2 && !saw_pair) saw_pair = true;
	}
	if(saw_three) return card_type::three_kind;
	if(saw_pair) return card_type::one_pair;
	
	return card_type::high_kind;
}

void sort_ascendingly_by_rank(std::vector<camel_card>& cards)
{
	auto comparison = [](const camel_card& lhs, const camel_card& rhs)
	{
		std::vector<char> card_labels{'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
		
		for(unsigned int i=0; i<lhs.hand.size(); ++i)
		{
			auto lhs_label = lhs.hand[i];
			auto rhs_label = rhs.hand[i];
			
			auto lhs_pos = std::find(card_labels.begin(), card_labels.end(), lhs_label);
			auto rhs_pos = std::find(card_labels.begin(), card_labels.end(), rhs_label);
			
			if(lhs_pos < rhs_pos) return true;
			if(lhs_pos > rhs_pos) return false;
		}		
		return false;
	};
	
	std::sort(cards.begin(), cards.end(), comparison);
}

int main()
{
	std::map<card_type, std::vector<camel_card>> collection_per_type{};
	
	std::ifstream input{"input_07.txt"};
	std::string hand, bid;
	while(input >> hand >> bid)
	{
		camel_card card = {hand, std::stoi(bid)};
		collection_per_type[type_of(hand)].push_back(card);
	}
	
	for(auto& [type, collection]: collection_per_type)
		sort_ascendingly_by_rank(collection);
	
	
	unsigned long sum = 0;
	unsigned long rank = 1;	
	for(const auto& [type, collection]: collection_per_type)
	{
		for(const auto& card: collection)
		{
			auto product = card.bid * rank;
			sum += product;
			++rank;
		}
	}
	std::cout << sum << '\n';
	return 0;
}
