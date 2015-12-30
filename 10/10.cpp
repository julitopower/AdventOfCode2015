#include <iostream>
#include <string>
#include <sstream>

std::string read(const std::string& input);

int main (int argc, char** argv) {
  std::string line;
  std::getline(std::cin, line);

  for(int i = 0 ; i < 40 ; ++i) {
    line = read(line);
  }
  std::cout << line.size() << std::endl;
}

std::string read(const std::string& input) {
  std::stringstream ss;
  char current = '\0';
  size_t currentCount = 0;
  for(auto& c : input) {
    if(c != current) {
      if(current != '\0') {
	ss << currentCount << current;
      }
      currentCount = 1;
      current = c;
    } else {
      ++currentCount;
    }
  }

  if(current != '\0') {
    ss << currentCount << current;
  }
  
  return ss.str();
}
