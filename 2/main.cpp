#include <iostream>
#include <fstream>
#include <string>

int red_max = 0;
int green_max = 0;
int blue_max = 0;
int id_start = 5;

enum colors {
    red, green, blue
};
int maximas[3] = {red_max, green_max, blue_max};

int pow(int a, int b) 
{
    int result = 1;
    for(int i = 0; i < b; ++i) {
	result *= a;
    }
    return result;
}
bool is_digit(char c) 
{
    return c >= '0' && c <= '9';
}
bool irrelevant(char c) 
{
    return c == ',' || c == ' ' || c == ':' || c == ';';
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
int read_color(const std::string& line, int& cursor) 
{
    int color = -1;
    char c = line[cursor];
    switch (c) {
	case 'r':
	    color = red;
	    cursor += 3;
	    break;
	case 'g':
	    color = green;
	    cursor += 5;
	    break;
	case 'b':
	    color = blue;
	    cursor += 4;
	    break;
	default:
	    std::cout << "wrong input in read color!\n";
	    break;
    }
    return color;
}
int eval_line(const std::string& line) 
{
    int id = 0;
    int i = id_start;
    while(line[i] != ':') {
	i++;
    }
    int power = 0;
    int cursor = i;
    while(i > id_start) {
	i--;
	id += (line[i] - '0') * pow(10, power++);
    }
    int last_num = 0;
    while(cursor < line.length()) {
	char current = line[cursor];
	if(irrelevant(current)) {
	    cursor++;
	}
	else if(is_digit(current)) {
	    last_num = read_number(line, cursor);
	}
	else {
	    int color = read_color(line, cursor); 
	    if(last_num > maximas[color]) {
		maximas[color] = last_num;
	    }
	}
    }
    return id;
}

int main()
{
    std::string line;
    std::fstream file;
    file.open("input.txt", std::fstream::in);
    int cursor = 5;
    //std::cout << read_number(line, cursor) << "\n";
    //std::cout << "cursor = " << cursor << "\n";
    int sum = 0;
    std::cout << "------------------------\n";
    while(file.is_open() && std::getline(file, line)) { 
	eval_line(line);
	int power = maximas[red] * maximas[green] * maximas[blue];
	sum += power;
	std::cout << "red max = " << maximas[red] << "\ngreen max = " << maximas[green] << "\nblue max = " << maximas[blue] << "\n";
	std::cout << "power = " << power << "\n";
	std::cout << "--------\n";
	maximas[red] = 0;
	maximas[green] = 0;
	maximas[blue] = 0;
    }
    std::cout << "sum = " << sum << "\n";
    std::cout << "------------------------\n";
    return 0;
}
