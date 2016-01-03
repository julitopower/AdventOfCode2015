#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <array>
#include <boost/algorithm/string.hpp>

std::vector<std::vector<int>> generateAll(int limit, const std::vector<std::vector<int>>& input, bool find = false);

// This are the values provided in the quiz input. This solution is not very flexible, but
// get's the problem solved
std::array<std::array<int, 5>, 4> properties = {{{4, -2,  0, 0, 5},
						 {0,  5, -1, 0, 8},
						 {-1, 0,  5, 0, 6},
						 {0,  0, -2, 2, 1}}};

int main (int argc, char** argv) {
  std::string line;

  int limit = 100;
  int elements = 4;
  std::vector<std::vector<int>> v;
  for(int i = 0 ; i < elements - 1; ++i) {
    v = generateAll(limit, v); 
  }
  // For the last generation iteration we just want to print out the max value
  generateAll(limit, v, true);
}

std::vector<std::vector<int>> generateAll(int limit, const std::vector<std::vector<int>>& input,
					  bool find) {
  std::vector<std::vector<int>> output;

  // The input vector is empty, fill it please
  if (input.size() == 0) {
    for(int i = 0 ; i <= limit ; ++i) {
      output.push_back({i});
    }
    return std::move(output);
  }
  
  int max = 0;
  for(auto& v : input) {
    for(int i = 0 ; i <= limit ; ++i) {
      auto vCopy = v;
      vCopy.push_back(i);

      // Do not add options that add up to more than the limit otherwise
      // memory explodes. In fact memory explodes with more than 3 different
      // elements. This is why we use "find" hack, to not store in memory
      // the vector with the 4 elements.
      if(std::accumulate(vCopy.begin(), vCopy.end(), 0) <= limit) {
	if(find) {
	  int total = 1;
	  for(int i = 0 ; i < 4 ; ++i) {
	    int propTotal = 0;
	    for(int j = 0 ; j < vCopy.size() ; ++ j) {
	      propTotal += (vCopy[j] * properties[j][i]);
	    }
	    total *= (propTotal > 0) ? propTotal : 0;
	  }
	  max = std::max(total, max);
	} else {
	  output.push_back(std::move(vCopy));
	}
      } else {
	break;
      }
    }    
  }
  if(find)
    std::cout << "Max Total " << max << std::endl;
  return std::move(output);
}
