#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

struct Node {
    Node() { left = ""; right = "";}
    Node(std::string l, std::string r) : left(l), right(r) {};
    std::string left;
    std::string right;
};
std::string path;
std::unordered_map<std::string, Node> map;
std::vector<std::string> starting_nodes;

size_t steps() {
    std::vector<std::string> next = starting_nodes;
    std::vector<size_t> counts;
    for(int i = 0; i < next.size(); ++i) counts.push_back(0);

    for(int i = 0; i < next.size(); ++i) {
	while(next[i][2] != 'Z') {
	    if(path[counts[i] % path.size()] == 'R') next[i] = map[next[i]].right;
	    else next[i] = map[next[i]].left;
	    counts[i]++;
	}
    }
    size_t count = 1; 
    for(size_t c : counts) {
	std::cout << "count = " << c << "\n";
    }
    return count;
}

int main() {
    std::string line;
    std::fstream file;
    file.open("input.txt", std::fstream::in);
    int i = 0;
    while(std::getline(file, line)) {
	if(i == 0) path = line;
	else if (line.size()) {
	    std::string name = line.substr(0, 3);
	    if(name[2] == 'A') starting_nodes.push_back(name);
	    map[name] = Node(line.substr(7, 3), line.substr(12, 3));
	}
	i++;
    }
    std::cout << steps();
}
