#include <iostream>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

const std::string SEPARATORS = "x";

size_t parse_line(const std::string& line);

int main (int argc, char** argv) {
  std::string line;
  std::getline(std::cin, line);

  size_t surface = 0;
  while(!cin.eof()) {
    surface += parse_line(line);
    std::getline(std::cin, line);
  }

  std::cout << surface << std::endl;
}

size_t parse_line(const std::string& line) {
  std::vector<std::string> strs;
  std::vector<int> values;

  boost::split(strs, line, boost::is_any_of(SEPARATORS));
  if(strs.size() != 3)
    return 0;

  for(auto& str : strs) {
    boost::trim(str);
    values.push_back(std::stoi(str));
  }

  std::sort(values.begin(), values.end());
  return 3 * values[0] * values[1] + 2 * values[1] * values[2] + 2 * values[2] * values[0];
}
