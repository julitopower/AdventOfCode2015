#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

const char UP = '^';
const char DOWN = 'v';
const char LEFT = '<';
const char RIGHT = '>';

int main(int argc, char** argv) {
  std::string input;
  std::cin >> input;

  int current_x = 0;
  int current_y = 0;
  std::set<std::pair<int, int>> visited {std::make_pair(current_x, current_y)};
  size_t count = 1;

  std::for_each(input.begin(), input.end(),
		[&visited, &current_x, &current_y, &count] (char& c) {
		  switch(c) {
		  case UP:
		    ++current_y;
		    break;
		  case DOWN:
		    --current_y;
		    break;
		  case LEFT:
		    --current_x;
		    break;
		  case RIGHT:
		    ++current_x;
		  }

		  if(visited.insert(std::make_pair(current_x, current_y)).second)
		    ++count;
		});
  std::cout << count << std::endl;
  return 0;
}
