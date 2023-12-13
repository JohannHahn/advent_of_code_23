#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::vector<int> numbers;

int pow(size_t a, size_t b) 
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
    bool negative = (cursor > 0 && line[cursor - 1] == '-');
    while(is_digit(line[i])){
		i++;
    };
    int power = 0;
    cursor = i;
    while(i > start) {
		i--;
		number += (line[i] - '0') * pow(10, power++);
    }
    if(negative) number *= -1;
    return number;
}

void handle_line(const std::string& line) {
    int cursor = 0;
    while(cursor < line.size()) {
	if(!is_digit(line[cursor])) cursor++; 
	else {
	    numbers.push_back(read_number(line, cursor));
	}
    }
}

int next_number() {
    std::vector<int> next_line;
    int next = numbers[numbers.size() - 1];
    bool not_zeroes = true;

    do {

	for(int i = 1; i < numbers.size(); ++i) {	
	    next_line.push_back(numbers[i] - numbers[i-1]);
	}

	not_zeroes = false;
	next += next_line[next_line.size() - 1];
	for(int n : next_line) {
	    if(n != 0) {
		not_zeroes = true;
		break;
	    }
	}
	numbers = next_line;
	next_line.clear();
    } while(not_zeroes);

    std::cout << "next num = " << next << "\n";
    return next;
}
int prev_number() {
    std::vector<int> next_line;
    std::vector<int> firsts = {numbers[0]};
    bool not_zeroes = true;
    int prev = 0;
    do {

	for(int i = 1; i < numbers.size(); ++i) {	
	    next_line.push_back(numbers[i] - numbers[i-1]);
	}

	not_zeroes = false;
	firsts.push_back(next_line[0]);
	for(int n : next_line) {
	    std::cout << n << " ";
	    if(n != 0) {
		not_zeroes = true;
		//break;
	    }
	}
	std::cout << "\n";
	numbers = next_line;
	next_line.clear();
    } while(not_zeroes);
    for(int i = firsts.size() - 2; i >= 0; i--) {
	std::cout << "first = " << firsts[i] << "\n";
	prev = firsts[i] - prev;
	std::cout << "prev = " << prev << "\n";
    }

    return prev;
}

int main() {
    std::string line;
    std::fstream file;
    file.open("input.txt", std::fstream::in);
    int sum = 0;
    while(std::getline(file, line)) {
	handle_line(line);
	std::cout << "line =	       " << line << "\n";
	std::cout << "read numbers : ";
	for(int n : numbers) std::cout << n << " ";
	std::cout << "\n";
	int n = prev_number();
	std::cout << "prev num = " << n << "\n";
	numbers.clear();
	sum += n;
    }
    std::cout << sum;
}


