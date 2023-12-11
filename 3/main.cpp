#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Pair {
    Pair(int n, int i): number(n), gear_index(i) {};
    int number;
    int gear_index;
};
std::vector<Pair> gear_candidates;
std::string grid;
int sum = 0;
int sum_gear = 0;
int grid_width = 0;
int grid_height = 0;
#define INDEX(x, y) x + y * grid_width 
#define IN_FIELD(x, y) x >= 0 && x < grid_width && y >= 0 && y < grid_height

int pow(int a, int b) 
{
    int power = 1;
    while (b-- > 0) {
	power *= a;
    }
    return power;
}

bool is_digit(char c) 
{
    return c >= '0' && c <= '9';
}

int read_number(int& cursor) 
{
    int number = 0;
    int i = cursor;
    int start = cursor;
    while(is_digit(grid[i])){
	i++;
    };
    int power = 0;
    cursor = i;
    while(i > start) {
	i--;
	number += (grid[i] - '0') * pow(10, power++);
    }
    return number;
}
bool is_symbol(char c) 
{
    return !is_digit(c) && c >= 33 && c < 65 && c != '.';
}

bool evaluate_candidate(int start_x, int start_y, int length, int number)
{
    for(int y = -1; y < 2; ++y) {
	for(int x = -1; x < length + 1; ++x) {
	    int new_x = x + start_x;
	    int new_y = y + start_y;
	    if(IN_FIELD(new_x, new_y) && is_symbol(grid[INDEX(new_x, new_y)])) {
		if(grid[INDEX(new_x,new_y)] == '*') {
		    std::cout << " gear candidate : " << number << " at " << INDEX(new_x, new_y) << "\n";
		    gear_candidates.push_back(Pair(number, INDEX(new_x, new_y)));
		}
		return true; 
	    }
	}
    }
    return false;
}

void do_thing() 
{
    int cursor = 0;
    while(cursor < grid.length()) {
	if(is_digit(grid[cursor])) {
	    int start_index = cursor;
	    int number = read_number(cursor);
	    int length = cursor - start_index;
	    int x = start_index % grid_width;
	    int y = start_index / grid_width;
	    if(evaluate_candidate(x, y, length, number)) {
		sum += number;
	    }
	}
	else {
	    cursor++;
	}
    }
    for(int i = 0; i < gear_candidates.size(); ++i) {
	for(int j = 0; j < gear_candidates.size(); ++j) {
	    if(i != j && gear_candidates[i].gear_index == gear_candidates[j].gear_index) {
		std::cout << "gear found at index = " << gear_candidates[i].gear_index << "\n";
		int gear_ratio = gear_candidates[i].number * gear_candidates[j].number;	
		sum_gear += gear_ratio;
	    }
	} 
    }
    sum_gear /= 2;
}

int main() 
{
    std::string line;
    std::fstream file;
    file.open("input.txt", std::fstream::in);
    while(std::getline(file, line)) {
	grid_height++;
	grid += line;
	grid_width = line.length();
    }
    do_thing();
    std::cout << "sum = " << sum_gear;
    return 0;
}
