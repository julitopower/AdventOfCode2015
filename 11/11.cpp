#include <iostream>
#include <string>
#include <sstream>

const char MIN = 'a';
const char MAX = 'z';

void increment(std::string& input);
bool isValid(const std::string& input);

int main (int argc, char** argv) {
  std::string line;
  std::getline(std::cin, line);

  while(!isValid(line)) {
    increment(line);
  }

  std::cout << line << std::endl;
}

bool isValid(const std::string& input) {
  bool threeConsecutive = false;
  size_t groupsOfTwo = 0;
  char firstGroupChar = '\0';
  for(int i = 0 ; i < input.size() ; ++i) {
    char current = input[i];
    // Forbidden characters
    if(current == 'i' || current == 'o' || current == 'l') {
      return false;
    }

    //At least 2 non-overlapping groups of 2 characters
    if(groupsOfTwo < 2 &&  current != firstGroupChar) {
      if(i < input.size() - 1) {
	if(input[i+1] == current) {
	  ++groupsOfTwo;
	  if(groupsOfTwo == 1) {
	    firstGroupChar = current;
	  }
	}
      } else {
	return false;
      }
    }

    //3 consecutive characters
    if(!threeConsecutive) {
      if(i < input.size() - 2) {
	threeConsecutive = current == input[i+1] - 1 &&
	                   current == input[i+2] - 2;
      } else {
	return false;
      }
    }
  }

  return threeConsecutive && (groupsOfTwo > 1);
}

void increment(std::string& input) {
  for(auto it = input.rbegin() ; it != input.rend() ; ++it) {
    (*it) = *it + 1;;
    if(*it > MAX) { 
      *it = MIN;
      continue;
    }
    break;
  }
}
