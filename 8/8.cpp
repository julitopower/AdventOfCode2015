#include <iostream>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

int main (int argc, char** argv) {
  std::string line;
  std::getline(std::cin, line);

  size_t total = 0;
  size_t memory = 0;
  while(!cin.eof()) {
    total += line.size();
    for(int i = 0 ; i < line.size() ; ++i) {
      auto& c = line[i];
      if(c == '\"')
	continue;
      if(c == '\\') {
	++i;
	c = line[i];
	if(c == 'x') {
	  i = i + 2;
	}
      }
      ++memory;
    }
    std::getline(std::cin, line);
  }

  std::cout << total << ", " << memory << ", " << (total - memory) << std::endl;
}
