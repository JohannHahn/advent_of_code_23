#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

size_t read_number(const std::string& line, size_t& cursor) 
{
    size_t number = 0;
    size_t i = cursor;
    size_t start = cursor;
    while(is_digit(line[i])){
		i++;
    };
    size_t power = 0;
    cursor = i;
    while(i > start) {
		i--;
		number += (line[i] - '0') * pow(10, power++);
    }
    return number;
}

size_t winning(size_t time, size_t best_dist) {
    size_t count = 0;
    for(size_t i = 0; i < time; ++i) {
	if((time - i) * i > best_dist) {
	    count++;
	}
    }
    return count;
}


void trim_spaces(std::string& line) {
    int cursor = 0;
    while(cursor < line.length()) {
	if(line[cursor] == ' ') {
	    line.erase(cursor, 1);
	}
	else {
	    cursor++;
	}
    }
}
int main() {
    std::fstream file;
    std::string line;
    std::vector<size_t> total_time;
    std::vector<size_t> distance;
    file.open("input.txt", std::fstream::in);
    if(!file.is_open()) {
	std::cout << "file not found\n";
	return 1;
    }
    int i = 0;
    while(std::getline(file, line)) {
	trim_spaces(line);
	std::cout << line << "\n";
	size_t cursor = 0;
	while(cursor < line.length()) {
	    if(!is_digit(line[cursor])) {cursor++;}
	    else if(i == 0) {
		total_time.push_back(read_number(line, cursor));
	    }
	    else {
		distance.push_back(read_number(line, cursor));
	    }
	}
	i++;
    }
    size_t result = 1;
    for(i = 0; i < total_time.size(); ++i) {
	std::cout << total_time[i] << " , " << distance[i] << "\n";
	result *= winning(total_time[i], distance[i]);
    }
    std::cout << result;
}





