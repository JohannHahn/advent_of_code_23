#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <assert.h>

enum State {
    first_line, new_chunk, current_chunk
};

struct Range{
    size_t dst;
    size_t src;
    size_t length;
    bool in_range(size_t from_src) {
	return from_src >= src && from_src < src+length;
    }
    size_t to_dst(size_t from_src) {
	assert(in_range(from_src) && "wrong input");
	return from_src + (dst - src);
    }
};
struct Map {
    std::vector<Range> ranges;
    void print() {
	for(Range r : ranges) {
	    std::cout << "dst = " << r.dst << ", src = " << r.src << ", length = " << r.length << "\n";
	}
    }
    size_t map(size_t n) {
	for(Range r : ranges) {
	    if(r.in_range(n)) {
		return r.to_dst(n);
	    }
	}
	return n;
    }
};
std::vector<Map> maps;
std::vector<size_t> seeds;
State state = first_line;

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

void seed_range(size_t start, size_t length) {
    for(size_t i = start; i < start + length; ++i) {
	seeds.push_back(i);
    }
}

void read_line(const std::string& line) {
    size_t cursor = 0;
    while(cursor < line.length()) {
	if(!is_digit(line[cursor])) {
	    cursor++;
	}
	else if(state == first_line) {
	    seeds.push_back(read_number(line, cursor));
	}
	else if(state == current_chunk) {
	    Range r;
	    r.dst = read_number(line, cursor);
	    cursor++;
	    r.src = read_number(line, cursor);
	    cursor++;
	    r.length = read_number(line, cursor);
	    maps[maps.size() - 1].ranges.push_back(r);
	}
    }
    switch(state) {
	case first_line:
	state = new_chunk;
	maps.push_back(Map());
	break;

	case new_chunk:
	state = current_chunk;
	break;

	case current_chunk:
	if(line.length() == 0) {
	    state = new_chunk;
	    maps.push_back(Map());
	}
	default:
	break;
    }
}

size_t map_to_end(size_t seed) {
    size_t min = 0;
    size_t next = seed;
    for(size_t m = 0; m < maps.size(); ++m) {
	next = maps[m].map(next);
    }
    return next;
}

int main() 
{
    size_t min = SIZE_MAX;
    std::fstream file;
    std::string line;
    file.open("test.txt", std::fstream::in);
    if(!file.is_open()) {
	std::cout << "file not found\n";
	return 1;
    }
    while(std::getline(file, line)) {
	read_line(line);	
    }
    for(size_t i = 0; i < seeds.size(); i+=2) {
	size_t min = SIZE_MAX;
	for(size_t seed = seeds[i]; seed < seeds[i] + seeds[i + 1]; ++seed) {
	    size_t m = map_to_end(seed);
	    if(min > m) {
		min = m;
	    }
	    std::cout << "seed " << i << " done\n";
	}
    }

    return 0;
}
