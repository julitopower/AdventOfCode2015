#include <iostream>
#include <string>
#include <ctype.h>

int count(const std::string& input);

int main (int argc, char** argv) {
  std::string line;
  std::getline(std::cin, line);

  int accum = 0;
  while(!std::cin.eof()) {
    accum += count(line);
    std::cout << accum << std::endl;
    std::getline(std::cin, line);
  }

  std::cout << accum << std::endl;
}

int count(const std::string& input) {
  bool inString = false;
  bool inNumber = false;

  std::string currentValue = "";
  int accum = 0;
  for(auto it = input.begin() ; it != input.end() ; ++it) {
    //Let's see if the current character is numeric
    if(isdigit(*it) || *it == '-') {
      if(!inNumber) {
	inNumber = true;
	currentValue = "";
      }
      currentValue += *it;
    } else if(inNumber) {
      inNumber = false;
      accum += stoi(currentValue);
    }
  }
  if(inNumber) {
    accum += stoi(currentValue);
  }
  return accum;
}
