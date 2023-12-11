#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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
enum cards{
    k2, k3, k4, k5, k6, k7, k8, k9,
    T, J, Q, K, A

};
bool check_type(const char* hand, int type) { 
    int length = strlen(hand);
    if(type == high_card) {
	for(int i = 0; i < length; ++i) {
	    if(i > 0) {
		if(hand[i - 1] != hand[i]) return false;
	    }
	}
    }
    else if(type == one_pair) {
	bool pair_found = false;
	for(int i = 0; i < length; ++i) {
	    for(int j = i + 1; j < length; ++j) {
		if(!pair_found && hand[i] == hand[j]) {
		    pair_found = true;
		}
		else if(pair_found && hand[i] == hand[j]) {
		    return false;
		}
	    }
	}
    }
    else if(type == two_pair) {
	int first_pair = 0;
	int second_pair = 0;
	for(int i = 0; i < length; ++i) {
	    for(int j = i + 1; j < length; ++j) {
		if(!first_pair && hand[i] == hand[j]) {
		    first_pair= hand[i];
		}
		else if(!second_pair && first_pair && hand[i] == hand[j] && hand[i] != first_pair) {
		    second_pair = hand[i];
		    return false;
		}
	    }
	}
    }
    return true;
}
int longest_run(const char* hand) {
    int run = 0;
    int i = 0;
    while(hand++) {
	if(i > 0 && hand[i - 1] == hand[i]) {
	    
	}
    }
    return run;
}

int get_hand_type(const char* hand) {
    int type = -1;
    std::vector<bool> possible_types = {true};
    char last = 0;
    int i = 0;
    int same_label = 0;
    while(hand++) {
	if(i > 0) {
	    if(last != hand[i]) {
		possible_types[four_o_kind] = false;
	    }
	    else {
		same_label++;
	    }
	}
	i++;
	last = hand[i];
    }
    return type;
}
int main (int argc, char *argv[]) {
    return 0;
}
