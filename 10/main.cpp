#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <assert.h>

std::string grid;
std::string path;
std::string inside_points;
int width = 0;
int height = 0;
int max_dist = 0;

#define INDEX(x, y) (x + y*width)
#define GRID_AT(x, y) grid[INDEX(x,y)]
#define IN_GRID(x, y) (x >= 0 && x < width && y >= 0 && y < height)

enum direction {
    north, east, south, west, direction_max
};

#define OPPOSITE(dir) ((dir + 2) % direction_max) 


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

std::string print_dir(int dir) {
    std::string out = "no dir found";
    if(dir == north) out = "north";
    else if(dir == west) out = "west";
    else if(dir == east) out = "east";
    else if(dir == south) out = "south";
    return out;
}

int get_dir(char pipe, int dir_in) {
    int dir_out = -1;
    if(pipe == 'F') dir_out = (dir_in == south ? east : south);
    else if(pipe == 'L') dir_out = dir_in == north ? east : north;
    else if(pipe == 'J') dir_out = dir_in == north ? west: north;
    else if(pipe == '|') dir_out = dir_in == north ? south: north;
    else if(pipe == '7') dir_out = dir_in == south ? west: south;
    else if(pipe == '-') dir_out = dir_in == west? east: west;
    if(dir_out == -1) std::cout << "not a pipe! \n";
    return dir_out;
}
bool connected(int dir, char pipe) {
    bool result = false;
    if(dir == north) {
	result = pipe == '7' || pipe == '|' || pipe == 'F';
    }
    else if(dir == south) {
	result = pipe == 'L' || pipe == '|' || pipe == 'J';
    }
    else if(dir == west) {
	result = pipe == 'F' || pipe == '-' || pipe == 'L';
    }
    else if(dir == east) {
	result = pipe == '7' || pipe == '-' || pipe == 'J';
    }
    return result;
}

void next_coords(int dir, int&x, int& y) {
	if(dir == north) y -= 1;
	else if(dir == south) y += 1;
	else if(dir == west) x -= 1;
	else if(dir == east) x += 1;
}

void find_dirs(int x, int y, int& dir1, int& dir2) {
    int count = 0;
    for(int dir = 0; dir < direction_max; ++dir) {
	int x_n = x;
	int y_n = y;
	next_coords(dir, x_n, y_n);
	if(IN_GRID(x_n, y_n)) {
	    char c = GRID_AT(x_n, y_n);
	    if(connected(dir, c)) {
		if(count == 0) {
		    dir1 = dir;
		    //std::cout << "found dir in find_dirs " << print_dir(dir1) << "\n";
		    count++;
		}
		else {
		    dir2 = dir;
		    //std::cout << "found secons dir " << print_dir(dir2) << "\n";
		    return;
		}
	    }
	}
    }
}


void walk(int x, int y, int prev_dist, int dir_in) {
    //std::cout << "walking in from direction " << print_dir(dir_in) << "\n";
    char current = GRID_AT(x, y);
    //std::cout << "into tile " << current << "\n";
    //std::cout << "at coordinates x, y =  " << x << ", " << y << "\n";
    int dir_out = -1;
    if(current == 'S' && prev_dist > 0) {
	return;
    } 
    else if(current == 'S') {
	path[INDEX(x, y)] = '.';
	int dir1;
	int dir2;
	find_dirs(x, y, dir1, dir2); 
	int x1 = x; int y1 = y;
	next_coords(dir1, x1, y1);
	walk(x1, y1, prev_dist+1, OPPOSITE(dir1));
    } 
    else {
	max_dist++;
	path[INDEX(x,y)] = '.';
	int x_n = x;
	int y_n = y;
	dir_out = get_dir(current, dir_in);
	next_coords(dir_out, x_n, y_n);
	walk(x_n, y_n, prev_dist+1, OPPOSITE(dir_out));
    }
}

int count_intersections(int x, int y, int dir) {
    int inter = 0;
    next_coords(dir, x, y);
    while(IN_GRID(x, y)) {
	if(path[INDEX(x, y)] != '_') {
	    inter++;
	}
	next_coords(dir, x, y);
    }
    return inter;
}


bool inside(int x, int y) {
    bool result = false;
    if(path[INDEX(x,y)] != '_') result = false;
    else {
	int inter[direction_max] = {0};
	for(int dir = 0; dir < direction_max; ++dir) {
	    inter[dir] = count_intersections(x, y, dir);
	    if(inter[dir] == 0) return false;
	}
	result = true;
	std::cout << x << ", " << y << ": ";
	for(int i = 0; i < direction_max; ++i) {
	    std::cout << print_dir(i) << ": " << inter[i] << " ";
	    if(inter[i] % 2 == 0) {
		result = false;
		//break;
	    }
	}
	std::cout << "\n";
    }
    return result;
}
void print_grid(const std::string& g) {
    std::cout << "----------------------\n";
    for(int y = 0; y < height; ++y) {
	for(int x = 0; x < width; ++x) {
	    std::cout << g[INDEX(x,y)] << " ";
	}
	std::cout << "\n";
    }
    std::cout << "----------------------\n";
}
int main() {
    std::string line;
    std::fstream file;
    file.open("test4.txt", std::fstream::in);
    while(std::getline(file, line)) {
	grid += line;
	width = line.size();
	height++;
	for(int i = 0; i < line.size(); ++i) path += "_";
	for(int i = 0; i < line.size(); ++i) inside_points += "0";
    }
    for(int y = 0; y < height; ++y) {
	for(int x = 0; x < width; ++x) {
	    if(GRID_AT(x, y) == 'S') {
		walk(x, y, 0, -1);
		break;
	    }
	}
    }
    int outside_count = 0;
    for(int y = 0; y < height; ++y) {
	for(int x = 0; x < width; ++x) {
	    if(inside(x, y)) {
		inside_points[INDEX(x,y)] = 'I';
		outside_count++;
	    }
	}
    }
    print_grid(grid);
    print_grid(path);
    print_grid(inside_points);
    std::cout << outside_count;
    //std::cout << (max_dist / 2 + 1);
}
