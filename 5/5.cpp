#include <iostream>
#include <string>

const char A = 0x1;
const char E = 0x2;
const char I = 0x4;
const char O = 0x8;
const char U = 0x10;

bool has_3_vowels(const char input) {
  size_t counter = 0;
  for(int i = 0 ; i < 5 ; ++i) {
    counter += (0x1 & (input >> i));
  }
  return counter >= 3;
}

bool is_vowel(const char input) {
      switch(input) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
	return true;
      }
      return false;
}

int main(int argc, char** argv) {
  std::string line;
  std::getline(std::cin, line);

  size_t counter = 0;
  while(!std::cin.eof()) {
    bool consecutive_equal = false;
    bool forbidden = false;
    size_t vowels = 0;
    for(int i = 0 ; i < line.size() - 1 ; ++i) {
      vowels += (is_vowel(line.at(i)) ? 1 : 0);
      if(line.at(i) == line.at(i+1))
	consecutive_equal = true;

      if((line.at(i) == 'a' && line.at(i+1) == 'b') ||
	 (line.at(i) == 'c' && line.at(i+1) == 'd') ||
	 (line.at(i) == 'p' && line.at(i+1) == 'q') ||
	 (line.at(i) == 'x' && line.at(i+1) == 'y')) {
	forbidden = true;
	break;
      }
    }

    vowels += (is_vowel(line.at(line.size() - 1)) ? 1 : 0);
    if(!forbidden && consecutive_equal && vowels >= 3)
      ++counter;

    std::getline(std::cin, line);
  }
  std::cout << counter << std::endl;
}
