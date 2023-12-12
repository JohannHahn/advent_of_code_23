#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

enum card {
    J, k2, k3, k4, k5, k6, k7, k8, k9,
    T, Q, K, A, card_max

};
std::unordered_map<char, int> card_ranking = {
    {'A', A}, {'K', K}, {'Q', Q}, {'J', J}, {'T', T},
    {'9', k9}, {'8', k8}, {'7', k7}, {'6', k6}, {'5', k5}, {'4', k4}, {'3', k3}, {'2', k2}
};
struct hand {
    std::string cards;
    int type;
    int bid;
};
std::vector<hand> hands;

enum hand_type {
    high_card, 
    one_pair, 
    two_pair, 
    three_o_kind, 
    full_house,
    four_o_kind,
    five_o_kind,
    type_max
};

int add_js(std::unordered_map<char, int>& map, int type) {
    if(map.find('J') != map.end()) {
	int js = map['J'];
	if(type == high_card) type = one_pair;
	else if (type == one_pair) type = three_o_kind;
	else if (type == two_pair) {
	    if(js == 1) type = full_house;
	    if(js == 2) type = four_o_kind;
	}
	else if (type == three_o_kind) type = four_o_kind;
	else if (type == full_house) type = five_o_kind; 
	else if (type == four_o_kind) type = five_o_kind; 
    }
    return type;
}

size_t pow(size_t a, size_t b) 
{
    size_t power = 1;
    while (b-- > 0) {
	power *= a;
    }
    return power;
}

bool is_digit(char c) 
{
    return c >= '0' && c <= '9';
}

size_t read_number(const std::string& line, size_t cursor) 
{
    size_t number = 0;
    size_t i = cursor;
    size_t start = cursor;
    while(is_digit(line[i])){
		i++;
    };
    size_t power = 0;
    //cursor = i;
    while(i > start) {
		i--;
		number += (line[i] - '0') * pow(10, power++);
    }
    return number;
}


std::string print_hand_type(hand_type type) {
    std::string output = "";
    switch (type) {
	case five_o_kind:
	output = "five of a kind";
	break;
	case four_o_kind:
	output = "four of a kind";
	break;
	case three_o_kind:
	output = "three of a kind";
	break;
	case full_house:
	output = "full house";
	break;
	case two_pair:
	output = "two pair";
	break;
	case one_pair:
	output = "one pair";
	break;
	case high_card:
	output = "high card";
	break;
	default:
	output = "wrong input";
	break;
    }
    return output;
}


hand_type get_hand_type(const std::string& hand) {
    int type = type_max;
    std::unordered_map<char, int> map;
    for(int i = 0; i < hand.length(); ++i) {
	if(map.find(hand[i]) == map.end()) {
	    map[hand[i]] = 1;
	}
	else {
	    map[hand[i]]++;
	}
    }
    assert(map.size() && "konnte keine character aus der hand lesen");
    if(map.size() == 1) type = five_o_kind;
    else if(map.size() == 2) {
	for(std::pair<char, int> p : map) {
	    if(p.second == 1) {
		type = four_o_kind;
	    }
	}
	if(type != four_o_kind) type = full_house;
    }
    else if(map.size() == 3) {
	for(std::pair<char, int> p : map) {
	    if(p.second == 3) {
		type = three_o_kind;
	    }
	}
	if(type != three_o_kind) type = two_pair;
    }
    else if(map.size() == 4) {
	type = one_pair;
    }
    else { 
	type = high_card;
    }
    type = add_js(map, type);
    std::cout << hand << "\n type = " << print_hand_type((hand_type) type) << "\n";
    return (hand_type)type;
}

bool higher_ranked(const hand& hand1, const hand& hand2) {
    bool higher = false;
    if(hand1.type > hand2.type) return true; 
    else if(hand2.type > hand1.type) return false;
    else {
	for(int i = 0; i < hand1.cards.length(); ++i) {
	    if(card_ranking[hand1.cards[i]] == card_ranking[hand2.cards[i]]) continue;
	    else return card_ranking[hand1.cards[i]] > card_ranking[hand2.cards[i]];
	}
    }
    return higher;
}

int main (int argc, char *argv[]) {
    std::fstream file;
    std::string line;
    file.open("input.txt", std::fstream::in);
    while(std::getline(file, line)) {
	int cursor = 0;
	hand hand; 
	hand.cards = line.substr(0, 5);
	hand.bid = read_number(line, 6);
	hand.type = get_hand_type(hand.cards);
	hands.push_back(hand);
    }
    std::sort(hands.begin(), hands.end(), [](hand hand1, hand hand2)
                                  {
				    bool higher = false;
				    if(hand1.type > hand2.type) return true; 
				    else if(hand2.type > hand1.type) return false;
				    else {
					for(int i = 0; i < hand1.cards.length(); ++i) {
					    if(card_ranking[hand1.cards[i]] == card_ranking[hand2.cards[i]]) continue;
					    else return card_ranking[hand1.cards[i]] > card_ranking[hand2.cards[i]];
					}
				    }
				    return higher;
                                  });
    int winnings = 0;
    for(hand hand : hands) {
	std::cout << hand.cards << " bid = " << hand.bid << " type = " << print_hand_type((hand_type)hand.type) << "\n";
    }
    for(int i = 0; i < hands.size(); ++i) {
	winnings += hands[i].bid * (hands.size() - i);
    }
    std::cout << winnings;
    return 0;
}






