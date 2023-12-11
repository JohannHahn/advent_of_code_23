#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> winning_numbers;
std::vector<int> your_numbers;

struct Lines {
    std::string line;
    int count;
    Lines* next;
};
typedef std::vector<Lines> LineList;
Lines lines;

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

int read_number(const std::string& line, int& cursor) 
{
    int number = 0;
    int i = cursor;
    int start = cursor;
    while(is_digit(line[i])){
	i++;
    };
    int power = 0;
    cursor = i;
    while(i > start) {
	i--;
	number += (line[i] - '0') * pow(10, power++);
    }
    return number;
}
bool find(int n) 
{
    for(int m : winning_numbers) {
	if(n == m) return true;
    }
    return false;
}
int read_line(const std::string& line) 
{
    int result = 0;
    int cursor = 0;
    bool first_half = true;
    int matches = 0;
    while(line[cursor++] != ':') {};
    while(cursor < line.length()) {
	if(is_digit(line[cursor])) {
	    int number = read_number(line, cursor);
	    if(first_half) {
		winning_numbers.push_back(number);
	    }
	    else {
		your_numbers.push_back(number);
	    }
	}
	else {
	    if(line[cursor] == '|') {
		first_half = false;
	    }
	    cursor++;
	}
    }
    for(int n : your_numbers) {
	if(find(n)) {
	    matches++;
	}
    }
    winning_numbers.clear();
    your_numbers.clear();
    return matches;
}
// lese die ganze datei ein in ein line array
// gehe durch die lines
// kopiere bei n matches -> n lines unter der aktuellen 

int main() 
{
    int sum = 0;
    std::string line;	
    std::fstream file;
    file.open("input.txt");
    Lines* current = &lines;
    while(getline(file, line)) {
	current->line = line;
	current->count = 1;
	current->next = new Lines();
	current = current->next;
    }
    current = &lines;
    while(current->next) {
	int matches = read_line(current->line);
	Lines* next = current->next;
	for(int i = 0; i < matches; ++i) {
	    if(next) {
		next->count += current->count;
		next = next->next;
	    }
	}
	current = current->next;
    }
    current = &lines;
    while(current->next) {
	sum+= current->count;
	current = current->next;
    }
    std::cout << sum;
    return 0;
}
